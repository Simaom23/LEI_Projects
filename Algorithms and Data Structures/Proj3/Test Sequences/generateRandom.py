import random

from sys import stdin, stdout


def outln(n):
    stdout.write(str(n))
    stdout.write("\n")


def main():
    n = int(input())
    outln(n)
    for x in range(n):
        outln(random.randint(0, 10000000))


if __name__ == "__main__":
    main()
