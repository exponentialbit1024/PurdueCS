from torchvision import datasets, transforms
from NeuralNetwork import NeuralNetwork
import torch
from torch.autograd import Variable
import torch.nn.functional as F
import numpy as np
from matplotlib import pyplot as plt
import pickle

class MyImg2Num:

    def __init__(self, fromFile = False):
        self.train_loader = torch.utils.data.DataLoader(datasets.MNIST('data', train=True, download=True, transform=transforms.ToTensor()),batch_size=600, shuffle=True)
        self.test_loader = torch.utils.data.DataLoader(datasets.MNIST('data', train=False, download=False, transform=transforms.ToTensor()), batch_size=600, shuffle=True)
        if not fromFile:
            self.model = NeuralNetwork((784, 32, 10))
            # self.model = NeuralNetwork((2, 2, 2))
        else:
            pickle_in = open("myimagenn.pkl", "rb")
            self.model = pickle.load(pickle_in)
            pickle_in.close()
        self.max_epochs = 10

    def __oneHot(self, target):
        return np.eye(10, dtype='uint8')[target]
        # return np.eye(2, dtype='uint8')[target]

    def train(self):
        all_mse = []
        for epoch in range(self.max_epochs):
            print("epoch", epoch)
            epoch_mse = []
            for data, target in self.train_loader:
                oneDX = data.resize_(600, 784)
                oneDY = torch.FloatTensor(self.__oneHot(target)).resize_(600, 10)
                y_pred = self.model.forward(oneDX)
                mse = F.mse_loss(Variable(y_pred), Variable(oneDY))
                epoch_mse.append(mse)
                self.model.backward(oneDY)
                self.model.updateParams(0.5)
            all_mse.append(sum(epoch_mse) / len(epoch_mse))
        print("train_err", all_mse)
        modelFile = open("myimagenn.pkl", "wb")
        pickle.dump(self.model, modelFile)
        modelFile.close()

    def __evaluate(self):
        all_mse = []
        for epoch in range(10):
            epoch_mse = []
            for data, target in self.test_loader:
                oneDX = data.resize_(600, 784)
                oneDY = torch.FloatTensor(self.__oneHot(target)).resize_(600, 10)
                y_pred = self.model.forward(oneDX)
                mse = F.mse_loss(Variable(y_pred), Variable(oneDY))
                tyt = oneDY.numpy()
                tyy = y_pred.numpy()
                eqn = 0
                for j in range(len(tyy)):
                    if list(tyy[j]).index(max(tyy[j])) == list(tyt[j]).index(max(tyt[j])):
                        eqn+=1
                # print(eqn / 600, mse.numpy()[0])
                # print(oneDX[0], oneDY[0], y_pred[0])
                # input("")
                epoch_mse.append(mse)
            all_mse.append(sum(epoch_mse) / (len(epoch_mse) * len(all_mse)))
        print("eval_err", all_mse)

    def forward(self, img):
        imgSize = img.size()
        nImg = img.resize_(1, imgSize[2] * imgSize[3])
        y_pred = self.model.forward(img)
        print(list(y_pred[0]).index(max(list(y_pred[0]))))

if __name__ == '__main__':
    # nn = MyImg2Num(fromFile = False)
    nn = MyImg2Num(fromFile = True)
    # nn.train()
    # nn.evaluate()
    test_loader = torch.utils.data.DataLoader(datasets.MNIST('data', train=False, download=False, transform=transforms.ToTensor()), batch_size=1, shuffle=True)
    for data, target in test_loader:
        nn.forward(data)
        print(target)
        break
    # nn.model.theta[0][0][0] = 0.15
    # nn.model.theta[0][1][0] = 0.25
    # nn.model.theta[0][0][1] = 0.20
    # nn.model.theta[0][1][1] = 0.30
    # nn.model.theta[0][2][0] = 0.35
    # nn.model.theta[0][2][1] = 0.35
    # #
    # nn.model.theta[1][0][0] = 0.40
    # nn.model.theta[1][1][0] = 0.50
    # nn.model.theta[1][0][1] = 0.45
    # nn.model.theta[1][1][1] = 0.55
    # nn.model.theta[1][2][0] = 0.60
    # nn.model.theta[1][2][1] = 0.60
    #
    # nn.toy_train()
