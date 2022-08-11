# Proj 3.2
# Simão Monteiro
# Nº2019215412

from sys import stdin, stdout


def readln():
    return stdin.readline().rstrip()


class Utente:
    def __init__(self, nome, vacina, data):
        self.nome = nome
        self.vacData = [[vacina, data]]


class Leaf:
    def __init__(self, utente):
        self.right = None
        self.left = None
        self.utente = utente

    # Adicionar à Árvore

    def add(self, utente):
        if self.utente is not None:
            if utente.nome < self.utente.nome:
                if self.left is None:
                    self.left = Leaf(utente)
                    return ("NOVO UTENTE CRIADO")
                else:
                    return self.left.add(utente)

            elif utente.nome > self.utente.nome:
                if self.right is None:
                    self.right = Leaf(utente)
                    return ("NOVO UTENTE CRIADO")
                else:
                    return self.right.add(utente)

            else:
                x = True
                for n in range(len(self.utente.vacData)):
                    if utente.vacData[0][0] == self.utente.vacData[n][0]:
                        self.utente.vacData[n][1] = utente.vacData[0][1]
                        x = False
                        return ("VACINA ATUALIZADA")

                if x:
                    self.utente.vacData.extend(utente.vacData)
                    self.utente.vacData.sort(key=lambda vacina: vacina[0])
                    return ("NOVA VACINA INSERIDA")

        else:
            self.utente = utente
            return ("NOVO UTENTE CRIADO")

    # Consultar a Árvore

    def consult(self, nome):
        if self.utente is not None:
            if nome < self.utente.nome:
                if self.left is None:
                    return ("NAO ENCONTRADO")
                else:
                    return self.left.consult(nome)

            elif nome > self.utente.nome:
                if self.right is None:
                    return ("NAO ENCONTRADO")
                else:
                    return self.right.consult(nome)
            else:
                return self.utente
        else:
            return ("NAO ENCONTRADO")

    # Listar a Árvore

    def listing(self, listagem):
        if self.utente is not None:
            if self.left is not None:
                self.left.listing(listagem)
            listagem.append(self.utente)
            if self.right is not None:
                self.right.listing(listagem)

    # Eliminar a Árvore

    def delete(self):
        if self.left is not None:
            self.left.delete()
        self.utente = None
        if self.right is not None:
            self.right.delete()
# Função main


def main():
    tree = Leaf(None)
    entrada = []
    line = readln().split()
    while line[0] != "FIM":
        entrada.append(line)
        line = readln().split()
    for i in range(len(entrada)):
        if entrada[i][0] == "ACRESCENTA":
            newUtente = Utente(entrada[i][1], entrada[i][2], entrada[i][3])
            novo = tree.add(newUtente)
            print(novo)
        elif entrada[i][0] == "APAGA":
            tree.delete()
            print("LISTAGEM DE NOMES APAGADA")
        elif entrada[i][0] == "LISTAGEM":
            lista = []
            tree.listing(lista)
            for x in range(len(lista)):
                print(lista[x].nome, end=" ")
                for n in range(len(lista[x].vacData)):
                    if n != len(lista)-1:
                        print(lista[x].vacData[n]
                              [0], lista[x].vacData[n][1], end=" ")
                    else:
                        print(lista[x].vacData[n][0],
                              lista[x].vacData[n][1], end="")
                print()
            print("FIM")
        elif entrada[i][0] == "CONSULTA":
            consultado = tree.consult(entrada[i][1])
            if type(consultado) is str:
                print(consultado)
            else:
                print(consultado.nome, end=" ")
                for n in range(len(consultado.vacData)):
                    if n != len(consultado.vacData)-1:
                        print(consultado.vacData[n][0],
                              consultado.vacData[n][1], end=" ")
                    else:
                        print(consultado.vacData[n][0],
                              consultado.vacData[n][1])
                print("FIM")
        else:
            print("INPUT MAL INTRODUZIDO")


if __name__ == "__main__":
    main()
