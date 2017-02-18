#!/usr/bin/python
import sys
import os

#print (str(sys.argv[1]))

for file in os.listdir("."):
    if file.endswith("StreamUsers"):
        print(file)