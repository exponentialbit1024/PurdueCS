from torchvision import datasets, transforms
from NeuralNetwork import NeuralNetwork
import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim
import numpy as np
from matplotlib import pyplot as plt
from torch.autograd import Variable
import pickle

class NnImg2Num:

    def __init__(self, fromFile = False):
        self.train_loader = torch.utils.data.DataLoader(datasets.MNIST('data', train=True, download=True, transform=transforms.ToTensor()),batch_size=600, shuffle=False)
        self.max_epochs = 5
        if not fromFile:
            self.model = torch.nn.Sequential(torch.nn.Linear(784, 32), torch.nn.Sigmoid(), torch.nn.Linear(32, 10))
        else:
            pickle_in = open("pyimagenn.pkl", "rb")
            self.model = pickle.load(pickle_in)
            pickle_in.close()
        self.test_loader = torch.utils.data.DataLoader(datasets.MNIST('data', train=False, download=True, transform=transforms.ToTensor()), batch_size=600, shuffle=True)

    def __oneHot(self, target):
        return np.eye(10, dtype='uint8')[target]

    def train(self):
        criterion = nn.MSELoss(size_average=False)
        optimizer = optim.SGD(self.model.parameters(), lr=1e-4)
        all_mse = []
        for epoch in range(self.max_epochs):
            epoch_mse = []
            for data, target in self.train_loader:
                oneDX = data.resize_(600, 784)
                oneDY = torch.FloatTensor(self.__oneHot(target)).resize_(600, 10)
                y_pred = self.model(Variable(oneDX))
                loss = criterion(y_pred, Variable(oneDY))
                # print("loss", loss.data[0])
                epoch_mse.append(loss)
                optimizer.zero_grad()
                loss.backward()
                optimizer.step()
            all_mse.append(sum(epoch_mse) / len(epoch_mse))
        print("train_err", all_mse)
        modelFile = open("pyimagenn.pkl", "wb")
        pickle.dump(self.model, modelFile)
        modelFile.close()

    def forward(self, img):
        imgSize = img.size()
        nImg = img.resize_(1, imgSize[2] * imgSize[3])
        y_pred = self.model(Variable(img))
        print(list(y_pred[0]).index(max(list(y_pred[0]))))

    def evaluate(self):
        criterion = nn.MSELoss(size_average=False)
        optimizer = optim.SGD(self.model.parameters(), lr=1e-4)
        all_mse = []
        for epoch in range(self.max_epochs):
            epoch_mse = []
            for data, target in self.test_loader:
                oneDX = data.resize_(600, 784)
                oneDY = torch.FloatTensor(self.__oneHot(target)).resize_(600, 10)
                y_pred = self.model(Variable(oneDX))
                loss = criterion(y_pred, Variable(oneDY))
                # print("eval_loss", loss.data[0])
                epoch_mse.append(loss)
            all_mse.append(sum(epoch_mse) / len(epoch_mse))
        print("eval_err", all_mse)

if __name__ == '__main__':
    snn = NnImg2Num(fromFile = True)
    # snn.train()
    snn.evaluate()
    test_loader = torch.utils.data.DataLoader(datasets.MNIST('data', train=False, download=False, transform=transforms.ToTensor()), batch_size=1, shuffle=True)
    for data, target in test_loader:
        snn.forward(data)
        print(target)
        break
