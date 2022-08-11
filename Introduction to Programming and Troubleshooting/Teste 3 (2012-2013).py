# Versão 1
# Pergunta 2
def referencia(ref,dic):
    new_dic=dict()
    ref_2=ref[0]+ref[1]
    soma=0
    if(ref in dic.keys()):
        for i in dic.keys():
            if(len(ref)==6) and (ref_2 in i):
                soma+=dic[i]
    return soma

# Pergunta 3
def ler_ficheiro(ficheiro):
    dicio={}
    fo=open(ficheiro, "r")
    palavras=fo.read().split()
    for palavra in palavras:
        dicio[palavra]=dicio.get(palavra,0)+1
    fo.close()
    return dicio

# Versão 2
# Pergunta 2
def list_dic(lista):
    dic={}
    for i in lista:
        dic[i]=dic.get(i,0)+1
    return dic

# Pergunta 3
def word_fich(ficheiro,n):
    fo=open(ficheiro, "r")
    palavras=fo.read().split()
    if n>len(palavras)-1:
        print("''")
    else:
        for i in range(1,len(palavras)+1):
            if i==n:
                print(palavras[i-1])
    fo.close()

# Versão 3
# Pergunta 2
def verdadeiros(dicio,nome):
    lista=[]
    if nome not in dicio.keys():
        return None
    else:
        amigos=dicio[nome]
        for amigo in amigos:
            if nome in dicio[amigo]:
                lista.append(amigo)
        return lista
    
# Pegunta 3
def linhas(ficheiro, n):
    fo=open(ficheiro, "r+")
    for i in range(n):
        l_palavras=fo.readline()
       
#Versão 4
# Pergunta 2
def palavras(texto):
    texto1=texto.split()
    print(texto1)
    for i in texto1:
        print
    
    