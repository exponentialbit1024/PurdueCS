import torch
import math
import numpy as np

class NeuralNetwork:

    def __init__(self, inputVars):
        self.output_dim = inputVars[len(inputVars) - 1]
        self.theta = {}
        for i in range(len(inputVars) - 1):
            mat = torch.FloatTensor(inputVars[i] + 1, inputVars[i + 1])
            sigma = 1 / math.sqrt(inputVars[i])
            mat.normal_(mean=0, std=sigma)
            self.theta[i] = mat

    def forward(self, inputTensor):
        output = inputTensor.resize_(1, len(inputTensor))
        for i in range(len(self.theta)):
            output = np.dot(output, self.theta[i])[0]
            output = np.hstack((output, 1))
            output = torch.sigmoid(torch.FloatTensor(output))
        return torch.FloatTensor(output).resize_(1, len(output))

    def getLayer(self, layerNum):
        return self.theta[layerNum]
