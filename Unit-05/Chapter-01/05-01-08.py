def getChessSquareColour(x: int, y: int) -> str:
    if x < 0 or x > 7 or y < 0 or y > 7:
        return ""
    if x % 2 - y % 2:
        return "black"
    return "white"