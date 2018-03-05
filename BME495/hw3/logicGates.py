from NeuralNetwork import NeuralNetwork
import torch
import numpy as np
import math
import random

np.random.seed(0)

class AND:

    def __init__(self):
        self.model = NeuralNetwork((2, 1))

    def __call__(self, x, y):
        return self.forward(x, y)

    def sigmoid(self, x):
        return 1 / (1 + math.exp(-x))

    def forward(self, x, y):
        self.input = torch.FloatTensor([x, y, -0.5])
        yh = self.model.forward(self.input)
        yh = torch.sum(yh)
        yh = self.sigmoid(yh)
        yh -= 0.349
        return yh > 0.5

    def train(self):
        for i in range(10000):
            choices = [[1,1],[1,0],[0,1],[0,0]]
            j = random.choice(choices)
            self.forward(j[0], j[1])
            self.model.backward(torch.FloatTensor([int(j[0] and j[1])]))
            self.model.updateParams(0.006)
        return 0

class OR:

    def __init__(self):
        self.model = NeuralNetwork((2, 1))

    def __call__(self, x, y):
        return self.forward(x, y)

    def sigmoid(self, x):
        return 1 / (1 + math.exp(-x))

    def forward(self, x, y):
        x = int(x)
        y = int(y)
        self.input = torch.FloatTensor([x, y, 1])
        yh = self.model.forward(self.input)
        yh = torch.sum(yh)
        yh = self.sigmoid(yh)
        yh -= 0.23
        # print(x,y, yh)
        return yh < 0.5

    def train(self):
        for i in range(50000):
            choices = [[1,1],[1,0],[0,1],[0,0]]
            j = random.choice(choices)
            self.forward(j[0], j[1])
            self.model.backward(torch.FloatTensor([int(j[0] or j[1])]))
            self.model.updateParams(0.005)
        return 0

class NOT:

    def __init__(self):
        self.model = NeuralNetwork((1, 1))

    def __call__(self, x):
        return self.forward(x)

    def sigmoid(self, x):
        return 1 / (1 + math.exp(-x))

    def forward(self, x):
        self.input = torch.FloatTensor([x, -0.5])
        yh = self.model.forward(self.input)
        yh = torch.sum(yh)
        yh = self.sigmoid(yh)
        yh -= 0.3
        return yh < 0.5

    def train(self):
        for i in range(25000):
            choices = [[0],[1]]
            j = random.choice(choices)
            self.forward(j[0])
            self.model.backward(torch.FloatTensor([int(not j[0])]))
            self.model.updateParams(0.05)
        return 0

class XOR:

    def __init__(self):
        self.model = NeuralNetwork((2, 2, 1))

    def __call__(self, x, y):
        return self.forward(x, y, pred=1)

    def sigmoid(self, x):
        return 1 / (1 + math.exp(-x))

    def forward(self, x, y, pred=0):
        self.input = torch.FloatTensor([x, y, 1])
        yh = self.model.forward(self.input)
        yh = torch.sum(yh)
        yh = self.sigmoid(yh)
        yh -= 0.28
        if pred == 1:
            print(x,y, yh)
        return yh > 0.5

    def train(self):
        for i in range(20000):
            choices = [[1,1],[1,0],[0,1],[0,0]]
            j = random.choice(choices)
            self.forward(j[0], j[1])
            self.model.backward(torch.FloatTensor([int(bool(j[0]) != bool(j[1]))]))
            self.model.updateParams(0.008)
        return 0
