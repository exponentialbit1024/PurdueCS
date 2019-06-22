import pandas as pd
from collections import namedtuple
from math import log
import sys
import time as time

Node    = namedtuple('Node', "left, right, numExs, feature")
Feature = namedtuple("Feature", "type, value")

positiveAtt  = '>50K'

def load_data(filename):
    data = pd.read_csv(filename, sep = ', ', quotechar = '"', header = None, engine='python')
    X = data.as_matrix()

    feats  = set()

    for x in X:
        for i in range(len(x) - 1):
            feats.add(Feature(i, x[i]))

    return X, feats

def vanilla(X, atts, isDepth, currDepth, maxDepth):
    length         = len(X);
    numNegativeAtt = 0;
    numPositiveAtt = 0;

    for i in range(length):
        if (X[i][8] == positiveAtt): numPositiveAtt += 1;
        else:                        numNegativeAtt += 1;

    if (isDepth and currDepth == maxDepth):
        if (numNegativeAtt > numPositiveAtt): return Node(None, None, (numPositiveAtt, numNegativeAtt), Feature(8, '<=50K'))
        else:                                 return Node(None, None, (numPositiveAtt, numNegativeAtt), Feature(8, positiveAtt))

    if (len(atts) == 0):
        if (numNegativeAtt > numPositiveAtt): return Node(None, None, (numPositiveAtt, numNegativeAtt), Feature(8, '<=50K'))
        else:                                 return Node(None, None, (numPositiveAtt, numNegativeAtt), Feature(8, positiveAtt))

    if (numPositiveAtt == length): return Node(None, None, (numPositiveAtt, numNegativeAtt), Feature(8, positiveAtt))
    if (numNegativeAtt == length): return Node(None, None, (numPositiveAtt, numNegativeAtt), Feature(8, '<=50K'))

    root        = None
    bestFeature = Feature(None, None)
    maxIG       = -1

    sorted(atts)

    for attribute in atts:
        gain = 0.0
        if (root == None or attribute.type != root.feture.type): gain = infoGain(X, attribute)
        if (gain > maxIG):
            maxIG       = gain
            bestFeature = attribute

    if (maxIG <= 0):
        if (numNegativeAtt > numPositiveAtt): return Node(None, None, (numPositiveAtt, numNegativeAtt), Feature(8, '<=50K'))
        else:                                 return Node(None, None, (numPositiveAtt, numNegativeAtt), Feature(8, positiveAtt))

    with_feature    = []
    without_feature = []

    for example in X:
        if (example[bestFeature.type] == bestFeature.value): with_feature    += [example]
        else:                                                without_feature += [example]

    root = Node(None, None, (numPositiveAtt, numNegativeAtt), bestFeature)
    if (len(with_feature) == 0):
        if (numNegativeAtt > numPositiveAtt): return Node(None, None, (numPositiveAtt, numNegativeAtt), Feature(8, '<=50K'))
        else:                                 return Node(None, None, (numPositiveAtt, numNegativeAtt), Feature(8, positiveAtt))

    else:
        root = Node(vanilla(with_feature, atts, isDepth, currDepth + 1, maxDepth), vanilla(without_feature, atts, isDepth, currDepth + 1, maxDepth), (numPositiveAtt, numNegativeAtt), bestFeature)

    return root

def infoGain(data, feature):
    if (len(data) == 0): return 0.0

    with_feature    = []
    without_feature = []

    for example in data:
        if (example[feature.type] == feature.value): with_feature    += [example]
        else:                                        without_feature += [example]

    if (len(with_feature) == 0 or len(without_feature) == 0): return 0.0

    gain =  entropy(data) - (float(float(len(with_feature)) / float(len(data)) * float(entropy(with_feature))) + float(float(len(without_feature)) / float(len(data)) * float(entropy(without_feature))))

    if (gain < 0.00000000000001): gain = 0

    return gain

def entropy(data):
    if (len(data) == 0): return 0.0

    numNegativeAtt = 0;
    numPositiveAtt = 0;

    for example in data:
        if (example[8] == positiveAtt): numPositiveAtt += 1;
        else:                           numNegativeAtt += 1;

    posProb = float(numPositiveAtt) / float(len(data));
    negProb = float(numNegativeAtt) / float(len(data));

    if (posProb == 0): return -1 * negProb * float(log(negProb, 2))
    if (negProb == 0): return -1 * posProb * float(log(posProb, 2))

    return -1 * (posProb * float(log(posProb, 2)) + negProb * float(log(negProb, 2)));

def accuracy(root, data):
    result = 0;
    for example in data:
        if (prediction(root, example)): result += 1

    return float(result) / float(len(data))

def prediction(root, example):
    if   (root.left == None and root.right == None):         return root.feature.value == example[8]
    elif (example[root.feature.type] != root.feature.value): return prediction(root.right, example)
    else:                                                    return prediction(root.left,  example)

def countNodes(root):
    count = 0
    if root.left is None and root.right is None:
        return 1
    else:
        if root.left is not None:
            count += countNodes(root.left)
        if root.right is not None:
            count += countNodes(root.right)

    return count

def pruning(root):
    if (root.left == None and root.right == None):
        if (root.feature.value == ">50K"): return root.numExs[1]
        else:                              return root.numExs[0]

    error = pruning(root.left) + pruning(root.right)
    if (error < min(root.numExs[0], root.numExs[1])): return error

    value = ""
    if (root.numExs[0] > root.numExs[1]): value = ">50K"
    else:                                 value = "<=50K"
    root._replace(left=None, right=None, feature=Feature(8, value))

    if (root.numExs[0] > root.numExs[1]): return root.numExs[1]
    else:                                 return root.numExs[0]

def main():
    maxDepth = -1
    if len(sys.argv) < 5:
        print("Not enough args")
        sys.exit(-1)
    trainFile = sys.argv[1]
    testFile = sys.argv[2]
    typeAlg = sys.argv[3]
    trainpct = int(sys.argv[4])

    if len(sys.argv) == 6:
        validpct = int(sys.argv[5])
    elif len(sys.argv) == 7:
        validpct = int(sys.argv[5])
        maxDepth = int(sys.argv[6])

    if maxDepth != -1:
        MAX_DEPTH = int(maxDepth)

    X, atts1 = load_data(trainFile)
    Xt, _ = load_data(testFile)

    root = None
    X = X[: int(len(X) * trainpct / 100)]
    root = vanilla(X, atts1, False, 0, 0)
    print("Training set accuracy: ", accuracy(root, X))
    print("Test set accuracy: ", accuracy(root, Xt))
    print("Nodes = ", countNodes(root))

if __name__ == '__main__':
    main()
