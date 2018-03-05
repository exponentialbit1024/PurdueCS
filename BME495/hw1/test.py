from conv import Conv2D
from PIL import Image
from torchvision import transforms, utils
from torch.autograd import Variable
from torchvision.utils import save_image as save
import torch
import uuid
import matplotlib.pyplot as plt
import numpy as np

def save_outputs(output_image, task_name):
     for image in output_image:
         save(image, str(uuid.uuid4()) + "_" + task_name + ".png")

if __name__ == '__main__':
    checkerIm = Image.open("checkert1.jpg")
    cat = Image.open("cat2.jpg")
    loader = transforms.Compose([transforms.ToTensor()])
    checkerTensor = Variable(loader(checkerIm)).data
    _, ch_width, ch_height = checkerTensor.size()
    catTensor = Variable(loader(cat)).data
    _, c_width, c_height = catTensor.size()

    #test 1 - task 1
    conv2d_1 = Conv2D(in_channel=3, o_channel=1, kernel_size=3, stride=1)
    num_op, output_image = conv2d_1.forward(checkerTensor)
    _, width, height = output_image.size()

    assert width == ch_width and height == ch_height
    print("passed task 1a")
    save_outputs(output_image, "task1")

    num_op, output_image = conv2d_1.forward(catTensor)
    _, width, height = output_image.size()

    assert width == c_width and height == c_height
    print("passed task 1b")
    print("passed task 1")
    save_outputs(output_image, "task1")

    #test 2 - task 2
    conv2d_2 = Conv2D(in_channel=3, o_channel=2, kernel_size=5, stride=1)
    num_op, output_image = conv2d_2.forward(checkerTensor)
    _, width, height = output_image.size()

    assert width == ch_width and height == ch_height
    print("passed task 2a")
    save_outputs(output_image, "task2")

    num_op, output_image = conv2d_2.forward(catTensor)
    _, width, height = output_image.size()

    assert width == c_width and height == c_height
    print("passed task 2b")
    print("passed task 2")
    save_outputs(output_image, "task2")

    #test 3 - task 3
    conv2d_3 = Conv2D(in_channel=3, o_channel=3, kernel_size=3, stride=2)
    num_op, output_image = conv2d_3.forward(checkerTensor)
    _, width, height = output_image.size()

    assert width == ch_width and height == ch_height
    print("passed task 3a")
    save_outputs(output_image, "task3")

    num_op, output_image = conv2d_3.forward(catTensor)
    _, width, height = output_image.size()

    assert width == c_width and height == c_height
    print("passed task 3b")
    print("passed task 3")
    save_outputs(output_images, "task3")

    #part B
    if conv2d_1.set_mode('rand'):
         times = []
         for i in range(11):
             if conv2d_1.set_o_channel(2 ** i):
                 start = datetime.now()
                 numops, output_image = conv2d_1.forward(catTensor)
                 delta = datetime.now()-start
                 print(i, 2 ** i, delta)
                 times.append(delta)
         np.save("times", times)
         plt.plot(range(11), times)
         plt.savefig("partb_graph.png")

    #part C
    if conv2d_2.set_mode('rand'):
        times = []
        for i in range(3, 13, 2):
            if conv2d_2.set_kernel_size(i):
                numops, output_image = conv2d_2.forward(catTensor)
                print(i, numops)
                times.append(numops)
        np.save("ctimes", times)
        plt.plot(range(3, 13, 2), times)
        plt.savefig("partc_graph.png")

