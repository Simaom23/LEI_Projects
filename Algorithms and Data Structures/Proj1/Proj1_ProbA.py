import time
def main():
    n = int(input())
    array = [int(x) for x in input().split()]
    start = time.time()
    somaMax = 0
    for i in range(n - 1):
        soma = 0
        for j in range(i + 1, n):
            soma = array[j] + array[i]
            if soma >= somaMax:
                somaMax = soma
    print(somaMax)
    print("Running Time:", (time.time() - start))

if __name__ == "__main__":
    main()
