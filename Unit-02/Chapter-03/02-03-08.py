sides = sorted([float(input()) for _ in range(3)])
print("valid triangle" if sides[0] + sides[1] > sides[2] else "not a valid triangle")