#!/usr/bin/env python

# graph some points and some lines 
# lines are red and points are blue
# points are in an array of tuples

import matplotlib.pyplot as plt

points = [(2, -3), (-10, 9), (0, 0), (-5, -2), (4, -7)]

lines = [(-5,5.25,4.73,-2.9), (0,10.0556, 4.73, 0), (0, 10.0556, 4.74, -9.05), (-5,5.25,4.73,-5), (2,9,-20,2), (4,7.125,-20,-4.14286)]

xLeft = -30
xRight = 30
yBottom = -30
yTop = 30

plt.axis([xLeft, xRight, yBottom, yTop])

for line in lines:
    plt.plot([line[0], line[2]], [line[1], line[3]], 'r')

for point in points:
    plt.plot(point[0], point[1], 'bo')

plt.show()
