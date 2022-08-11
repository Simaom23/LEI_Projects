import random
def main():
    n = int(input())
    for i in range(n):
        print("%d "%(random.randint(0, 1000000)), end='')

if __name__ == "__main__":
    main()
