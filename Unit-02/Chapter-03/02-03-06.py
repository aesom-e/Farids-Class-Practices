def between(bottom: float, num: float, top: float, inclusive: bool) -> bool:
    if(inclusive):
        return bottom <= num and top >= num
    else:
        return bottom < num and top > num

ranges = sorted([float(input()) for _ in range(2)])
print("between" if between(ranges[0], float(input()), ranges[1], True) else "not between")