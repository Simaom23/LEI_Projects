# Simão Monteiro
# Nº2019215412

from sys import stdin, stdout
import time


def readln():
    return stdin.readline().rstrip()


def outln(n):
    stdout.write(str(n))
    stdout.write("\n")


def incrementa(tamanho):
    arrayInt = []
    arrayInt.append(1)
    n = 0
    i = 1
    while n < tamanho:
        n = (4**i)+3*(2**(i-1)) + 1
        arrayInt.append(int(n))
        i += 1
    return arrayInt


def improvedShell():
    file = readln()
    f = open(file, 'r')
    tamanho = int(f.readline().rstrip())
    array = []
    n = f.readline().rstrip()
    while(n != ''):
        array.append(int(n))
        n = f.readline().rstrip()

    arrayIntervalo = incrementa(tamanho)
    intervalo = 0
    if(tamanho == len(array)):
        inicio = time.time()
        for x in range(len(arrayIntervalo)-1, -1, -1):
            intervalo = arrayIntervalo[x]
            for i in range(intervalo, tamanho):
                aux = array[i]
                j = i
                while(j >= intervalo and array[j - intervalo] > aux):
                    array[j] = array[j - intervalo]
                    j -= intervalo
                array[j] = aux
        final = time.time() - inicio
        print("Proccessed Time: ", final)
        '''for i in range(len(array)):
            outln(array[i])'''


if __name__ == "__main__":
    improvedShell()
