# Simão Monteiro
# Nº2019215412

from sys import stdin, stdout
import time


def readln():
    return stdin.readline().rstrip()


def outln(n):
    stdout.write(str(n))
    stdout.write("\n")


def divideConquer(array, low, high):
    middle = (low + high) // 2
    if array[middle] < array[low]:
        array[low], array[middle] = array[middle], array[low]

    if array[high] < array[low]:
        array[low], array[high] = array[high], array[low]

    if array[high] < array[middle]:
        array[middle], array[high] = array[high], array[middle]

    array[middle], array[high - 1] = array[high - 1], array[middle]

    i = low
    j = high - 1
    pivot = array[high - 1]
    while(1):

        while array[i] <= pivot and i < j:
            i = i + 1

        while array[j] >= pivot and i < j:
            j = j - 1

        if i < j:
            array[i], array[j] = array[j], array[i]

        else:
            break

    array[i], array[high - 1] = array[high - 1], array[i]

    return i


def quickSort(array, low, high):
    if low < high:
        i = divideConquer(array, low, high)
        quickSort(array, low, i - 1)
        quickSort(array, i + 1, high)


def main():
    array = []
    tamanho = int(readln().rstrip())
    n = readln().rstrip()
    while(n != ''):
        array.append(int(n))
        n = readln().rstrip()
    quickSort(array, 0, tamanho - 1)
    for i in range(len(array)):
        outln(array[i])


if __name__ == "__main__":
    main()
