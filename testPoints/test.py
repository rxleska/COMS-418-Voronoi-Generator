#!/usr/bin/env python

# graph some points and some lines 
# lines are random color and points are blue
# points are in an array of tuples

import matplotlib.pyplot as plt
import random as rand

points = [(2, -3), (-10, 9), (0, 0), (-5, -2), (4, -7)]

# [x1, y1, x2, y2]
lines = [(4, 7.125, -26.8077, 0), (2, 9, -27.2802, -8.19908), (2, 9, -1.61794, 0), (-4.79231, 4.73077, 7.49638, 0), (0, 10.0556, -1.0016, 0), (0, 10.0556, 3.06903, 0), (-5, 4.63636, 3899.82, 0), (-4.79231, 4.73077, 3899.82, 0) ]

xLeft = 0
xRight = 0
yBottom = 0
yTop = 0

for line in lines:
    xLeft = min(xLeft, line[0], line[2])
    xRight = max(xRight, line[0], line[2])
    yBottom = min(yBottom, line[1], line[3])
    yTop = max(yTop, line[1], line[3])

# add some padding
xLeft -= 10
xRight += 10
yBottom -= 10
yTop += 10

print(xLeft, xRight, yBottom, yTop)

xLeft = -37.2802
xRight = 17.49638
yBottom = -18.19908
yTop = 20.0556

# print out the start of each line segment
for line in lines:
    print(line[0], line[1])


# plt.axis([xLeft, xRight, yBottom, yTop])

# for line in lines:
#     # random color
#     plt.plot([line[0], line[2]], [line[1], line[3]], color=(rand.random(), rand.random(), rand.random()))

# for point in points:
#     plt.plot(point[0], point[1], 'bo')

# plt.show()
