"""Simulates a fight between two people with different healths and different strength

This script randomly alternates turns between John and Joe where John has more health
and lower strength, and Joe has less health and higher strength.
"""

import random

john, joe = 750, 250

def hit(name: str) -> None:
    """
    Simulates a hit in the fight

    Args:
        name (str): The name of the victim
    """

    global john, joe
    if name == "John":
        hit = random.randint(60, 90)
        john -= hit
        if john < 0:
            john = 0
        print(f"Joe hits for {hit}. John now has {john} health")
    elif name == "Joe":
        hit = random.randint(20, 30)
        joe -= hit
        if joe < 0:
            joe = 0
        print(f"John hits for {hit}. Joe now has {joe} health")
    else:
        raise ValueError(f"No person named {name}")

rounds = 1
while 1:
    print(f"\nRound {rounds}")
    rounds += 1

    # Check if John goes first
    if random.randint(0, 1):
        hit("Joe")
        if joe <= 0:
            print("John wins")
            break
        hit("John")
        if john <= 0:
            print("Joe wins")
            break
    else:
        hit("John")
        if john <= 0:
            print("Joe wins")
            break
        hit("Joe")
        if joe <= 0:
            print("John wins")
            break