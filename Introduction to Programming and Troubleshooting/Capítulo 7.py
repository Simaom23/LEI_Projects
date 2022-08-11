#Ex 7.1
def file_generator(nome_ficheiro, texto):
    conteudo=open(nome_ficheiro, "w")
    conteudo.write(texto)
    conteudo.close()

#Ex 7.2
def ler(nome_ficheiro,pos_inicial,num_caracter):
    f=open(nome_ficheiro, "r")
    f.seek(pos_inicial)
    cont=f.read(num_caracter)
    f.close()
    return cont

#Ex 7.3
def add_file(nome_ficheiro,data):
    f=open(nome_ficheiro, "r+")
    f.seek(0,2)
    f.write("\n")
    f.write(data)
    f.close()

#Ex 7.4
def numeros(ficheiro):
    fd=open(ficheiro, "r")
    lista=list()
    acum=''
    todo=fd.read()
    for c in todo:
        if c.isdigit():
            acum+=c
        elif (acum!=""):
            lista.append(int(acum))
            acum=''
    if acum!="":
        lista.append(int(acum))
    fd.close()
    return lista

#Ex 7.6
def file_copy(o_file,c_file):
    f_o=open(o_file,"r")
    f_c=open(c_file,"w")
    add=f_o.read()
    f_c.write(add)
    f_o.close()
    f_o.close()

#Ex 7.11

    
#Ex 7.12
def dados_pessoais(ficheiro):
    fd=open(ficheiro)
    fdnew=open("novo", "w")
    profissao={102:"Professor", 411:"Advogado", 203:"Estudante"}
    estado={1:"Casado", 2:"Solteiro"}    
    for linha in fd.readlines():
        nome,apelido,idade,cod_prof,cod_civil=linha.strip().split()
        fd.write(nome[0]+apelido[0]+''+idade+''+profissao[int(cod_prof)]+''+estado[int(cod_civil)])
    fd.close()
    fdnew.close()
    
#Ex 7.16
def url():
    special_car="~"
    car=""
    user=""
    fich=open("URLs.txt","r")
    ler=[fich.read()]
    print (range(len(ler[0])))
    for i in range(len(ler[0])):
        if ler[i]==special_car:
            car=special_car
        print(ler[i])
        if car==special_car:
            user=user.append(str(ler[i]))  
    print (user)

import csv
#Ex 7.17
def zoo():
    zoo_dic={}
    fich=open("zoo.csv")
    csv_reader=csv.reader(fich)
    for linha in csv_reader:
        zoo_dic[linha[1]]=zoo_dic.get(linha[1],[])+[linha[0]]
    return zoo_dic



         
            
    
    