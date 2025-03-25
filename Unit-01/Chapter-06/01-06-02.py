import math

x = sorted([int(input()) for _ in range(5)])
print(f"Minimum: {x[0]}")
print(f"Maximum: {x[4]}")
print(f"Average: {sum(x) / len(x)}")
print(f"Cubic value of the minimum: {x[0] * x[0] * x[0]}")
print(f"Square root of the absolute value of the maximum: {math.sqrt(abs(x[4]))}")