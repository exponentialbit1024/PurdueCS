import numpy as np
from torchvision import transforms
import torch
from PIL import Image

class Conv2D:

    def __init__(self, in_channel, o_channel, kernel_size, stride, mode='known'):
        self.in_channel = in_channel
        self.o_channel = o_channel
        self.kernel_size = kernel_size
        self.stride = stride
        self.mode = mode
        self.K1 = np.array([[-1, -1, -1], [0, 0, 0], [1, 1, 1]])
        self.K2 = np.array([[-1, 0, 1], [-1, 0, 1], [-1, 0, 1]])
        self.K3 = np.array([[1, 1, 1], [1, 1, 1], [1, 1, 1]])
        self.K4 = np.array([[-1, -1, -1, -1, -1], [-1, -1, -1, -1, -1], [0, 0, 0, 0, 0], [1, 1, 1, 1, 1], [1, 1, 1, 1, 1]])
        self.K5 = np.array([[-1, -1, 0, 1, 1], [-1, -1, 0, 1, 1], [-1, -1, 0, 1, 1], [-1, -1, 0, 1, 1], [-1, -1, 0, 1, 1]])

    def kernel_selector(self):
        if self.mode == 'known':
            if self.o_channel == 1:
                return [self.K1]
            elif self.o_channel == 2:
                return [self.K4, self.K5]
            elif self.o_channel == 3:
                return [self.K1, self.K2, self.K3]
        elif self.mode == 'rand':
            kernel_list = []
            for i in range(self.o_channel):
                kernel_list.append(np.random.randint(low=-1, high=2, size=(self.kernel_size, self.kernel_size)))
            return kernel_list

    def set_o_channel(self, new_o_channel):
        try:
            new_o_channel = int(new_o_channel)
            self.o_channel = new_o_channel
            return True
        except Exception as e:
            print(e)
            return False
        return False

    def get_o_channel(self):
        return self.o_channel

    def set_mode(self, new_mode):
        if new_mode == 'known' or new_mode == 'rand':
            self.mode = new_mode
            return True
        return False

    def set_kernel_size(self, new_kernel_size):
        try:
            new_kernel_size = int(new_kernel_size)
            self.kernel_size = new_kernel_size
            return True
        except Exception as e:
            print(e)
            return False
        return False

    def convolve(self, image, kernel):
        kernel = np.flipud(np.fliplr(kernel))
        output = np.zeros_like(image)
        image_padded = np.zeros((image.shape[0] +  2 , image.shape[1] +  2))
        image_padded[1:-1, 1:-1] = image
        num_op = 0
        for x in range(image.shape[1]):
            for y in range(1, image.shape[0] - 1):
                try:
                    mult = kernel * image_padded[y: y + self.kernel_size, x : x + self.kernel_size]
                    output[y,x]=mult.sum()
                except:
                    #print(image_padded[y : y + self.kernel_size, x : x + self.kernel_size].shape)
                    pass
                num_op += 2 * self.kernel_size * self.kernel_size
                y += self.stride - 1
            x += self.stride - 1
        return num_op, output

    def forward(self, input_image):
        num_op = 0
        in_channels, width, height = input_image.size()
        outputs = np.zeros((self.o_channel, width, height))
        kernel_list = self.kernel_selector()
        for o in range(self.o_channel):
            output = np.zeros((width, height))
            for c in range(in_channels):
                num_ops, current_convolution = self.convolve(input_image[c], kernel_list[o])
                output += current_convolution
                num_op += num_ops
            outputs[o] = output
        return num_op, torch.from_numpy(outputs)

    def scipy_convolve(self, input_image):
        from scipy.ndimage import convolve
        in_channels, width, height = input_image.size()
        outputs = np.zeros((self.o_channel, width, height))
        kernel_list = self.kernel_selector()
        for o in range(self.o_channel):
            output = np.zeros((width, height))
            for c in range(in_channels):
                output += convolve(input_image[c], kernel_list[o])
            outputs[o] = output
        return 0, torch.from_numpy(outputs)
