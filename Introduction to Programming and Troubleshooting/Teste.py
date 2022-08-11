def remove_elementos(l_i,l_b):
    new_list=[]
    for i in range(len(l_b)):
        if l_b[i]==1:
            new_list.append(l_i[i])
    return new_list

def histograma(entrada,saida):
    lista_carateres={}
    fo=open(entrada, "r")
    carateres=[fo.read()]
    for i in range(len(carateres[0])):
        lista_carateres[carateres[0][i]]=lista_carateres.get(carateres[0][i],0)+1
    fo.close()
    fo1=open(saida, "w")
    for i in lista_carateres:
        fo1.write(i)
        fo1.write("|")
        fo1.write("*"*lista_carateres[i])
        fo1.write("\n")
    fo1.close()
    