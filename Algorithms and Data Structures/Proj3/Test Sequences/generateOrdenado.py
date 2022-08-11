import random

from sys import stdin, stdout


def outln(n):
    stdout.write(str(n))
    stdout.write("\n")


def main():
    n = int(input())
    outln(n)
    array = []
    for x in range(n):
        array.append(x)

    for x in range(int(n*0.05)):
        array[random.randint(0, len(array) - 1)
              ] = array[random.randint(0, len(array) - 1)]

    for x in range(len(array)):
        outln(array[x])


if __name__ == "__main__":
    main()
