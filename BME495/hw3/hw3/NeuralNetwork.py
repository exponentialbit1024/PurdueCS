import torch
import math
import numpy as np
import copy
import random

random.seed(0)

class NeuralNetwork:

    def __init__(self, inputVars):
        self.output_dim = inputVars[len(inputVars) - 1]
        self.theta = {}
        for i in range(len(inputVars) - 1):
            mat = torch.FloatTensor(inputVars[i] + 1, inputVars[i + 1])
            sigma = 1 / math.sqrt(inputVars[i])
            mat.normal_(mean=0, std=sigma)
            self.theta[i] = mat
        self.dE_dTheta = {}
        self.localGrads = []

    def forward(self, inputTensor):
        output = inputTensor.resize_(1, len(inputTensor))
        for i in range(len(self.theta)):
            output = np.dot(output, self.theta[i])[0]
            output = torch.cat(output)
            output = torch.sigmoid(torch.FloatTensor(output))
            self.localGrads.append(output)
        return torch.FloatTensor(output).resize_(1, len(output))

    def getLayer(self, layerNum):
        return self.theta[layerNum]

    def backward(self, target):
        for i in reversed(range(len(self.theta))):
            layer = self.theta[i]
            errors = []
            if i != len(self.theta) - 1:
                for j in range(len(layer)):
                    error = 0.0
                    for neuron in self.theta[i + 1]:
                        for k in range(len(neuron)):
                            error += (self.theta[k] * self.dE_dTheta[j])
                    errors.append(error)
            else:
                for j in range(len(layer)):
                    neuron = layer[j]
                    errors.append(target - self.localGrads[i][j - 1])
            for k in range(len(layer)):
                neuron = layer[k]
                self.dE_dTheta[k] = errors[k] * (self.localGrads[i][k - 1] * (1 - self.localGrads[i][k - 1]))
        # print("prev", self.theta)

    def updateParams(self, eta):
        for key, mat in self.theta.items():
            mat = mat - eta * self.dE_dTheta[key]
            self.theta[key] = mat
