#Vers�o 1
# Pergunta 1
def conta1(texto,letra):
    num=0
    for car in texto.upper():
        if car==letra.upper():
            num+=1
    return num
def conta2(texto,letra):
    num=0
    for car in range(len(texto)):
        if texto[car].upper()==letra.upper():
            num+=1
    return num
"""R: Poder�amos ent�o retirar o range e converter texto para maisc�las dentro do for, sendo que no if teriamos retirar o upper do car e converter a letra dada para mai�sculas e tambem em vez de o num(contador) ser igual a 1 meter a adicionar 1 a cada vez que � encontrada a letra."""

# Pergunta 2
def mdc(l1,l2):
    divisores=[]
    for div_1 in l1:
        if div_1 in l2:
                divisores.append(div_1)
    print(divisores[-1],divisores)

# Pergunta 3
import math
def divide(texto,partes):
    texto_dividido=[]
    comp_partes=math.ceil(len(texto)/partes)
    for i in range(partes-1):
        texto_dividido.append(texto[i*comp_partes:(i+1)*comp_partes])
    texto_dividido.append(texto[(partes-1)*comp_partes:])
    print(texto_dividido)


# Vers�o 2
#Pergunta 1
"""Como texto="iprp" e o comprimento do texto � 4 no ponto de interoga��o vamos ter:
i
pp
rrr
pppp
"""

# Pergunta 2
def divisores(n):
    divisores=[]
    for i in range(1,n+1):
        if n%i==0:
            divisores.append(i)
    return divisores

# Pergunta 3





# Vers�o 3
# Pergunta 1
"""
0
2
4
8
"""

# Pergunta 2
def maiusculas(frase):
    letras_m="ABCDEFGHIJKLMNOPQRSTUVXZ"
    upper=[]
    for car in frase:
        if car in letras_m:
            upper.append(car)
    return upper

# Pergunta 3
def transposta(matriz):
    return[[matriz[j][i] for j in range(len(matriz))] for i in range(len(matriz[0]))] 


            