sentence = input()
word = input()
space = int(input())
print(f"{sentence[:space+1]}{word}{sentence[space:]}")