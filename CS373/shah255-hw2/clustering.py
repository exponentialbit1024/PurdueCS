'''
By: Siddharth Shah
Using 2 late days
email: shah255@purdue.edu
'''
import numpy as np
import pandas as pd
import sys
from copy import deepcopy
import random
from heapq import heappush, heappop, heapify
import time
from scipy.spatial.distance import squareform, pdist
#from sklearn import preprocessing
#Euclidean dist
def dist(a, b, ax=1):
    return np.linalg.norm(a - b)

def load_data(datasetPath, logNorm = False, scikitScale = False):
    data = pd.read_csv(datasetPath, sep=',', quotechar='"', header=0)
    data = data[["latitude", "longitude", "reviewCount", "checkins"]]
    if logNorm:
        data["reviewCount"] = data["reviewCount"].apply(np.log)
        data["checkins"] = data["checkins"].apply(np.log)
    X = data.as_matrix()
    if scikitScale:
        X = preprocessing.scale(X)
    return X

def kmeans(X, k):
    num_instances, num_features = X.shape
    prototypes = X[np.random.randint(0, num_instances - 1, size=k)]
    prototypes_old = np.zeros(prototypes.shape)
    assignments = np.zeros((num_instances, 1))
    euc = dist(prototypes, prototypes_old)
    epsilon = 0
    sse = []
    while euc > epsilon:
        euc = dist(prototypes, prototypes_old)
        prototypes_old = prototypes
        for idx, data in enumerate(X):
            dist_centroid = np.zeros((k, 1))
            for idx2, data2 in enumerate(prototypes):
                dist_centroid[idx2] = dist(data2, data)
            assignments[idx, 0] = np.argmin(dist_centroid)

        new_prototypes = np.zeros((k, num_features))

        for index in range(len(prototypes)):
            point_clusters = [i for i in range(len(assignments)) if assignments[i] == index]
            mean = np.mean(X[point_clusters], axis = 0)
            new_prototypes[index, :] = mean
        prototypes = new_prototypes
    assignments = assignments.flatten()
    return prototypes, assignments

def sse(cluster, centroids):
    return dist(cluster, centroids) ** 2

def k_elbow(X):
    K = [2, 4, 8, 16, 32, 64]
    for k in K:
        centroids, assignments = kmeans(data, k)
        wc_sse = 0
        for index in range(k):
            point_clusters = [i for i in range(len(assignments)) if assignments[i] == index]
            wc_sse += sse(data[point_clusters], centroids[index])
        print("WC-SSE=" + str(wc_sse))
        for idx, centroid in enumerate(centroids):
            print("Centroid" + str(idx + 1) + "=" + str(centroid))

def cluster_plot(X, assignments, k, ac = False):
    from matplotlib import pyplot as plt
    if not ac:
        clusters = []
        for index in range(k):
            point_clusters = [i for i in range(len(assignments)) if assignments[i] == index]
            clusters.append(X[point_clusters])
        colors = ["c","y","g","b"]

        for idx, cluster in enumerate(clusters):
            lats = []
            lons = []
            revs = []
            chks = []
            for point in cluster:
                lats.append(point[0])
                lons.append(point[1])
                revs.append(point[2])
                chks.append(point[3])
            # plt.scatter(revs,chks, color = colors[idx])
            plt.scatter(lats,lons, color = colors[idx])
            # c1.append(np.vstack((lons, lats)))
        plt.show()
    else:
        clusters = assignments
        colors = ["y","g","b"]
        for idx, cluster in enumerate(clusters):
            lats = []
            lons = []
            revs = []
            chks = []
            for point in cluster:
                lats.append(point[0])
                lons.append(point[1])
                revs.append(point[2])
                chks.append(point[3])
            # plt.scatter(revs,chks, color = colors[idx])
            plt.scatter(lats,lons, color = colors[idx])
            # c1.append(np.vstack((lons, lats)))
        plt.show()

def heap_builder(X):
    pq = []
    dist_mat = list(squareform(pdist(X, metric = "euclidean")))
    for i in range(len(dist_mat)):
        for j in range(i):
            heappush(pq, (dist_mat[i][j], i, j))
    return dist_mat, pq

