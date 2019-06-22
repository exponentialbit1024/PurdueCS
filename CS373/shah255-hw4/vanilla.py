import pandas as pd
import numpy as np
import sys
# from sklearn.metrics import zero_one_loss
import time

def load_data(datasetPath):
    X = pd.read_csv(datasetPath, sep=',', quotechar='"', header=0)
    return X

def binarize(x1, x2):
    splitPoint = len(x1)
    x1 = x1.drop(labels="goodForGroups", axis = 1)
    x2 = x2.drop(labels="goodForGroups", axis = 1)
    frames = [x1, x2]
    merge = pd.concat(frames)
    binarizeD = pd.get_dummies(merge, columns=merge.columns.values)
    binaryMx = binarizeD.as_matrix()
    return binaryMx, splitPoint

def split_vector(mergeMx, splitPoint):
    X = mergeMx[:splitPoint]
    Xt = mergeMx[splitPoint:]
    return X, Xt

def prediction(b, weights, x):
    dtp = np.dot(x, weights) + b
    if dtp >= 0:
        return 1
    return 0

def train(X, maxIter, y):
    weights = np.array([0.0 for i in range(len(X[0]))])
    b = 0
    for i in range(maxIter):
        for idx, j in enumerate(X):
            pred = prediction(b, weights, j)
            err = y[idx] - pred
            if err:
                b += err
                weights = [i + err * k for i, k in zip(weights, j)]
    return b, weights

def predict_batch(X, y, nn):
    bias = nn[0]
    weights = nn[1]
    y_hat = []
    y = np.array(y, dtype=float)

    for x in X:
        y_hat.append(prediction(bias, weights, x))

    acc = 0
    for i in range(len(y_hat)):
        if y_hat[i] == y[i]:
            acc += 1

    y_hat = np.array(y_hat, dtype=float)
    return 1 - float(acc) / len(y)

if __name__ == '__main__':
    start = time.time()
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

    y = X['goodForGroups'].as_matrix()
    yt = Xt['goodForGroups'].as_matrix()

    mergeDf = binarize(X, Xt)
    X, Xt = split_vector(mergeDf[0], mergeDf[1])

    nn = train(X, maxIter, y)
    # print(nn)
    loss = predict_batch(Xt, yt, nn)
    print("ZERO-ONE LOSS=" + str(loss))
    # print(time.time() - start)
