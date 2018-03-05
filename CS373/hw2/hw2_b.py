import numpy as np
import pandas as pd
import sys
from copy import deepcopy
import random
from sklearn.metrics.pairwise import pairwise_distances

#Euclidean dist
def dist(a, b, ax=1):
    return np.linalg.norm(a - b)

def load_data(datasetPath):
    data = pd.read_csv(datasetPath, sep=',', quotechar='"', header=0)
    data = data[["latitude", "longitude", "reviewCount", "checkins"]]
    X = data.as_matrix()
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
            # print((X[point_clusters] - mean) ** 2)
            new_prototypes[index, :] = mean
        prototypes = new_prototypes
    assignments = assignments.flatten()
    return prototypes, assignments

def sse(X, centroids, assignments):
    pass

def hierarchical_clustering(data, no_of_clusters):
    #first step is to calculate the initial distance matrix
    #it consists distances from all the point to all the point
    color = ['r','g','b','y','c','m','k','w']
    initial_distances = pairwise_distances(data,metric='euclidean')
    #making all the diagonal elements infinity
    np.fill_diagonal(initial_distances,sys.maxsize)
    clusters = find_clusters(initial_distances)

    #plotting the clusters
    iteration_number = initial_distances.shape[0] - no_of_clusters
    clusters_to_plot = clusters[iteration_number]
    arr = np.unique(clusters_to_plot)

    indices_to_plot = []
    for x in np.nditer(arr):
        indices_to_plot.append(np.where(clusters_to_plot==x))
    p=0

    print(clusters_to_plot)


def find_clusters(input):
    clusters = {}
    row_index = -1
    col_index = -1
    array = []


    for n in range(input.shape[0]):
        array.append(n)

    clusters[0] = np.array(array).copy()

    #finding minimum value from the distance matrix
    #note that this loop will always return minimum value from bottom triangle of matrix
    for k in range(1, input.shape[0]):
        min_val = sys.maxsize

        for i in range(0, input.shape[0]):
            for j in range(0, input.shape[1]):
                if(input[i][j]<=min_val):
                    min_val = input[i][j]
                    row_index = i
                    col_index = j

        #once we find the minimum value, we need to update the distance matrix
        #updating the matrix by calculating the new distances from the cluster to all points

        for i in range(0,input.shape[0]):
            if(i != col_index and i!=row_index):
                temp = (input[col_index][i]+input[row_index][i])/2
                input[col_index][i] = temp
                input[i][col_index] = temp
                print(temp)

        #set the rows and columns for the cluster with higher index i.e. the row index to infinity
        #Set input[row_index][for_all_i] = infinity
        #set input[for_all_i][row_index] = infinity
        for i in range (0,input.shape[0]):
            input[row_index][i] = sys.maxsize
            input[i][row_index] = sys.maxsize

        #Manipulating the dictionary to keep track of cluster formation in each step
        #if k=0,then all datapoints are clusters

        minimum = min(row_index,col_index)
        maximum = max(row_index,col_index)
        for n in range(len(array)):
            if(array[n]==maximum):
                array[n] = minimum
        clusters[k] = np.array(array).copy()

    return clusters

if __name__ == '__main__':
    if len(sys.argv) < 4:
        print("Insufficient arguments")
        sys.exit(-1)
    datasetPath = sys.argv[1]
    K = int(sys.argv[2])
    model = sys.argv[3]
    data = load_data(datasetPath)
    if model == 'km':
        centroids, assignments = kmeans(data, K)
        print(assignments)
    elif model == 'ac':
        hierarchical_clustering(data, K)
    else:
        print("Unknown model")
