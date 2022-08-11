import random
from sys import stdin, stdout


def outln(n):
    stdout.write(str(n))
    stdout.write("\n")


def main():
    n = int(input())
    outln(n)
    for x in range(n, 0, -1):
        outln(x)


if __name__ == "__main__":
    main()
