from neural_network import NeuralNetwork
import torch
import numpy as np
import math

class AND:

    def __init__(self):
        self.model = NeuralNetwork((2, 1))
        layer0 = self.model.getLayer(0)
        layer0[0] = 1
        layer0[1] = 0.5
        layer0[2] = 1

    def __call__(self, x, y):
        return self.forward(x, y)

    def sigmoid(self, x):
        return 1 / (1 + math.exp(-x))

    def forward(self, x, y):
        self.input = torch.FloatTensor([x, y, -0.5])
        y = self.model.forward(self.input)
        y = torch.sum(y)
        y = self.sigmoid(y)
        y -= 0.3
        return y > 0.5

class OR:

    def __init__(self):
        self.model = NeuralNetwork((2, 1))
        layer0 = self.model.getLayer(0)
        layer0[0] = 1
        layer0[1] = 1
        layer0[2] = 1

    def __call__(self, x, y):
        return self.forward(x, y)

    def sigmoid(self, x):
        return 1 / (1 + math.exp(-x))

    def forward(self, x, y):
        self.input = torch.FloatTensor([x, y, 0.5])
        y = self.model.forward(self.input)
        y = torch.sum(y)
        y = self.sigmoid(y)
        y -= 0.3
        return y > 0.5

class NOT:

    def __init__(self):
        self.model = NeuralNetwork((1, 1))
        layer0 = self.model.getLayer(0)
        layer0[0] = -8
        layer0[1] = 4

    def __call__(self, x):
        return self.forward(x)

    def sigmoid(self, x):
        return 1 / (1 + math.exp(-x))

    def forward(self, x):
        self.input = torch.FloatTensor([x, 1])
        y = self.model.forward(self.input)
        y = torch.sum(y)
        y = self.sigmoid(y)
        y -= 0.3
        return y > 0.5

class XOR:

    def __init__(self):
        self.model = NeuralNetwork((2, 2, 1))
        layer0 = self.model.getLayer(0)
        layer0[0][0] = 20
        layer0[0][1] = -20
        layer0[1][0] = -20
        layer0[1][1] = 20
        layer0[2][0] = 10
        layer0[2][1] = 10
        layer1 = self.model.getLayer(1)
        layer1[0] = 10
        layer1[1] = 10

    def __call__(self, x, y):
        return self.forward(x, y)

    def sigmoid(self, x):
        return 1 / (1 + math.exp(-x))

    def forward(self, x, y):
        self.input = torch.FloatTensor([x, y, -1])
        y = self.model.forward(self.input)
        y = torch.sum(y)
        y = self.sigmoid(y)
        y -= 0.3
        return y > 0.5
