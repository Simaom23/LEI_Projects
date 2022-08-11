import time
def main():
    n = int(input())
    array = [int(x) for x in input().split()]
    start = time.time()
    n1 = 0
    n2 = 0
    for i in range(n):
        if(array[i] >= n1):
            n2 = n1
            n1 = array[i]
        elif (array[i] > n2 and array[i] != n1):
            n2 = array[i]
    print(n1 + n2)
    print("Running Time:", (time.time() - start))

if __name__ == "__main__":
    main()
