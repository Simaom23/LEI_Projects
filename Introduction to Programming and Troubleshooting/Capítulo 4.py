#Ex 4.1 FEITO
#EX 4.2
def letras_gregas():
    print(chr(0x3B1),"\n",chr(0x3B2),"\n",chr(0x3B3))

#Ex 4.3 - Os objetos são iguais e têm a mesma identidade.

#Ex 4.4 - É semelhante ao caso anterior.

#Ex 4.5 - O x muda de valor logo a sua identidade tambem muda.

#Ex 4.6 - a toma um valor de identidade que depois é passado para b na igualdade e uma diferente atribuição a a muda a sua identidade.

#Ex 4.7 - Já desenhei.

#Ex 4.8 - a strin "a" é multiplicada 3 vezes e é atribuido o valor ao nome 'cad' que ganha um valor de identidade na memória.

#Ex 4.12
def num_quad():
    cont=1
    print("%s \t %s" % ("Número", "Quadrado"))
    while cont<=5:
        quadrado=cont**2
        print("{0:6d}{1:11d}".format(cont, quadrado))
        cont+=1

#Ex 4.14
def tabuada(n):
    if(n<=10):
        print("Tabuada do número %d" % (n))
        print("-"*20)
        for i in range(1,11):
            print("%d x\t%4d\t=%4d" % (n, i, i*n))
    else:
        print("Insira um número menor ou igual a 10")
        
#Ex 4.15
def acronimo(texto):
    acron=""
    previous_letter=""
    acron+=texto[0]
    for i in texto:
        if previous_letter==" ":
            acron+=i
        previous_letter=i
    return acron

#Ex 4.16
def plane():
    v=eval(input("Velocidade de descolagem (m/s): "))
    a=eval(input("Aceleração para descolagem (m/s): "))
    c=(v**2)/(2*a)
    print("Para a velocidade %.2f e aceleração %.2f o comprimento mínimo da pista é: %.2f"%(v, a, c))
    
#Ex 4.17
def energia():
    ti=eval(input("Temperatura inicial (Celsius): "))
    tf=eval(input("Temperatura final (Celsius): "))
    m=eval(input("Quantidade de água (Quilogramas): "))
    e=m*(tf-ti)*4184
    print("Para a massa de água %.2fKG, temperatura inicial %.2fºC e temperatura final %.2fºC a energia necessária é: %.2f Joules" % (m, ti, tf, e))

#Ex 4.18
def temperatura():
    v=eval(input("Velociade do vento (milhas/hora): "))
    t=eval(input("Temperatura (Farenheit [-58, 41]): "))
    tv=35.4+0.6215*t-35.75*v+0.4275*t+v
    print("Para a velocidade do vento %.2f e temperatura exterior %.2f a temperatura sentida é como: %.2f"%(v, t, tv))
    
#Ex 4.19
#def show_matrix(matriz):

#Ex 4.20
def estima(pop):
    n=eval(input("Frequência de nascimentos (minutos): "))
    f=eval(input("Frequência de falecimentos (minutos): "))
    e=eval(input("Frequência de emigração (minutos): "))
    print("Resumo dos dados:")
    print("-"*16)
    print("Frequência de nascimentos (minutos): %d"%n)
    print("Frequência de falecimentos (minutos): %d"%f)
    print("Frequência de emigração (minutos): %d"%e)
    print("Frequência de emigração (minutos): %d"%pop)
    print("Estimativa:")
    print("-"*10)
    minutos_total=60*24*365
    n_nascimentos=minutos_total*n
    n_falecimentos=minutos_total*f
    n_emigrantes=minutos_total*e
    estimativa=pop+n_nascimentos-n_falecimentos-n_emigrantes
    print("A população ao fim de uma ano: %d"%estimativa)
#Para calcular para vários anos adicionava um input do utilzador para anos e multiplicava os 365 dias pelos anos
    
#Ex 4.19      