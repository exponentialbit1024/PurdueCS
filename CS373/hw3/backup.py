import pandas as pd
import sys

from operator import itemgetter
from math import log2
import copy

class Tree:

    def __init__(self, variable, children):
        self.variable = variable
        self.children = children
        self.parents = ["salaryLevel"]

    def nextLevel(self):
        for child in self.children:
            if isinstance(self.children[child], Tree):
                self.children[child].nextLevel()
            elif entropy(self.children[child]) != 0:
                best, self.children[child] = datasetToTree(self.children[child], self.parents)
                self.children[child].parents = self.parents + [best]

def entropy(data):
    if len(set(point["salaryLevel"] for point in data)) == 1:
        return 0
    N = len(list(filter(itemgetter("salaryLevel"), data))) / len(data)
    return -N * log2(N) - (1 - N) * log2(1 - N)

def datasetToTree(data, exclude):
    entropies = [(var, crossEntropy(data, var)) for var in data[0] if var not in exclude]
    best, _ = max(entropies, key = itemgetter(1))
    return best, Tree(variable = best, children = split(data, best))

def crossEntropy(data, var):
    values = set(point[var] for point in data)
    E = 0
    for value in values:
        p = sum(point[var] == value for point in data) / len(data)
        E += p * entropy(list(filter(lambda point: point[var] == value, data)))
    return entropy(data) - E

def split(data, var):
    values = set(point[var] for point in data)
    tree = dict()
    for value in values:
        tree[value] = list(filter(lambda point: point[var] == value, data))
    return tree

def load_data(filename):
    data = pd.read_csv(filename, sep=',', quotechar='"', header=None, engine='python')
    X = data.as_matrix()
    dictX = []
    y = []
    for dataPoint in X:
        dictPoint = {}
        dictPoint['workclass'] = dataPoint[0]
        dictPoint['education'] = dataPoint[1]
        dictPoint['marital-status'] = dataPoint[2]
        dictPoint['occupation'] = dataPoint[3]
        dictPoint['relationship'] = dataPoint[4]
        dictPoint['race'] = dataPoint[5]
        dictPoint['sex'] = dataPoint[6]
        dictPoint['native-country'] = dataPoint[7]
        if '>50' in dataPoint[8]:
            dictPoint['salaryLevel'] = True
        else:
            dictPoint['salaryLevel'] = False
        y.append(dictPoint['salaryLevel'])
        dictX.append(dictPoint)
    return dictX, y

def predict(tree, datapoint):
    maxShare = 0
    currentPred = False
    treeOb = tree[1]
    while isinstance(treeOb, Tree):
        for key, value in datapoint.items():
            if isinstance(treeOb, Tree):
                if value in treeOb.children:
                    treeOb = treeOb.children[value]
                else:
                    for keyc, valuec in treeOb.children.items():
                        if isinstance(valuec, Tree):
                            treeOb = valuec
                            continue
                        else:
                            print("children", type(valuec))
            else:
                for dp in treeOb:
                    shared_items = set(dp.items()) & set(datapoint.items())
                    if maxShare < len(shared_items):
                        maxShare = len(shared_items)
                        currentPred = dp['salaryLevel']
                break
    return currentPred

def generate_model(X, labelCol):
    treeOb = datasetToTree(X, "salaryLevel")
    treeOb[1].nextLevel()
    return treeOb

def predict_test(X, y, treeOb):
    y_hat = []
    for x in X:
        yy = predict(treeOb, x)
        # print(yy)
        y_hat.append(yy)
    uneqC = 0
    for idx, pred in enumerate(y_hat):
        if pred != y[idx]:
            uneqC += 1
    print(len(X) - uneqC)
    return len(X) - uneqC

def predict_train(X, y, treeOb):
    y_hat = []
    for x in X:
        yy = predict(treeOb, x)
        # print(yy)
        y_hat.append(yy)
    uneqC = 0
    for idx, pred in enumerate(y_hat):
        if pred != y[idx]:
            uneqC += 1
    print(len(X) - uneqC)
    return len(X) - uneqC

if __name__ == '__main__':
    if len(sys.argv) < 5:
        print("Not enough args")
        sys.exit(-1)
    trainFile = sys.argv[1]
    testFile = sys.argv[2]
    typeAlg = sys.argv[3]
    trainpct = sys.argv[4]

    if len(sys.argv) == 6:
        validpct = sys.arv[5]
    elif len(sys.argv) == 7:
        validpct = sys.arv[5]
        maxDepth = sys.arv[6]

    X, y = load_data(trainFile)
    X = X[:int((int(trainpct) / 100) * len(X))]

    Xt, y_t = load_data(testFile)

    print(len(X))

    ttype = input("Test type: ")

    if ttype == 't':
        treeOb = generate_model(X, "salaryLevel")
        t1 = predict_test(Xt, y_t, treeOb)
        t2 = predict_test(Xt, y_t, treeOb)
        t3 = predict_test(Xt, y_t, treeOb)
        t4 = predict_test(Xt, y_t, treeOb)
        print(t1, t2, t3, t4)
        input("")

        treeOb2 = generate_model(X, "salaryLevel")
        t1 = predict_test(Xt, y_t, treeOb2)
        t2 = predict_test(Xt, y_t, treeOb2)
        t3 = predict_test(Xt, y_t, treeOb2)
        t4 = predict_test(Xt, y_t, treeOb2)
        print(t1, t2, t3, t4)
        input("")

        treeOb3 = generate_model(X, "salaryLevel")
        t1 = predict_test(Xt, y_t, treeOb3)
        t2 = predict_test(Xt, y_t, treeOb3)
        t3 = predict_test(Xt, y_t, treeOb3)
        t4 = predict_test(Xt, y_t, treeOb3)
        print(t1, t2, t3, t4)

    else:
        treeOb = generate_model(X, "salaryLevel")
        print(treeOb)
        t1 = predict_train(X, y, treeOb)
        t2 = predict_train(X, y, treeOb)
        t3 = predict_train(X, y, treeOb)
        t4 = predict_train(X, y, treeOb)
        t5 = predict_train(X, y, treeOb)
        print(t1, t2, t3, t4, t5)
        input("")

        treeOb2 = generate_model(X, "salaryLevel")
        t1 = predict_train(X, y, treeOb2)
        t2 = predict_train(X, y, treeOb2)
        t3 = predict_train(X, y, treeOb2)
        t4 = predict_train(X, y, treeOb2)
        t5 = predict_train(X, y, treeOb2)
        print(t1, t2, t3, t4, t5)
        input("")

        treeOb3 = generate_model(X, "salaryLevel")
        t1 = predict_train(X, y, treeOb3)
        t2 = predict_train(X, y, treeOb3)
        t3 = predict_train(X, y, treeOb3)
        t4 = predict_train(X, y, treeOb3)
        t5 = predict_train(X, y, treeOb3)
        print(t1, t2, t3, t4, t5)
