#Ex 9.1 
def resto(n1,n2):
    if(n1<n2):
        return n1
    else:
        return resto(n1-n2,n2)

#Ex 9.2
def expo(v,w):
    if len(v)==1:
        return v[0]*w[0]
    else:
        return v[0]*w[0]+expo(v[1:],w[1:])

#Ex 9.3
def expo_2(x,n):
    if n==1:
        return x
    else:
        if n%2==0:
            return expo_2(x**2,n/2)
        else:
            return expo_2(x**2,(n-1)/2)

#Ex 9.4
def removedup(cadeia):
    if len(cadeia)==1:
        return cadeia
    elif cadeia[0]==cadeia[1]:
        return cadeia[0]+removedup(cadeia[2:])
    else:
        return cadeia[0]+removedup(cadeia[1:])

#Ex 9.5
def include(conj1,conj2):
    if conj1==[]:
        return True
    elif conj1[0] not in conj2:
        return False
    return conj(conj1[1:],conj2)

#Ex 9.6
def intersect(conj1,conj2):
    if conj1==[]:
        return []
    elif conj1[0] in conj2:
        return [conj1[0]]+intersect(conj1[1:],conj2)
    else:
        return intersect(conj1[1:],conj2)
    
