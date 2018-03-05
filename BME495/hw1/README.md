Notes:

1) I use padding for convolution, which might break pre-existing test files, for the reason I'm supplying my own test file where the size of input and convoluted images are the same.
2) I use uuid package for generating random image names, that might also break the code if trying to use save_output function in main.py
3) I have a function inside conv.py that calls scipy convolution, but that is just for base-line checks and not being called in the forward function.
4) When main.py is run, by default it takes in the 1280x720 image of the cat called cat2.jpg, but you can change the source in the main.py
5) I have 2 folders with separate output images in grayscale, total accounting to 12 images as mentioned in the deliverables
6) The graphs for part B and part C have been named respectively.
