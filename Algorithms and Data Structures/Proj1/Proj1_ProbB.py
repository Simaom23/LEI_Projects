import time
def main():
    n = int(input())
    array = [int(x) for x in input().split()]
    start = time.time()
    array.sort(reverse = True)
    n1 = array[0]
    n2 = array[1]
    print(n1 + n2)
    print("Running Time:", (time.time() - start))

if __name__ == "__main__":
    main()
