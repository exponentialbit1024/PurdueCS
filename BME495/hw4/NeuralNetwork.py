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
        self.localGrads = {}
        self.dE_dTheta = {}

    def forward(self, input2d):
        preds = torch.FloatTensor(input2d.size()[0], self.output_dim).zero_()
        # preds = torch.FloatTensor(1, 2).zero_()
        i = 0
        for inp in input2d:
            prediction = self.forward1d(inp)
            preds[i] = prediction
            i += 1
        return preds

    def forward1d(self, inputTensor):
        inp = copy.deepcopy(inputTensor)
        self.localGrads[0] = inp
        for i in range(len(self.theta)):
            layer = self.theta[i]
            inputHat = torch.cat((inp, torch.FloatTensor([1])))
            output = torch.FloatTensor(np.dot(inputHat, layer))
            output = torch.pow((1 + torch.exp(-output)), -1)
            inp = copy.deepcopy(output)
            # print("sig", inp)
            self.localGrads[i + 1] = inp
        return torch.FloatTensor(inp)

    def getLayer(self, layerNum):
        return self.theta[layerNum]

    def backward1d(self, target):
        error = 0
        errors = []
        lDers = []
        lDiffs = []
        e = 0
        for i in reversed(range(len(self.theta))):
            layer = self.theta[i]
            lGrads = self.localGrads[i + 1]
            if i == len(self.theta) - 1:
                error = lGrads - target
                lDiffs.append(error)
                deriv = lGrads * (1 - lGrads)
                error = error * deriv
                error = error.resize_(1, len(error))
                errors.append(error)
                error = error.t() * self.localGrads[i]
                # error = torch.cat((error, torch.zeros(len(error), len(error[0]))))
                # print("fin_error", error)
            else:
                error_sums = []
                for error in errors:
                    error = error * self.theta[i + 1]
                    for row in error:
                        error_sums.append(sum(row))
                error = torch.FloatTensor(error_sums[:-1])
                gradDerivs = lGrads * (1 - lGrads)
                error = error * gradDerivs
                error = error.resize_(1, len(error))
                error = error.t() * self.localGrads[i]
                # print("Lerror", error)
                # error = torch.cat((error, torch.zeros(len(error), len(error[0]))))
            # print("error", error.t())
            # input("")
            errN = error.t()
            errN = torch.cat((errN, torch.zeros(1, len(errN[0]))))
            self.dE_dTheta[i] = errN

    def backward(self, target):
        for tgt in target:
            self.backward1d(tgt)

    def updateParams(self, eta):
        for i in range(len(self.theta)):
            # print("theta_i", self.theta[i], "dedtheta_i", self.dE_dTheta[i])
            # input("")
            self.theta[i] = self.theta[i] - eta * self.dE_dTheta[i]
            # print("updated_theta", self.theta[i])
