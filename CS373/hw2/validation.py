import numpy as np
import pandas as pd
import sys
from copy import deepcopy
from sklearn.cluster import KMeans
from sklearn.cluster import AgglomerativeClustering

def load_data(datasetPath):
    data = pd.read_csv(datasetPath, sep=',', quotechar='"', header=0)
    data = data[["latitude", "longitude", "reviewCount", "checkins"]]
    X = data.as_matrix()
    return X

#Euclidean dist
def dist(a, b, ax=1):
    return np.linalg.norm(a - b, axis=ax)

def kmeans(X, k):
    kmeans = KMeans(n_clusters=k).fit(X)
    print(list(kmeans.cluster_centers_))
    # print(list(kmeans.predict(X)))

def aggl(X, k):
    agglO = AgglomerativeClustering(n_clusters=k, linkage="average").fit(X)
    print(agglO.labels_)

if __name__ == '__main__':
    if len(sys.argv) < 4:
        print("Insufficient arguments")
        sys.exit(-1)
    datasetPath = sys.argv[1]
    K = int(sys.argv[2])
    model = sys.argv[3]
    data = load_data(datasetPath)
    if model == 'km':
        kmeans(data, K)
    elif model == 'ac':
        aggl(data, K)
    else:
        print("Unknown model")
