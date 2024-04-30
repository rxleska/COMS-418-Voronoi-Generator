#!/usr/bin/env python

# graph some points and some lines 
# lines are random color and points are blue
# points are in an array of tuples

import matplotlib.pyplot as plt
import random as rand
from math import cos,sin

# generate 20 cocircular points with random distributions by generating 20 values between 0 and 2pi then converting to x,y
points = [rand.random()*2*3.14159 for i in range(20)]

# generate 20 random lines by generating 20 random points
lines = []
for point in points:
    lines.append([10*cos(point),10*sin(point)])

# print the points and lines
for line in lines:
    print("(" + line[0].__str__() + "," + line[1].__str__() + ")")