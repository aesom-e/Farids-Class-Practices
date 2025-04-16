msg = input("Message: ")
key = int(input("Key: "))

msg = ''.join([" " if c == " " else chr((ord(c) - 65 + key) % 26 + 65) for c in msg])

print(msg)