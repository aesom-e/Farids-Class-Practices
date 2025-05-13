def fizzBuzz(upTo: int) -> None:
    for i in range(1, upTo+1):
        if not i % 3 and not i % 5:
            print("FizzBuzz", end=" ")
        elif not i % 3:
            print("Fizz", end=" ")
        elif not i % 5:
            print("Buzz", end=" ")
        else:
            print(i, end=" ")

fizzBuzz(int(input()))