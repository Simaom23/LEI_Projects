from sys import stdin, stdout
import time


def readln():
    return stdin.readline().rstrip()


def outln(n):
    stdout.write(str(n))
    stdout.write("\n")


def countingSort(array, chave, tamanho):
    count = [0] * 10

    for i in range(tamanho):
        elemento = (array[i] // chave) % 10
        count[elemento] += 1

    for i in range(1, 10):
        count[i] = count[i] + count[i - 1]

    tamanhoAux = tamanho - 1
    aux = [0] * tamanho
    while tamanhoAux >= 0:
        i = array[tamanhoAux] // chave
        aux[count[i % 10] - 1] = array[tamanhoAux]
        count[i % 10] -= 1
        tamanhoAux -= 1

    for i in range(0, tamanho):
        array[i] = aux[i]


def radixSort():
    file = readln()
    f = open(file, 'r')
    tamanho = int(f.readline().rstrip())
    array = []
    n = f.readline().rstrip()
    while(n != ''):
        array.append(int(n))
        n = f.readline().rstrip()

    maximo = max(array)
    divide = 1
    start = time.time()
    while(maximo // divide > 0):
        countingSort(array, divide, tamanho)
        divide = divide * 10
    final = time.time() - start
    print("Tempo:", final)
    for i in range(len(array)):
        outln(array[i])


if __name__ == "__main__":
    radixSort()
