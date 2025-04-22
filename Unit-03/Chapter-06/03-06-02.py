msg = input()
keys = [int(input()) for _ in range(3)]

new_msg = ""

for i in range(len(msg)):
    if msg[i] == " ":
        new_msg += " "
        continue
    if msg[i].isupper():
        new_msg += chr((ord(msg[i]) - ord('A') + keys[i%3]) % 26 + ord('A'))
    elif msg[i].islower():
        new_msg += chr((ord(msg[i]) - ord('a') + keys[i%3]) % 26 + ord('a'))
    elif msg[i].isdigit():
        new_msg += chr((ord(msg[i]) - ord('0') + keys[i%3]) % 10 + ord('0'))
    else:
        raise ValueError(f"{msg[i]} is not a letter nor a digit")

print(new_msg)