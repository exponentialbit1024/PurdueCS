import torch
import torch.nn as nn
import torchvision
import torchvision.transforms as transforms
from torchvision import datasets, transforms
import torch.optim as optim
import numpy as np
from torch.autograd import Variable
import torch.nn.functional as F

class img2num(nn.Module):

    def __init__(self):
        super(img2num, self).__init__()
        self.relu = nn.ReLU()
        self.conv1 = nn.Conv2d(1, 6, kernel_size=5, stride = 1, padding = 0)
        self.pool1 = nn.MaxPool2d(kernel_size = 2, stride = 2)
        self.conv2 = nn.Conv2d(6, 16, kernel_size = 5, stride = 1, padding = 0)
        self.pool2 = nn.MaxPool2d(kernel_size = 2, stride = 2)
        self.fc1 = nn.Linear(16 * 4 * 4, 120)
        self.fc2 = nn.Linear(120, 84)
        self.fc3 = nn.Linear(84, 10)
        self.train_loader = torch.utils.data.DataLoader(datasets.MNIST('data', train=True, download=True, transform=transforms.ToTensor()),batch_size=600, shuffle=True)
        self.test_loader = torch.utils.data.DataLoader(datasets.MNIST('data', train=False, download=True, transform=transforms.ToTensor()), batch_size=600, shuffle=False)
        self.max_epochs = 10

    def train(self):
        criterion = nn.CrossEntropyLoss()
        optimizer = optim.SGD(self.parameters(), lr=0.001)
        all_mse = []
        for epoch in range(self.max_epochs):
            epoch_mse = []
            for data, target in self.train_loader:
                data, target = Variable(data), Variable(target)
                optimizer.zero_grad()
                output = self.forward(data)
                loss = criterion(output, target)
                # print("loss", loss.data[0])
                epoch_mse.append(loss)
                loss.backward()
                optimizer.step()
            all_mse.append(sum(epoch_mse) / len(epoch_mse))
        print("train_err", all_mse)

    def forward(self, img):
        x = self.relu(self.conv1(img))
        x = self.pool1(x)
        x = self.relu(self.conv2(x))
        x = self.pool2(x)
        x = x.view(-1, 16 * 4 * 4)
        x = self.relu(self.fc1(x))
        x = self.relu(self.fc2(x))
        x = self.fc3(x)
        return x

    def test(self):
        test_loss = 0
        correct = 0
        for data, target in self.test_loader:
            data, target = Variable(data, volatile=True), Variable(target)
            output = self.forward(data)
            test_loss += F.nll_loss(output, target, size_average=False).data[0] # sum up batch loss
            pred = output.data.max(1, keepdim=True)[1] # get the index of the max log-probability
            correct += pred.eq(target.data.view_as(pred)).cpu().sum()

        test_loss /= len(self.test_loader.dataset)
        print('\nTest set: Average loss: {:.4f}, Accuracy: {}/{} ({:.0f}%)\n'.format(
            test_loss, correct, len(self.test_loader.dataset),
            100. * correct / len(self.test_loader.dataset)))

if __name__ == '__main__':
    nn2num = img2num()
    nn2num.train()
    nn2num.test()