def init_aggl_cluster(X, preload = False):
    num_instances, num_features = X.shape

    dist_mat, pq = heap_builder(X)
    dataPoint = []
    clusters = {}
    for i in range(len(dist_mat)):
        dataPoint.append(X[i])
        clusters[i] = X[i]

    return clusters, pq, dist_mat, dataPoint

def flatten(cluster):
    # print("cluster", cluster)
    deeper = []
    oneD = []
    i = 0
    while len(cluster) > 0:
        i += 1
        if isinstance(cluster, list):
            frontier = cluster.pop(1)
            if len(frontier) == 4 and isinstance(frontier, np.ndarray):
                oneD.append(frontier)
                if len(cluster) == 1 and isinstance(cluster[0], np.ndarray):
                    oneD.append(cluster[0])
            else:
                oneD += flatten(frontier)
            cluster = cluster[0]
        else:
            break
    return oneD

def aggl(X, k):
    clusters, pq, dist_mat, dataPoints = init_aggl_cluster(X)
    cluster_rem = set()
    while len(clusters) > k:
        minDist = heappop(pq)
        pt_ids = minDist[1:]
        if pt_ids[0] not in cluster_rem and pt_ids[1] not in cluster_rem:
            cluster_rem.add(pt_ids[0])
            cluster_rem.add(pt_ids[1])
            dataPoints.append([dataPoints[pt_ids[0]], dataPoints[pt_ids[1]]])
            clusters[len(dataPoints) - 1] = [dataPoints[pt_ids[0]], dataPoints[pt_ids[1]]]

            del clusters[pt_ids[0]]
            del clusters[pt_ids[1]]

            new_distances = []
            for i in range(len(dist_mat)):
                if i != pt_ids[0] and i != pt_ids[1]:
                    if i > pt_ids[0]:
                        if i > pt_ids[1]:
                            dist = 0.5 * (dist_mat[i][pt_ids[0]] + dist_mat[i][pt_ids[1]])
                        else:
                            dist = 0.5 * (dist_mat[i][pt_ids[0]] + dist_mat[pt_ids[1]][i])
                    else:
                        if i > pt_ids[1]:
                            dist = 0.5 * (dist_mat[pt_ids[0]][i] + dist_mat[i][pt_ids[1]])
                        else:
                            dist = 0.5 * (dist_mat[pt_ids[0]][i] + dist_mat[pt_ids[1]][i])
                    new_distances.append(dist)
                    heappush(pq, (dist, len(dist_mat), i))
                else:
                    new_distances.append(0)
            new_distances.append(0)
            dist_mat.append(new_distances)

    wc_sse = 0
    centroids = []
    propClusters = []
    for c in clusters:
        clusterProp = flatten(clusters[c])
        propClusters.append(clusterProp)
        centroid = np.mean(clusterProp, axis = 0)
        centroids.append(centroid)
        wc_sse += sse(clusterProp, centroid)
    print("WC-SSE=" + str(wc_sse))
    return centroids, propClusters
    # print(len(pq))

if __name__ == '__main__':
    if len(sys.argv) < 4:
        print("Insufficient arguments")
        sys.exit(-1)
    datasetPath = sys.argv[1]
    K = int(sys.argv[2])
    model = sys.argv[3]
    data = load_data(datasetPath, logNorm = False)
    if model == 'km':
        # k_elbow(data)
        centroids, assignments = kmeans(data, K)
        # cluster_plot(data, assignments, K)
        wc_sse = 0
        for index in range(K):
            point_clusters = [i for i in range(len(assignments)) if assignments[i] == index]
            wc_sse += sse(data[point_clusters], centroids[index])
        print("WC-SSE=" + str(wc_sse))
        for idx, centroid in enumerate(centroids):
            print("Centroid" + str(idx + 1) + "=" + str(centroid))
    elif model == 'ac':
        # beginningTime = time.time()
        centroids, assignments = aggl(data, K)
        #cluster_plot(data, assignments, K, ac = True)
        for idx, centroid in enumerate(centroids):
            print("Centroid" + str(idx + 1) + "=" + str(centroid))
        # print(time.time() - beginningTime)
    else:
        print("Unknown model")
