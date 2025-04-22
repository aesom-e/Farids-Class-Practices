import math

k = int(input())

if not (0 < k <= 10):
    raise ValueError(f"Improper k value {k}")

# Ignore the hard coded icon and 3s
icon = "*x* xx* *"
for i in range(k*3):
    for j in range(k*3):
        print(icon[int(i/k)*3 + int(j/k)], end="")
    print()