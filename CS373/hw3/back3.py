import pandas as pd
from collections import namedtuple
from math import log
import sys
import time as time

Node    = namedtuple('Node', "left, right, numExs, feature")
Feature = namedtuple("Feature", "type, value")

positiveAtt  = '>50K'

def vanilla(X, atts, isDepth, currDepth, maxDepth):
    length         = len(X);
    numNegativeAtt = 0;
    numPositiveAtt = 0;

    for i in range(length):
        if (X[i][8] == positiveAtt): numPositiveAtt += 1;
        else:                        numNegativeAtt += 1;

    # end case for depth model
    if (isDepth and currDepth == maxDepth):
        if (numNegativeAtt > numPositiveAtt): return Node(None, None, (numPositiveAtt, numNegativeAtt), Feature(8, '<=50K'))
        else:                                 return Node(None, None, (numPositiveAtt, numNegativeAtt), Feature(8, positiveAtt))

    # base case - No attributes to split on
    if (len(atts) == 0):
        if (numNegativeAtt > numPositiveAtt): return Node(None, None, (numPositiveAtt, numNegativeAtt), Feature(8, '<=50K'))
        else:                                 return Node(None, None, (numPositiveAtt, numNegativeAtt), Feature(8, positiveAtt))

    # base case - all examples in data have same label
    if (numPositiveAtt == length): return Node(None, None, (numPositiveAtt, numNegativeAtt), Feature(8, positiveAtt))
    if (numNegativeAtt == length): return Node(None, None, (numPositiveAtt, numNegativeAtt), Feature(8, '<=50K'))

    # recursive case
    root        = None
    bestFeature = Feature(None, None)
    maxIG       = -1

    # to break ties when all atts are same
    sorted(atts)

    # select best feature
    for attribute in atts:
        gain = 0.0
        if (root == None or attribute.type != root.feture.type): gain = infoGain(X, attribute)
        if (gain > maxIG):
            maxIG       = gain
            bestFeature = attribute

    #print "IG = ", maxIG, "BF = ", bestFeature.value
    # base case - No best attribute
    if (maxIG <= 0):
        #atts.pop()
        if (numNegativeAtt > numPositiveAtt): return Node(None, None, (numPositiveAtt, numNegativeAtt), Feature(8, '<=50K'))
        else:                                 return Node(None, None, (numPositiveAtt, numNegativeAtt), Feature(8, positiveAtt))

    #print "BF = ", bestFeature.value
    # partition examples
    with_feature    = []
    without_feature = []

    for example in X:
        if (example[bestFeature.type] == bestFeature.value): with_feature    += [example]
        else:                                                without_feature += [example]

    root = Node(None, None, (numPositiveAtt, numNegativeAtt), bestFeature)
    # base case - No data in subset with best feature
    if (len(with_feature) == 0):
        if (numNegativeAtt > numPositiveAtt): return Node(None, None, (numPositiveAtt, numNegativeAtt), Feature(8, '<=50K'))
        else:                                 return Node(None, None, (numPositiveAtt, numNegativeAtt), Feature(8, positiveAtt))

    else:
        #atts.discard(bestFeature)
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
    # Read the arguments
    file_path   = sys.argv[1]
    testFile    = sys.argv[2]
    model       = sys.argv[3]
    trainSetPct = int(sys.argv[4])

    # Read the data from training file
    data1  = pd.read_csv(file_path, sep = ', ', quotechar = '"', header = None, engine='python')
    X1     = data1.as_matrix()
    atts1  = set()

    for example in X1:
        for i in range(len(example) - 1):
            atts1.add(Feature(i, example[i]))

    # Read the data from test file
    data2  = pd.read_csv(testFile, sep = ', ', quotechar = '"', header = None, engine='python')
    X2     = data2.as_matrix()
    atts2  = set()

    for example in X2:
        for i in range(len(example) - 1):
            atts2.add(Feature(i, example[i]))

    root = None
    #root2 = None

    startTime = time.time()

    if (model == "vanilla"):
        X    = X1[: int(len(X1) * trainSetPct / 100)]
        root = vanilla(X1, atts1, False, 0, 0)
        #root2 = vanilla(X2, atts2, False, 0, 0)
        print("Training set accuracy: ", accuracy(root, X))
        print("Test set accuracy: ", accuracy(root, X2))
        print("Nodes = ", countNodes(root))

    elif (model == "depth"):
        validationSetPct = int(sys.argv[5])
        maxDepth         = int(sys.argv[6])

        X    = X1[:(len(X1) * trainSetPct / 100)]
        root = vanilla(X, atts1, True, 0, maxDepth)
        #root2 = vanilla(X2, atts2, True, 0, maxDepth)
        print("Training set accuracy: ", accuracy(root, X))
        X     = X1[-(len(X1) * validationSetPct / 100):]
        print("Validation set accuracy: ", accuracy(root, X))
        print("Test set accuracy: ", accuracy(root, X2))

    elif (model == "prune"):
        validationSetPct = int(sys.argv[5])
        X    = X1[: int(len(X1) * trainSetPct / 100)]
        root = vanilla(X, atts1, False, 0, 0)
        pruning(root)

        print("Training set accuracy: ", accuracy(root, X))
        X    = X1[: int(len(X1) * validationSetPct / 100)]
        print("Test set accuracy: ", accuracy(root, X2))
        print("Nodes = ", countNodes(root))

    endTime = time.time() - startTime
    #print(endTime)

if __name__ == "__main__": main()
