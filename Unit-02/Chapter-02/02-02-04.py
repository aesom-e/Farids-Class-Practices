def between(bottom: float, num: float, top: float, inclusive: bool) -> bool:
    if(inclusive):
        return bottom <= num and top >= num
    else:
        return bottom < num and top > num

x = float(input())
print(between(25, x, 30, False) or between(50, x, 55, True))