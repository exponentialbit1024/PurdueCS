import pandas as pd
import ast
import csv
import sys
import math
import os
import copy

MAX_DEPTH = 1000000

def label_bool_map(inp):
    if '>50' in inp:
        return True
    else:
        return False

def load_data(filename):
    data = pd.read_csv(filename, sep=',', quotechar='"', header=None, engine='python')

    labels = data.iloc[:,-1].as_matrix()
    y = []
    for lb in labels:
        y.append(label_bool_map(lb))

    all_row = data.as_matrix()

    headers = ["workclass", "education", "marital-status", "occupation", "relationship", "race", "sex", "native-country", "salaryLevel"]
    idx_to_name, name_to_idx = get_header_name_to_idx_maps(headers)

    data = {
        'header': headers,
        'rows': all_row,
        'name_to_idx': name_to_idx,
        'idx_to_name': idx_to_name
    }

    return data, y


def get_header_name_to_idx_maps(headers):
    name_to_idx = {}
    idx_to_name = {}
    for i in range(0, len(headers)):
        name_to_idx[headers[i]] = i
        idx_to_name[i] = headers[i]
    return idx_to_name, name_to_idx

def get_uniq_values(data):
    idx_to_name = data['idx_to_name']
    idxs = idx_to_name.keys()

    val_map = {}
    for idx in iter(idxs):
        val_map[idx_to_name[idx]] = set()

    for data_row in data['rows']:
        for idx in idx_to_name.keys():
            att_name = idx_to_name[idx]
            val = data_row[idx]
            if val not in val_map.keys():
                val_map[att_name].add(val)
    return val_map


def get_class_labels(data, target_attribute):
    rows = data['rows']
    col_idx = data['name_to_idx'][target_attribute]
    labels = {}
    for r in rows:
        val = r[col_idx]
        if val in labels:
            labels[val] = labels[val] + 1
        else:
            labels[val] = 1
    return labels


def entropy(n, labels):
    ent = 0
    for label in labels.keys():
        p_x = labels[label] / n
        if p_x > 0:
            ent += - p_x * math.log(p_x, 2)
        else:
            ent += 0
    return ent


def partition_data(data, group_att):
    partitions = {}
    data_rows = data['rows']
    partition_att_idx = data['name_to_idx'][group_att]
    for row in data_rows:
        row_val = row[partition_att_idx]
        if row_val not in partitions.keys():
            partitions[row_val] = {
                'name_to_idx': data['name_to_idx'],
                'idx_to_name': data['idx_to_name'],
                'rows': list()
            }
        partitions[row_val]['rows'].append(row)
    return partitions


def avg_entropy_w_partitions(data, splitting_att, target_attribute):
    # find uniq values of splitting att
    data_rows = data['rows']
    n = len(data_rows)
    partitions = partition_data(data, splitting_att)

    avg_ent = 0

    for partition_key in partitions.keys():
        partitioned_data = partitions[partition_key]
        partition_n = len(partitioned_data['rows'])
        partition_labels = get_class_labels(partitioned_data, target_attribute)
        partition_entropy = entropy(partition_n, partition_labels)
        avg_ent += partition_n / n * partition_entropy

    return avg_ent, partitions


def most_common_label(labels):
    mcl = max(labels, key=lambda k: labels[k])
    return mcl

