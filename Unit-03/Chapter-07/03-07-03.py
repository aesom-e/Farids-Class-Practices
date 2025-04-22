k = int(input())

for i in range(k+1):
    for j in range(k+1):
        if not i and not j:
            print("X", end=" ")
        elif not i:
            print(f"{j}", end=" ")
        elif not j:
            print(f"{i}", end=" ")
        else:
            print(f"{(i)*(j)}", end=" ")
    print()