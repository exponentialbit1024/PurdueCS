from conv import Conv2D
from PIL import Image
from torchvision import transforms, utils
from torch.autograd import Variable
from torchvision.utils import save_image as save
import torch
import uuid
from datetime import datetime
import matplotlib.pyplot as plt
import numpy as np

def save_outputs(output_image, task_name):
    for image in output_image:
        save(image, str(uuid.uuid4()) + "_" + task_name + ".png")

if __name__ == '__main__':
    cat1 = Image.open("cat2.jpg")
    loader = transforms.Compose([transforms.ToTensor()])
    image = Variable(loader(cat1)).data
    #task 1
    conv2d_1 = Conv2D(in_channel=3, o_channel=1, kernel_size=3, stride=1)
    num_op, output_image = conv2d_1.forward(image)
    #num_op, output_image = conv2d_1.scipy_convolve(image)
    print("task 1: ", num_op)
    save_outputs(output_image, "task1")
    #task 2
    conv2d_2 = Conv2D(in_channel=3, o_channel=2, kernel_size=5, stride=1)
    num_op, output_image = conv2d_2.forward(image)
    #num_op, output_image = conv2d_2.scipy_convolve(image)
    print("task 2: ", num_op)
    save_outputs(output_image, "task2")
    #task 3
    conv2d_3 = Conv2D(in_channel=3, o_channel=3, kernel_size=3, stride=2)
    num_op, output_image = conv2d_3.forward(image)
    print("task 3: ", num_op)
    save_outputs(output_image, "task3")

    #part B
    if conv2d_1.set_mode('rand'):
        times = []
        for i in range(11):
            if conv2d_1.set_o_channel(2 ** i):
                start = datetime.now()
                numops, output_image = conv2d_1.forward(image)
                delta = datetime.now()-start
                print(i, 2 ** i, delta)
                times.append(delta)
        np.save("times", times)
        plt.plot(range(11), times)
        plt.show()

    #part C
    if conv2d_2.set_mode('rand'):
        times = []
        for i in range(3, 13, 2):
            if conv2d_2.set_kernel_size(i):
                numops, output_image = conv2d_2.forward(image)
                print(i, numops)
                times.append(numops)
        np.save("ctimes", times)
        plt.plot(range(3, 13, 2), times)
        plt.show()
