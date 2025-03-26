def between(bottom: float, num: float, top: float) -> bool:
    return bottom <= num and top >= num

x = float(input())
print(between(25, x, 30) or between(50, x, 55))