sides = [float(input()) for _ in range(3)]
print("valid triangle" if sum(sides) == 180 and sorted(sides)[0] > 0 else "not a valid triangle")