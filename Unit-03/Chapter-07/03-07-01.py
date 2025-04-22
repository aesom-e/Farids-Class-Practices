"""Prints the fibbonacci sequence up to the twenty-fifth term and an approximation of the golden ratio"""

previous, current = 1, 1
twenty_fourth, twenty_fifth = 0, 0

# Print the first two numbers
print("1\n1")

# range(23) accounts for the two terms already printed
for i in range(23):
    previous, current = current, previous+current
    print(current)

    if i == 21:
        twenty_fourth = current
    elif i == 22:
        twenty_fifth = current
        print(f"The ratio between fib(24) and fib(25) is {twenty_fifth / twenty_fourth}",
               "and approximates the golden ratio")