import random


def main():
    n = int(input())
    print(n)

    for x in range(n):
        value = random.randint(0, 9999)
        dia = random.randint(1, 31)
        mes = random.randint(1, 12)
        ano = random.randint(2007, 2100)
        if dia < 10:
            dia = "0"+str(dia)
        if mes < 10:
            mes = "0"+str(mes)
        final = str(value)+str(dia)+str(mes)+str(ano)
        print(final, end=" ")
    print()


if __name__ == '__main__':
    main()
