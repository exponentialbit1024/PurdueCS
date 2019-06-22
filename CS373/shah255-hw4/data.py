import pandas as pd
import numpy as np

def load_data(datasetPath):
    data = pd.read_csv(datasetPath, sep=',', quotechar='"', header=0)
    return data

def split_data(df, per = 50):
    msk = np.random.rand(len(df)) < per / 100
    train = df[msk]
    test = df[~msk]
    return train, test

if __name__ == '__main__':
    X = load_data("yelp_cat.csv")
    x1, x2 = split_data(X, 10)
    x1.to_csv("train-set.csv", index = False)
    x2.to_csv("test-set.csv", index = False)
