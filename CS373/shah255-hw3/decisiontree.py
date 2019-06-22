'''
By: Siddharth Shah  shah255@purdue.edu
Using 2 late days
'''

import pandas as pd
from collections import namedtuple
from math import log
import sys

MAX_DEPTH = float("inf")
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

def id3(X, feats, depth, depthF = False):

    totalSample = 0
    totalPos = 0

    for i in range(len(X)):
        totalSample += 1
        if X[i][8] == ">50K":
            totalPos += 1

    # print(depth, MAX_DEPTH)
    if depth == MAX_DEPTH:
        newNode = {}
        if (totalSample - totalPos) > totalPos:
            newNode['left'] = None
            newNode['right'] = None
            newNode['tot'] = totalSample
            newNode['pos'] = totalPos
            newNode['totA'] = 0
            newNode['posA'] = 0
            newNode['feat'] = Feature(8, '<=50K')
            return newNode
        else:
            newNode['left'] = None
            newNode['right'] = None
            newNode['tot'] = totalSample
            newNode['pos'] = totalPos
            newNode['totA'] = 0
            newNode['posA'] = 0
            newNode['feat'] = Feature(8, positiveAtt)
            return newNode

    if len(feats) == 0:
        newNode = {}
        if (totalSample - totalPos) > totalPos:
            newNode['left'] = None
            newNode['right'] = None
            newNode['tot'] = totalSample
            newNode['pos'] = totalPos
            newNode['totA'] = 0
            newNode['posA'] = 0
            newNode['feat'] = Feature(8, '<=50K')
            return newNode
        else:
            newNode['left'] = None
            newNode['right'] = None
            newNode['tot'] = totalSample
            newNode['pos'] = totalPos
            newNode['totA'] = 0
            newNode['posA'] = 0
            newNode['feat'] = Feature(8, positiveAtt)
            return newNode

    if totalPos == len(X):
        newNode = {}
        newNode['left'] = None
        newNode['right'] = None
        newNode['tot'] = totalSample
        newNode['pos'] = totalPos
        newNode['totA'] = 0
        newNode['posA'] = 0
        newNode['feat'] = Feature(8, positiveAtt)
        return newNode

    if totalSample - totalPos == len(X):
        newNode = {}
        newNode['left'] = None
        newNode['right'] = None
        newNode['tot'] = totalSample
        newNode['pos'] = totalPos
        newNode['totA'] = 0
        newNode['posA'] = 0
        newNode['feat'] = Feature(8, '<=50K')
        return newNode

    root = None
    bestFeat = Feature(None, None)
    maxIG = -1
    sorted(feats)

    for attr in feats:
        gain = 0.0
        if root is None:
            gain = infoGain(X, attr)
        if gain > maxIG:
            maxIG = gain
            bestFeat = attr

    if maxIG <= 0:
        if totalSample - totalPos > totalPos:
            newNode = {}
            newNode['left'] = None
            newNode['right'] = None
            newNode['tot'] = totalSample
            newNode['pos'] = totalPos
            newNode['totA'] = 0
            newNode['posA'] = 0
            newNode['feat'] = Feature(8, '<=50K')
            return newNode
        else:
            newNode = {}
            newNode['left'] = None
            newNode['right'] = None
            newNode['tot'] = totalSample
            newNode['pos'] = totalPos
            newNode['totA'] = 0
            newNode['posA'] = 0
            newNode['feat'] = Feature(8, positiveAtt)
            return newNode

    pos_dp = []
    neg_dp = []

    for x in X:
        if x[bestFeat.type] == bestFeat.value:
            pos_dp += [x]
        else:
            neg_dp += [x]

    root = {}
    root['left'] = None
    root['right'] = None
    root['tot'] = totalSample
    root['pos'] = totalPos
    root['feat'] = bestFeat

    if len(pos_dp) == 0:
        if totalSample - totalPos > totalPos:
            newNode = {}
            newNode['left'] = None
            newNode['right'] = None
            newNode['tot'] = totalSample
            newNode['pos'] = totalPos
            newNode['totA'] = 0
            newNode['posA'] = 0
            newNode['feat'] = Feature(8, '<=50K')
            return newNode
        else:
            newNode = {}
            newNode['left'] = None
            newNode['right'] = None
            newNode['tot'] = totalSample
            newNode['pos'] = totalPos
            newNode['totA'] = 0
            newNode['posA'] = 0
            newNode['feat'] = Feature(8, positiveAtt)
            return newNode
    else:
        root = {}
        if depthF:
            depth += 1
        root['left'] = id3(pos_dp, feats, depth, depthF = depthF)
        root['right'] = id3(neg_dp, feats, depth, depthF = depthF)
        root['tot'] = totalSample
        root['pos'] = totalPos
        root['totA'] = 0
        root['posA'] = 0
        root['feat'] = bestFeat
    return root

