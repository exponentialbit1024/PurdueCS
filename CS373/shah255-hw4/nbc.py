import pandas as pd
import numpy as np
import sys
import math

class NBC:

    def __init__(self, X, Xt, maxIter = 2):
        self.X = X
        self.Xt = Xt
        self.maxIter = maxIter

        self.positive = {}
        self.negative = {}

        self.posC = 0
        self.posGramCount = 0
        self.negGramCount = 0
        self.pA = 0
        self.pNA = 0

        self.alpha = 0

        flattened = [feat for feats in self.X for feat in feats[:-1]]
        self.unique = len(set(flattened))

    def train(self):
        for x in self.X:
            label = x[-1]
            feats = x[:-1]
            if label == 1:
                self.posC += 1
            for feat in feats:
                if label == 1:
                    self.positive[feat] = self.positive.get(feat, 0) + 1
                    self.posGramCount += 1
                else:
                    self.negative[feat] = self.negative.get(feat, 0) + 1
                    self.negGramCount += 1

        self.pA = self.posC / float(len(self.X))
        self.pNA = 1.0 - self.pA

    def prediction(self, x, alpha = 1.0):
        self.alpha = alpha
        isPos = self.pA * self.conditionalProb(x, 1)
        isNeg = self.pNA * self.conditionalProb(x, 0)
        if isPos > isNeg:
            return 1
        return 0

    def conditionalProb(self, x, label):
        result = 1.0
        for xi in x:
            result *= self.conditionalPoint(xi, label)
        return result

    def conditionalPoint(self, feat, label):
        # alpha = self.alpha
        alpha = 0
        if label == 1:
            return (self.positive.get(feat, 0) + alpha) / float(self.posGramCount + alpha * self.unique)
        else:
            return (self.negative.get(feat, 0) + alpha) / float(self.negGramCount + alpha * self.unique)

    def predict_test(self):
        y_hat = []
        y = []
        # sse = 0
        for x in self.Xt:
            y.append(x[-1])
            y_hat.append(self.prediction(x[:-1]))
            # if x[-1] == 0:
                # sse += (1 - self.conditionalProb(x[:-1], 0) / (self.conditionalProb(x[:-1], 0) + self.conditionalProb(x[:-1], 1))) ** 2
            # else:
                # sse += (1 - self.conditionalProb(x[:-1], 1) / (self.conditionalProb(x[:-1], 0) + self.conditionalProb(x[:-1], 1))) **2
        acc = 0
        # y_base = np.ones(len(y))
        # base = 0

        for i in range(len(y_hat)):
            if y_hat[i] == y[i]:
                acc += 1
            # if y[i] == y_base[i]:
                # base += 1
        # print(1 - base / len(y))
        # print(sse / len(y))
        return 1 - float(acc) / len(y)

def load_data(datasetPath):
    X = pd.read_csv(datasetPath, sep=',', quotechar='"', header=0)
    return X.as_matrix()

if __name__ == '__main__':
    if len(sys.argv) < 3:
        print("Insufficient args")
        sys.exit(-1)

    if len(sys.argv) == 3:
        maxIter = 2
        trainFile = sys.argv[1]
        testFile = sys.argv[2]
    else:
        trainFile = sys.argv[1]
        testFile = sys.argv[2]
        maxIter = int(sys.argv[3])

    X = load_data(trainFile)
    Xt = load_data(testFile)

    nbc = NBC(X, Xt)
    nbc.train()
    # print(nbc.pA)
    loss = nbc.predict_test()
    print("ZERO-ONE LOSS=" + str(loss))
