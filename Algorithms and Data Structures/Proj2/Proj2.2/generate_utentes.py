import random


def main():
    n = int(input())
    nomes = ["João", "António", "Simão", "Adriana",
             "Joana", "Maria", "Isabel", "Aparicio", "André", "Josefina", "Alexandre",
             "Madalena", "Bernardo", "Henrique", "Matilde", "Carlos",
             "Carolina", "Marta", "Tomás"]
    doencas = ["Covid", "HepatiteTóxica", "Enfarte", "Cancro",
               "Leishnein", "Prolapse", "Polio", "Tuberculose", "Anemia"]

    for x in range(int(n * 0.1)):
        print("ACRESCENTA", end=" ")
        print(nomes[random.randint(0, 18)], end=" ")
        print(doencas[random.randint(0, 8)], end=" ")
        print("%d/%d/%d" % (random.randint(1, 31),
              random.randint(1, 12), random.randint(2021, 2100)))
    for x in range(int(n * 0.9)):
        print("CONSULTA", end=" ")
        print(nomes[random.randint(0, 18)])
if __name__ == "__main__":
    main()
