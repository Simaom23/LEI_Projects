#Ex 2.1
def verify_list(lista,n):
    a=0
    for i in range(len(lista)):
        if lista[i]==n:
            a=i
    if a!=0:
        print("O elemento ocorreu na lista por último no índice %d!"%a)
    if a==0:
        print(-1)

#Ex 2.2
def rotate_right(lista):
    lista=lista[-1:]+lista[:len(lista)-1]
    return lista

#Ex 2.3
def rotate_left(lista):
    lista=lista[1:]+lista[:1]
    return lista

#Ex 2.4
def rotate_complex(lista,posicoes,direcao):
    if direcao=="direita" or direcao=="Direita" or direcao=="d" or direcao=="D":
        lista=lista[-posicoes:]+lista[:-posicoes]
    elif direcao=="esquerda" or direcao=="Esquerda" or direcao=="e" or direcao=="E":
        lista=lista[posicoes:]+lista[:posicoes]
    return lista
# Está a frente de cada linha de código o que é suposto estar a fazer
def palindromo(lista):
    lr=""   # Variavel lr passa a ter uma string vazia
    rl=""   # Variavel rl passa a ter uma string vazia
    for i in range (len(lista)):    # Ciclo para percorrer os indices da lista(diferentes palavras inseridas)
        for j in range(len(lista[i])):  #Ciclo para percorrer os carateres de cada palavra
            er+=lista[i][j] #Incrementa os carateres das duas palavras numa so palavra da esquerda para a direita
            re+=lista[len(lista)-i-1][len(lista[i])-j-1]    #Incrementa os carateres das duas palavras numa so palavra da direita para esquerda
    if(er==re): #Testa se as palavras são iguais
        return True
    else:
        return False

def formatar(cadeia):
    formatado="" # Variavel formatado passa a ter uma string vazia
    for i in range(len(cadeia)): # Ciclo para percorrer os indices da lista(diferentes palavras inseridas)
        for j in range(len(cadeia[i])): #Ciclo para percorrer os carateres de cada palavra
            if(j==0):   #Testa se j==0 o que quer dizer que se for o primeiro carater da palavra faz em baixo
                formatado+=cadeia[i][j].upper() #Colocar em maiúscula e incrementar a variavel formatado
            else:
                formatado+=cadeia[i][j] #Incrementa os carateres a variavel formatado 
            if (j==(len(cadeia[i])-1)): #Testa se j==ùltimo carater da palavra adicionar espaco à variavel formatado
                formatado+=" "    
    return formatado #No fim a primeira letra das palavras estarão em maiúsculas e formatado será uma string ou uma frase criada a partir da lista de palavras inseridas

def pergunta_2(cad1,cad2): 
    print("mensagem codificada: "+cad1) 
    print("chave: "+cad2) 
    a=cad2[2] 
    e=cad2[6] 
    i=cad2[10] 
    o=cad2[14] 
    u=cad2[18]
    cad_d=""
    for m in range (len(cad1)): 
        if cad1[m]==a: 
            cad_d+="a" 
        elif cad1[m]==e: 
            cad_d+="e" 
        elif cad1[m]==i: 
            cad_d+="i" 
        elif cad1[m]==o: 
            cad_d+="o" 
        elif cad1[m]==u: 
            cad_d+="u" 
        else:
            cad_d+=cad1[m]
    print("mensagem descodifica: " + cad_d) 
    soma=int(a)+int(e)+int(i)+int(o)+int(u) 
    return("soma dos codigos: " + str(soma))

def fds(palavra,cad):
    pos=0
    cad=cad.replace(".", "")
    cad=cad.replace(",", "")
    cad=cad.replace("?", "")
    cad=cad.replace("!", "")
    cad=cad.lower()
    cad=cad.split(" ")
    palavra=palavra.lower()
    print(palavra,cad)
    if palavra in cad:
        print("A palavra encontrasse na cadeia. Encontrasse nas posição/ões:", end=" ")
    else:
        print("A palavra não se encontra nesta cadeia.")
    for i in range(len(cad)):
        if(cad[i]==palavra):
            pos=i
            print(pos, end=" ")
            
def somat(y,z):
    i=1
    soma=0
    while(i<=100):
        soma+=((1+y*z)/(1+y))
        i+=1
    soma*=(y/(1+y))
    return soma

def lifetime(lista):
    k=len(lista)/3
    l_s=[[]]
    d=0
    n=0
    p_d=0
    p_n=0
    for i in range(len(lista)-1):
        if (i>k and i<(k*2)):
            l_s[d][1]=lista[i]
            d+=1
        elif (i>(k*2)):
            l_s[n][2]=lista[i]
            n+=1
        else:
            l_s[i][0]=lista[i]
    for i in range(len(l_s)-1):
        l_s[i][3]=(l_s[i][1]/l_s[i][2])
        l_s[i][3]=1-l_s[i][3]
        
    return l_s
    


def elemen(x):
    lista=[6,12,21,27,32,39,43,89,261,263,270,311,1,1,1,1,1,1,2,1,1,1,1,1,23,22,21,20,19,18,17,14,8,7,6,4]
    lista2=[]
    for i in range(len(lista)):
        if lista[i]==x:
            lista2.append(i)
    return lista2
    