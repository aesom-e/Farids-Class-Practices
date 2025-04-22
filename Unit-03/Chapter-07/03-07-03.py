"""Prints a multiplication table between 1 and a given number"""

k = int(input())

width = len(str(k*k))
for i in range(k+1):
    for j in range(k+1):
        if not i and not j:
            print("X".rjust(width), end=" ")
        elif not i:
            print(f"{j}".rjust(width), end=" ")
        elif not j:
            print(f"{i}".rjust(width), end=" ")
        else:
            print(f"{i*j}".rjust(width), end=" ")
    print()

# Two liner because why not:
# k = int(input())
# print(''.join([''.join(['X ' if not i and not j else (str(j) if not i else (str(i) if not j else (str(i*j)))) + ' ' for j in range(k+1)]) + '\n' for i in range(k+1)]))