import numpy as np

# Seed for reproducibility
np.random.seed(0)

# Generate 100 random points with x and y values ranging from -100 to 100
x_values = np.random.uniform(-1000, 1000, 100)
y_values = np.random.uniform(-1000, 1000, 100)

# Combine into a list of tuples
points = list(zip(x_values, y_values))

points.sort()

for point in points:
    print(point)