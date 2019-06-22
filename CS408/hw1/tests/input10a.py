import os, sys

up1 = os.path.abspath('..')
sys.path.insert(0, up1)

from nnc import *

runner("input29.txt")

try:
    with open("output.txt") as fileobject:
        for line in fileobject:
            print(line)
except:
    print("TEST FAILED")
