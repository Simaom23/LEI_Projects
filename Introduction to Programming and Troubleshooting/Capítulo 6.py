#Ex 6.1
def num_id(lista_idades):
    return len(lista_idades)

#Ex 6.2
def soma(lista_num):
    soma_pares=0
    soma_impares=0
    for i in range(len(lista_num)):
        if(lista_num[i]%2==0):
            soma_pares=soma_pares+lista_num[i]
        else:
            soma_impares=soma_impares+lista_num[i]
    print(soma_pares, soma_impares)
    
#Ex 6.3
def listagem_alternada(lista1,lista2):
    res=[]
    for i in range(len(lista1)):
        res=res+[lista1[i]]+[lista2[i]]
    return res

#Ex 6.4
def menor(num,lista):
    cont=0
    for i in range(len(lista)):
        if(lista[i]<num):
            cont+=1
    return cont

#Ex 6.6
def i_multiplier(n):
    n_multiplied=[]
    soma=0
    return n_multiplied

#Ex 6.8
def roda_90(n):
    m_nova=[]
    l=len(n)-1
    for col in range(len(n[0])):
        aux=[]
        for linha in range(l,-1,-1):
            aux.append(n[linha][col])
        m_nova.append(aux)
    return m_nova
        
#Ex 6.9

#Ex 6.11
def fruta(fruta,peso):
    dicio_fruta=dict()
    for i in range(len(fruta)):
        dicio_fruta[fruta[i]]=peso[i]    
    return dicio_fruta

#Ex 6.12
def fruta_atual(fruta,peso_inicial,stock,preco_compra,preco_venda):
    dicio_fruta=dict()
    lucro=0
    for i in range(len(fruta)):
        dicio_fruta[fruta[i]]=preco_compra[i],peso_inicial[i],stock[i],preco_venda[i]
    for i in dicio_fruta:
        a=dicio_fruta[i]
        lucro=lucro+((a[3]*(a[1]-a[2]))-(a[0]*a[1]))
        print("Lucro da fruta ",i,"=", lucro)
    mais_caro=0
    fruta_mais_cara=0
    for i in dicio_fruta:
        a=dicio_fruta[i]
        preco=a[3]-a[0]
        if(preco>mais_caro):
            mais_caro=preco
            fruta_mais_cara=i
    print("A fruta mais cara é: ",fruta_mais_cara)
    return dicio_fruta

#Ex 6.13
def conversor(ds,dm,m,a):
    dias_semana={1:"Domingo", 2:"Segunda-Feira", 3:"Terça-Feira", 4:"Quarta-Feira", 5:"Quinta-Feria", 6:"Sexta-Feira", 7:"Sábado"}
    meses_ano={1:"Janeiro", 2:"Fevereiro", 3:"Março", 4:"Abril", 5:"Maio", 6:"Junho", 7:"Julho", 8:"Agosto", 9:"Setembro", 10:"Outubro", 11:"Novembro", 12:"Dezembro"}
    for i in dias_semana.keys():
        if(i==ds):
            dias=(dias_semana[i])
    for i in meses_ano.keys():
        if(i==m):
            mes=meses_ano[i]
    print(dias+",",dm,"de",mes,"de",a)


#Ex 6.14
def informacoes(dicio):
    novo_dicio=dict()
    for chave in dicio.keys():
        if(dicio[chave][0] in "m"):
            metabolismo_basal=66+6.3*dicio[chave][3]+12.9+dicio[chave][2]-6.8*dicio[chave][1]
        if(dicio[chave][0]=="f"):
            metabolismo_basal=655+4.3*dicio[chave][3]+4.7+dicio[chave][2]-4.7*dicio[chave][1]
        novo_dicio.setdefault(chave, metabolismo_basal)
    return novo_dicio

#Ex 6.15
import copy
def imc(dicio):
    novo_dicio=copy.deepcopy(dicio)
    for chave in dicio.keys():
        imc=dicio[chave][0]/((dicio[chave][1])**2)
        novo_dicio[chave].append(imc)
    return novo_dicio

#Ex 6.16
def posicoes(texto):
    d=dict()
    vogais="aeiouAEIOU"
    for i in range(len(texto)):
        chave=texto[i]
        if texto[i] in vogais:
            if chave in d:
                d[chave].append(i)
            else:
                d[texto[i]]=[i]
    return d

#Ex 6.17
def invert_dic(dicio):
    novo_dicio={}
    for i in dicio:
        print(i)
        c=dicio[i]
        if c in novo_dicio:
            novo_dicio[c]=novo_dicio[c]+","+i
        else:
            novo_dicio[c]=i
    return novo_dicio
    
#Ex 6.18
def arvore(dicio,irmao1,irmao2):
    cont=0
    tamanho=len(dicio.keys())
    for chave in dicio.keys():
        cont+=1
        if(irmao1 in dicio[chave] and irmao2 in dicio[chave]):
            print("São irmãos!")
            break
        if(cont==tamanho):
            print("Não são irmãos!")
        

#Ex 6.19
def arvore_complexa(gen1,gen2,avo):
    for chave1,filhos in gen1.items():
        if avo==chave1:
            for chave2,valores in gen2.items():
                if chave2 in filhos:
                    print (str(valores).strip('[]'))

#6.20
def netos(gen2,gen1,neto):
    print("O teu avô/avó é o/a:")
    for chave2,netos in gen2.items():
        if neto in netos:
            for chave1,valores in gen1.items():
                if chave2 in valores:
                    print(chave1)
