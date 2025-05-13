def isOdd(i: float) -> int:
    if int(i) != i:
        return 0
    return i % 2

def isEven(i: float) -> int:
    if int(i) != i:
        return 0
    return not i % 2