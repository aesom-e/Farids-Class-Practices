"""Scales the resolution of an icon up

Every character is enlarged to a block of k*k size
"""

k = int(input("Scaling (k) value: "))

# Check that k is inbounds
if not (0 < k <= 10):
    raise ValueError(f"Improper k value {k} (0 < k <= 10)")

# Ignore the hard coded icon and 3s
icon = "*x* xx* *"
for i in range(k*3):
    for j in range(k*3):
        print(icon[int(i/k)*3 + int(j/k)], end="")
    print()