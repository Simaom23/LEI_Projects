# Proj 3.1
# Simão Monteiro
# Nº2019215412

from sys import stdin, stdout


def readln():
    return stdin.readline().rstrip()


def outln(n):
    stdout.write(str(n))
    stdout.write("\n")


def hashcode_one(x):
    return (x % 1000000007)


def hashcode(x, y):
    mod = 1000000007
    return (((x % mod) + (y % mod)) % mod)


class Node:
    def __init__(self, hashCode, left, right):
        self.right = right
        self.left = left
        self.key = hashCode


class HashTree:
    def __init__(self):
        self.root = None

    def hash(self, leafs):
        if len(leafs) != 0:
            auxLeafs = []
            for x in range(len(leafs)):
                key = hashcode_one(leafs[x])
                newNode = Node(key, None, None)
                auxLeafs.append(newNode)

            while len(auxLeafs) != 1:
                leafs = auxLeafs
                auxLeafs = []
                x = 0

                while x != len(leafs):
                    if(x != len(leafs) - 1):
                        key = hashcode(leafs[x].key, leafs[x + 1].key)
                        newNode = Node(key, leafs[x], leafs[x + 1])
                        auxLeafs.append(newNode)
                    x += 2

            if len(leafs) != 1:
                self.root = Node(auxLeafs[0].key, leafs[0], leafs[1])

            else:
                self.root = Node(auxLeafs[0].key, None, None)

            return

        else:
            return

    def hashValues(self, root):
        listagem = []
        if root == None:
            return

        aux = []
        aux.append(root)

        while len(aux) != 0:
            node = aux[0]
            del aux[0]
            if node == None:
                continue
            listagem.append(node.key)
            aux.append(node.left)
            aux.append(node.right)

        return listagem


def main():
    transactions = readln()
    hashTable = [int(x) for x in readln().split()]
    tree = HashTree()
    tree.hash(hashTable)
    listagem = tree.hashValues(tree.root)
    for x in listagem:
        outln(x)


if __name__ == "__main__":
    main()