def infoGain(X, feat):
    if len(X) == 0:
        return 0.0

    pos_dp = []
    neg_dp = []

    for x in X:
        if x[feat.type] == feat.value:
            pos_dp += [x]
        else:
            neg_dp += [x]

    if len(pos_dp) == 0 or len(neg_dp) == 0:
        return 0.0

    gain = entropy(X) - (float(float(len(pos_dp)) / float(len(X)) * float(entropy(pos_dp))) + float(float(len(neg_dp)) / float(len(X)) * float(entropy(neg_dp))))
    if gain < 0.00000001:
        return 0.0
    return gain

def entropy(X):
    if len(X) == 0:
        return 0.0

    totalPos = 0
    totalSample = 0

    for x in X:
        totalSample += 1
        if x[8] == ">50K":
            totalPos += 1

    pos_pb = float(totalPos) / float(len(X))
    neg_pb = float(totalSample - totalPos) / float(len(X))

    if pos_pb == 0:
        return -1 * neg_pb * float(log(neg_pb, 2))

    if neg_pb == 0:
        return -1 * pos_pb * float(log(pos_pb, 2))

    return -1 * (pos_pb * float(log(pos_pb, 2)) + neg_pb * float(log(neg_pb, 2)))

def predict(tree, dataPoint):
    if tree['left'] is None and tree['right'] is None:
        return tree['feat'].value == dataPoint[8]
    elif dataPoint[tree['feat'].type] != tree['feat'].value:
        return predict(tree['right'], dataPoint)
    else:
        return predict(tree['left'], dataPoint)

def accuracy(tree, X):
    result = 0
    for x in X:
        if predict(tree, x):
            result += 1
    return float(result) / float(len(X))

def pruning(tree):
    if tree['left'] is None and tree['right'] is None:
        if tree['feat'].value == ">50K":
            return tree['totA'] - tree['posA']
        else:
            return tree['posA']
    else:
        errL = pruning(tree['left'])
        errR = pruning(tree['right'])
        err = errL + errR

        if tree['totA'] - tree['posA'] > err:
            return err
        else:
            tree['left'] = None
            tree['right'] = None

            if tree['posA'] > tree['totA'] - tree['posA']:
                tree['feat'] = Feature(8, ">50K")
                return tree['totA'] - tree['posA']
            else:
                tree['feat'] = Feature(8, "<=50K")
                return tree['posA']

def prune_classify(dataPoint, tree):
    tree['totA'] += 1
    if dataPoint[8] == ">50K":
        tree['posA'] += 1
    if tree['left'] is not None or tree['right'] is not None:
        if dataPoint[tree['feat'].type] == tree['feat'].value:
            return prune_classify(dataPoint, tree['left'])
        else:
            return prune_classify(dataPoint, tree['right'])

def tree_print(tree):
    if tree['left'] is None and tree['right'] is None:
        print(tree)
    else:
        if tree['left'] is not None:
            tree_print(tree['left'])
        if tree['right'] is not None:
            tree_print(tree['right'])

def pre_pruning(vX, tree):
    for x in vX:
        prune_classify(x, tree)
    return tree

def main():
    global MAX_DEPTH
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

    X, feats = load_data(trainFile)
    Xv = X[: int(len(X) * trainpct / 100)]

    Xt, _ = load_data(testFile)

    if typeAlg == "vanilla":
        root = id3(Xv, feats, 1)
        print "Training set accuracy: ", accuracy(root, Xv)
        print "Test set accuracy: ", accuracy(root, Xt)
        # print("Nodes = ", node_counter(root))
    elif typeAlg == "depth":
        # for i in [1, 4, 7, 10, 13, 16, 19, 22, 25, 28, 31, 34]:
            # MAX_DEPTH = i
            # print("depth", i)
        root = id3(Xv, feats, 1, depthF = True)
        print "Training set accuracy: ", accuracy(root, Xv)
        if validpct > 0:
            vX = X[int(len(X) * trainpct / 100) : int(len(X) * trainpct / 100) + int(len(X) * validpct / 100)]
            print "Validation set accuracy: ", accuracy(root, vX)
        else:
            print "Validation set accuracy: ", accuracy(root, Xv)
        print "Test set accuracy: ", accuracy(root, Xt)
        # print("Nodes = ", node_counter(root))
    elif typeAlg == "prune":
        root = id3(Xv, feats, 1)
        # print("Nodes = ", node_counter(root))
        vX = X[int(len(X) * trainpct / 100) : int(len(X) * trainpct / 100) + int(len(X) * validpct / 100)]
        root = pre_pruning(vX, root)
        pruning(root)
        # print(root)
        # print("Nodes = ", node_counter(root))
        print "Training set accuracy: ", accuracy(root, Xv)
        print "Test set accuracy: ", accuracy(root, Xt)

if __name__ == "__main__":
    main()
