# Proj 3.3
# Simão Monteiro
# Nº2019215412

from sys import stdin, stdout


def readln():
    return stdin.readline().rstrip()


class Client:
    def __init__(self, nome, morada, volume):
        self.nome = nome
        self.morada = morada
        self.volume = volume


class Element:
    def __init__(self, cliente):
        self.pointer = None
        self.client = cliente


class List:
    def __init__(self):
        self.root = None

    def addClient(self, cliente):
        if self.root:
            prev = self.root
            while prev.pointer:
                if prev.client.nome != cliente.nome:
                    prev = prev.pointer
                else:
                    return ("CLIENTE JÁ EXISTENTE")
            prev.pointer = Element(cliente)
            return ("NOVO CLIENTE INSERIDO")
        else:
            self.root = Element(cliente)
            return ("NOVO CLIENTE INSERIDO")

    def newVolume(self, nome, volume):
        if self.root:
            prev = self.root
            while prev:
                if prev.client.nome == nome:
                    prev.client.volume += volume
                    if prev != self.root:
                        auxPointer = prev.pointer
                        prev.pointer = self.root
                        self.root = prev
                        last.pointer = auxPointer
                    return ("AQUISICAO INSERIDA")
                last = prev
                prev = prev.pointer
            return ("CLIENTE NÃO REGISTADO")
        else:
            return ("CLIENTE NÃO REGISTADO")

    def consult(self, nome):
        if self.root:
            prev = self.root
            while prev:
                if prev.client.nome == nome:
                    if prev != self.root:
                        auxPointer = prev.pointer
                        prev.pointer = self.root
                        self.root = prev
                        last.pointer = auxPointer
                    return (self.root.client)
                last = prev
                prev = prev.pointer
            return ("CLIENTE NÃO REGISTADO")
        else:
            return ("CLIENTE NÃO REGISTADO")

    def listing(self):
        listagem = []
        if self.root:
            prev = self.root
            while prev:
                listagem.append(
                    [prev.client.nome, prev.client.morada, prev.client.volume])
                prev = prev.pointer
        return listagem

    def delete(self):
        if self.root:
            prev = self.root
            while prev:
                aux = prev.pointer
                del prev.client
                del prev.pointer
                prev = aux
        self.root = None


def main():
    lista = List()
    entrada = []
    line = readln().split()
    while line[0] != "FIM":
        entrada.append(line)
        line = readln().split()
    for i in range(len(entrada)):
        if entrada[i][0] == "CLIENTE":
            newClient = Client(entrada[i][1],
                               entrada[i][2] + " " + entrada[i][3],
                               int(entrada[i][4]))
            novo = lista.addClient(newClient)
            print(novo)
        elif entrada[i][0] == "CONSULTA":
            consultado = lista.consult(entrada[i][1])
            if type(consultado) is str:
                print(consultado)
            else:
                print(consultado.nome, consultado.morada, consultado.volume)
                print("FIM")
        elif entrada[i][0] == "AQUISICAO":
            novoVolume = lista.newVolume(entrada[i][1], int(entrada[i][2]))
            print(novoVolume)
        elif entrada[i][0] == "APAGA":
            lista.delete()
            print("LISTAGEM DE CLIENTES APAGADA")
        elif entrada[i][0] == "LISTAGEM":
            listagem = lista.listing()
            listagem.sort(key=lambda nome: nome[0])
            for x in range(len(listagem)):
                print(listagem[x][0], listagem[x][1], listagem[x][2])
            print("FIM")
        else:
            print("INPUT MAL INTRODUZIDO")


if __name__ == "__main__":
    main()
