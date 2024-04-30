import random

# Generate 20 random points
points = [(random.uniform(-5000, 5000), random.uniform(-5000, 5000)) for _ in range(500)]


for p in points:
    print(f"({p[0]}, {p[1]})")