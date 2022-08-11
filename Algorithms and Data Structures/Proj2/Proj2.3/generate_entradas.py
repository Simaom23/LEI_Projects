import random
def main():
    n=int(input())
    nomes = []
    file1 = open("nome.txt", "r")
    read = file1.readline()
    while read:
        read = file1.readline().rstrip()
        nomes.append(read)
    del(nomes[len(nomes)-1])
    file1.close()
    for x in range(int((len(nomes)/2) - 1)):
        print("ACRESCENTA",end=' ')
        print(nomes[x],end=' ')
        print("Rua",end=' ')
        print(nomes[random.randint(0,len(nomes)-1)],end=' ')
        print(random.randint(0,9999999))

    '''consultados=[]
    for x in range(2499):
        index = random.randint(0,int((len(nomes)/2) - 1))
        if nomes[index] not in consultados:
            consultados.append(nomes[index])
        else:
            x-=1

    for x in range(int(n*0.9)):
        print("CONSULTA",end=' ')
        print(consultados[random.randint(0,len(consultados)-1)])'''

    for x in range(int(n)):
        print("CONSULTA",end=' ')
        print(nomes[random.randint(0,int((len(nomes)/2)-1))])


if __name__ == "__main__":
    main()
