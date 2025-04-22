a, b = 1, 1
twenty_fourth, twenty_fifth = 0, 0

# Print the first two numbers
print("1\n1")

for i in range(23):
    a, b = b, a+b
    print(b)

    if i == 21:
        twenty_fourth = b
    elif i == 22:
        twenty_fifth = b
        print(f"The ratio between fib(24) and fib(25) is {twenty_fifth / twenty_fourth} and approximates the golden ratio")