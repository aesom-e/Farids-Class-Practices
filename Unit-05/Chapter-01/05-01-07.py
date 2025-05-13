def writeToFile(name: str, text: str) -> None:
    with open(name, "w") as f:
        f.write(text)

def appendToFile(name: str, text: str) -> None:
    with open(name, "a") as f:
        f.write(text)

def readFromFile(name: str) -> str:
    with open(name, "r") as f:
        contents = f.read()
    return contents