def id3(data, uniqs, remaining_atts, target_attribute, depth):
    global MAX_DEPTH
    labels = get_class_labels(data, target_attribute)

    node = {}

    if depth > MAX_DEPTH:
        node['label'] = most_common_label(labels)
        node['error'] = 0
        node['left'] = True
        node['right'] = False
        return node

    # print(depth, MAX_DEPTH)

    if len(labels.keys()) == 1:
        node['label'] = next(iter(labels.keys()))
        node['error'] = 0
        node['left'] = True
        node['right'] = False
        return node

    if len(remaining_atts) == 0:
        node['label'] = most_common_label(labels)
        node['error'] = 0
        node['left'] = True
        node['right'] = False
        return node

    n = len(data['rows'])
    ent = entropy(n, labels)

    max_info_gain = None
    max_info_gain_att = None
    max_info_gain_partitions = None

    for remaining_att in remaining_atts:
        avg_ent, partitions = avg_entropy_w_partitions(data, remaining_att, target_attribute)
        info_gain = ent - avg_ent
        if max_info_gain is None or info_gain > max_info_gain:
            max_info_gain = info_gain
            max_info_gain_att = remaining_att
            max_info_gain_partitions = partitions

    if max_info_gain is None:
        node['label'] = most_common_label(labels)
        node['error'] = 0
        return node

    node['attribute'] = max_info_gain_att
    node['nodes'] = {}

    remaining_atts_for_subtrees = set(remaining_atts)
    remaining_atts_for_subtrees.discard(max_info_gain_att)

    uniq_att_values = uniqs[max_info_gain_att]

    for att_value in uniq_att_values:
        if att_value not in max_info_gain_partitions.keys():
            node['left'] = True
            node['right'] = False
            node['nodes'][att_value] = {'label': most_common_label(labels)}
            node['nodes'][att_value]['error'] = 0
            node['error'] = 0
            continue

        partition = max_info_gain_partitions[att_value]
        depth += 1
        node['error'] = 0
        node['left'] = False
        node['right'] = True
        node['nodes'][att_value] = id3(partition, uniqs, remaining_atts_for_subtrees, target_attribute, depth)
        node['mostVotes'] = most_common_label(labels)

    return node

def prune(tree):
    if 'label' in tree:
        return tree['error']

    for child in tree['nodes']:
        print(tree['nodes'][child]['right'], tree['nodes'][child]['left'])

def id3_prune(root, X):
    tree = copy.deepcopy(root)
    troot = tree
    for x in X:
        tree = troot
        while 'nodes' in tree:
            tempAttr = tree['attribute']
            for node in tree['nodes']:
                if node in x:
                    if tree['mostVotes'] != x[8]:
                        tree['error'] += 1
                    tree = tree['nodes'][node]
            if 'attribute' in tree:
                if tree['attribute'] == tempAttr:
                    if tree['mostVotes'] != x[8]:
                        tree['error'] += 1
                    tree = {'label' : tree['mostVotes'], 'error' : tree['error']}
    tree = troot
    print(X[0])
    prune(tree)
    # print(tree['nodes'][' Husband']['nodes'][' HS-grad']['nodes'][' Prof-specialty']['nodes']['Private'])

    # for key, value in tree['nodes'][' Husband']['nodes'][' HS-grad']['nodes'][' Prof-specialty']['nodes'].items():
        # print(key)

    return root

def predict(tree, dataPoint):
    while 'nodes' in tree and 'label' not in tree['nodes']:
        tempAttr = tree['attribute']
        for node in tree['nodes']:
            if node in dataPoint:
                tree = tree['nodes'][node]
        if 'attribute' in tree:
            if tree['attribute'] == tempAttr:
                tree = {'label' : tree['mostVotes']}
    return tree['label']

def predict_batch(X, y, treeOb):
    y_hat = []
    for x in X:
        yy = label_bool_map(predict(treeOb, x))
        # print(yy)
        y_hat.append(yy)
    uneqC = 0
    for idx, pred in enumerate(y_hat):
        if pred != y[idx]:
            uneqC += 1
    return (len(X) - uneqC) / len(X)

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

    dataX, y = load_data(trainFile)
    X = copy.deepcopy(dataX)
    X['rows'] = X['rows'][:int(len(X['rows']) * trainpct / 100)]
    y = y[:int(len(y) * trainpct / 100)]

    Xt, yt = load_data(testFile)

    target_attribute = "salaryLevel"
    remaining_attributes = set(X['header'])
    remaining_attributes.remove(target_attribute)

    uniqs = get_uniq_values(X)

    root = id3(X, uniqs, remaining_attributes, target_attribute, 1)

    if typeAlg == 'prune':
        validX = copy.deepcopy(dataX)
        validX['rows'] = validX['rows'][int(len(dataX['rows']) * trainpct / 100) : int(len(dataX['rows']) * trainpct / 100) + int(len(dataX['rows']) * validpct / 100)]
        root = id3_prune(root, validX['rows'])

    # t1 = predict_batch(X['rows'], y, root)
    # print("Training set accuracy: " + str(t1))
    # t2 = predict_batch(Xt['rows'], yt, root)
    # print("Testing set accuracy: " + str(t2))

if __name__ == "__main__":
    main()
