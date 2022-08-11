import math as m
import random as r
import turtle as t

#Ex 5.1
def crescente(n1,n2,n3):
    crescente=(n1,n2,n3)
    if(n1>n2):
        crescente=(n2,n1,n3)
    if(n1>n3):
        crescente=(n2,n3,n1)
    if(n2>n3):
        crescente=(n3,n2,n1)
    print(crescente)
    
#Ex 5.2
def viagem(estrada):
    if(estrada=="a1"):
        price=0.15*120+6.52
    elif(estrada=="a20"):
        price=0.12*120+15.2
    elif(estrada=="a21"):
        price=0.10*120+5.75 
    return price    
        
#Ex 5.3 
def roubo(ven_bruto):
    ven_liq=(ven_bruto-((ven_bruto*0.25)+(ven_bruto*0.05)+(ven_bruto*0.10)))
    print("Recebi: ", ven_liq)

#Ex 5.5
def ciclo():
    for i in range(20,-1,-2):
        print("i =",i)
      
#Ex 5.4
def nota_final(t1,t2,t3,t4,exam):
    nota=0.075*(t1+t2+t3+t4)+0.7*exam
    if nota>=14:
        print("Aprovado")
    elif nota<7:
        print("Reprovado")
    else:
        print("Oral")

#Ex 5.7
def amigas(palavra1,palavra2):
    car_1=len(palavra1)
    car_2=len(palavra2)
    cont=0
    if car_1==car_2:
        for i in range (car_1):
            if palavra1[i]==palavra2[i]:
                cont+=1
        if (((cont/car_1)*100)>90):
            print("Amigas")
        else:
            print("Não amigas")
    else:
        print("Inimigas")
        
#Ex 5.8
def minimo_divisor(num):
    for i in range(2,num+1):
        if num%i==0:
            return i
        
def primo(num):
    if minimo_divisor(num)==num:
        print("São primos")
    else:
        print("Nao são primos")

#Ex 5.9
def dado(nlan):
    cont=0
    npar=0
    while cont<= nlan:
        i=r.randint(1,6)
        cont+=1
        if i%2==0:
            npar+=1
    per=(npar/nlan)*100
    print (per, "%")

#Ex 5.10
def monte_carlo(dardos):
    cont=0
    for i in range(dardos):
        x=r.uniform(0,2)
        y=r.uniform(0,2)
        if((x<=1) and (y>=1)) or ((x>1) and (y<=1)) or ((x>1) and (y<x) and (y>=1)):
            cont+=1
    return 100*cont/dardos

#Ex 5.11
def factorial(n):
    fact=1
    for i in range(n,0,-1):
        fact=fact*i
    return fact

#Ex 5.12
def seno(x,prec):
    sen=0
    termo=0
    for i in range(prec):
        termo=(pow(-1,i)*pow(x,2*i+1))/(factorial(2*i+1))
        sen=sen+termo
    return sen

#Ex 5.13
def harmonic_number(n):
    res=0
    for i in range(1,n+1):
        res=res+(1/i)
    return res


def harmonic(n):
    serie=0
    for i in range(1,n+1):
        serie=serie+(harmonic_number(i))
    return res

#Ex 5.14 Usar matplotlib que NÂO ESTÁ A FUNCIONAR!!!!

#Ex 5.15
def logarithm(prec):
    e=0
    for i in range(prec):
        e=e+(1/factorial(i))
    return e

#Ex 5.16
def num_perfeito(inicio,fim):
    soma=0
    print("Estes são os números perfeitos no intervalo de %d a %d:"%(inicio,fim))
    for i in range(inicio,fim+1):
        for n in range(1,i):
            if (i%n==0):
                soma=soma+n
        if (soma==i):
            print(i)
        soma=0
        
#Ex 5.17
def padrao_a(n):
    comp=len(str(n))
    for i in range(1,n+1): 
        for j in range(1,i+1): 
            print(j,end=comp*' ') 
        print()
        
def padrao_b(n):
    for i in range(n,0,-1):
        for j in range(1,i+1):
            print(j,end=' ')
        print()

def padrao_c(n):
    for i in range(1,n+1):
        print(end=(n-i)*' ')
        for j in range(i,0,-1):
            print(j,end='')
        print()
        
#Ex 5.18
def quadrado(lado):
    for i in range(4):
        t.forward(lado)
        t.right(90)
        
def grelha(dim,lado,x,y):
    t.color("gray")
    t.pu()
    t.goto(x,y)
    for lin in range(dim):
        for col in range(dim):
            t.pd()
            quadrado(lado)
            t.pu()
            t.setx(t.xcor()+lado)
        t.pu()
        t.setposition(x, t.ycor()-lado)
    t.hideturtle()
    t.exitonclick()
    
#Ex 5.19
def random_walk(dim,lado,passos):
    t.speed(0)
    grelha(dim,lado,0,0)
    t.color("green")
    t.goto(0,0)
    t.pd()
    t.speed(6)
    t.dot()
    lim_x=lim_y=(dim*lado)
    cor_x=0
    cor_y=0
    for i in range(passos):
        go_to=random.choice(['N','E','S','W'])
    t.exitonclick()
    
#Ex 5.20
def num_fibonacci(n):
    fib_ant=0
    fib=1
    while fib<n:
        print(fib)
        fib_ant,fib=fib,fib_ant+fib
    return fib==n



