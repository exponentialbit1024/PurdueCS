import os, sys

up1 = os.path.abspath('..')
sys.path.insert(0, up1)

from nnc import *
import time

start = time.time()

runner("input29.txt")

print(time.time() - start)
