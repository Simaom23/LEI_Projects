#Ex 1.10F
def ex110f():
    Tc=eval(input("Introduza a temperatura em escala Celsius: "))
    Tf= 9/5*Tc+32
    print("A temperatura na escala Farenheit �: ", Tf)
#Ex 1.11F
import random
import math
def ex111f():
    r=random.randint(1,100)
    h=random.randint(1,100)
    volume= (math.pi * r**2 * h)/3
    print("O raio �: ", r)
    print("A altura �: ", h)
    print("O volume �: ", round(volume,3))
    
#Ex 1.15F
def ex115f(qtd_agua):
    garrafas_5=math.ceil(qtd_agua//5)
    qtd_agua=qtd_agua%5
    garrafas_15=math.ceil(qtd_agua//1.5)
    qtd_agua=qtd_agua%1.5
    garrafas_05=math.ceil(qtd_agua//0.5)
    qtd_agua=qtd_agua%0.5
    garrafas_025=math.ceil(qtd_agua//0.25)
    print(garrafas_5, garrafas_15,garrafas_05,garrafas_025)

#Ex 1.17M
def ex117m():
    x=eval(input("Insere a coordena X: "))
    y=eval(input("Insere a coordena Y: "))
    r=math.sqrt(x**2+y**2)
    x=r
    teta=math.acos(x/r)
    print("As coordenadas convertidas para polar s�o: ", x, y)

#Ex 1.18M
def ex118m():
    a=eval(input("Introduza a dist�ncia ao sol em AU's: "))
    m1=eval(input("Introduza a massa do 1� objeto: "))
    m2=eval(input("Introduza a massa do 2� objeto: "))
    p=math.sqrt((((4*math.pi)**2)*(a**3))/(6.67e-11*(m1+m2)))
    print(p)
    
import turtle
def poligono_regular(comp_lado,num_lados):
    angle=360/num_lados
    for i in range(num_lados):
        turtle.fd(comp_lado)
        turtle.right(angle)
    turtle.exitonclick()
        
#Ex 2.1F
def ex21f(forward,rotate):
    for i in range(5):
        turtle.fd(forward)
        turtle.right(rotate)
    turtle.exitonclick()

#Ex 2.2F
def ex22f(forward,rotate,exe):
    for i in range(exe):
        turtle.fd(forward)
        turtle.right(rotate)
        forward=forward+5
    turtle.exitonclick()

import random
#Ex 2.3F
def ex23f():
    turtle.colormode(255)
    for i in range(random.randint(0,1000)):
        r=random.randint(0,255)
        g=random.randint(0,255)
        b=random.randint(0,255)
        turtle.pencolor(r,g,b)
        turtle.fd(random.randint(0,100))
        turtle.seth(random.randint(0,360))
    turtle.exitonclick()

#Ex 2.5F
def ex25f(radius,steps):
    turtle.circle(radius, steps)
    
#Ex 2.9D
def ex29d_quadrado(lado,x,y,cor):
    turtle.pu()
    turtle.goto(x,y)
    turtle.pd()
    turtle.fillcolor(cor)
    turtle.begin_fill()
    for i in range(4):
        turtle.forward(lado)
        turtle.right(90)
    turtle.end_fill()
    
#Ex 2.9D
def ex29d(num,lado,x,y):
    var=0.5*lado
    for i in range(num):
        ex29d_quadrado(lado,x,y)
        x=x-var
        y=y+var
        lado=lado+2*var
    turtle.exitonclick()

#Ex 2.10D
def ex210d(num,lado,x,y,rotate):
    var=0.5*lado
    for i in range(num):
        ex29d_quadrado(lado,x,y)
        turtle.pu()
        turtle.goto(x,y)
        turtle.pd()
        turtle.left(rotate)
        lado=lado+2*var
    turtle.exitonclick() 

#Ex 2.11M
t=turtle
offset=165
border=10
half_offset=165/2
upper_line=0
lower_line=upper_line-(half_offset+border/4)

def ex211m_circulo(raio,x,y,cor):
    t.pu() 
    t.goto(x,y)
    t.pd() 
    t.pencolor(cor)
    t.circle(raio)
    
largura=5
raio=75
def ex211m():
    t.pensize(10)
    ex211m_circulo(raio,-offset,upper_line,"blue")
    ex211m_circulo(raio,-half_offset,lower_line,"yellow")
    ex211m_circulo(raio,0,0,"black")
    ex211m_circulo(raio,half_offset,lower_line,"green")
    ex211m_circulo(raio,offset,upper_line,"red")
    t.exitonclick()

def circulo(raio,x,y,cor,angulo):
    t.pu() 
    t.goto(x,y)
    t.pd()
    t.fillcolor(cor)
    t.begin_fill()
    t.circle(raio,angulo)
    t.end_fill()

def triangulo(x,y,a,b,c,angulo1,angulo2,pencolor,fillcolor,pos):
    turtle.pu()
    turtle.goto(x,y)
    turtle.seth(pos)
    turtle.pd()
    turtle.pencolor(pencolor)
    turtle.fillcolor(fillcolor)
    turtle.begin_fill()
    turtle.forward(a)
    turtle.left(angulo1)
    turtle.forward(b)
    turtle.left(angulo2)
    turtle.forward(c)
    turtle.end_fill()
    
#Ex 2.12D
def ex212d(quadrado):
    ex29d_quadrado(quadrado,-(quadrado/2),(quadrado/2),"yellow")
    circulo((quadrado/2.38),0,-(quadrado/2.38),"black",360)
    triangulo(0,0,(quadrado/2.04),(quadrado/2.04),(quadrado/2.04),120,120,"yellow","yellow",0)
    triangulo(0,0,(quadrado/2.04),(quadrado/2.04),(quadrado/2.04),120,120,"yellow","yellow",240)
    triangulo(0,0,(quadrado/2.04),(quadrado/2.04),(quadrado/2.04),120,120,"yellow","yellow",120)
    circulo((quadrado/10.63),0,-(quadrado/10.63),"yellow",360)
    circulo((quadrado/12.5),0,-(quadrado/12.5),"black",360)
    t.hideturtle()
    turtle.exitonclick()

#Ex 2.13D  
def ex213d(raio,x,y):
    circulo(raio,x,y,"white",360)
    t.setheading(-90)
    circulo(raio,x-raio,y+raio,"black",180)
    t.setheading(90)
    circulo(raio/2,x,y+raio,"black",180)
    t.setheading(-90)
    circulo(raio/2,x,y+raio,"white",180)
    circulo(raio/9,x-(raio/2)+(raio/9),y+raio,"white",360)
    circulo(raio/9,x+(raio/2)+(raio/9),y+raio,"black",360)
    t.hideturtle()
    turtle.exitonclick()
    
""" 3.9- Descodificar texto que foi codificado usando o m�todo de separa��o de
carateres nas posi��es pares e impares """
def encripta(texto_normal):
    comp=len(texto_normal)
    car_impares=texto_normal[1::2]
    car_pares=texto_normal[0:comp:2]
    texto_encriptado=car_impares+car_pares
    return texto_encriptado
if __name__=="__main__":
    encripta("texto a encriptar")

def encripta2(texto_normal):
    car_impares=''
    car_pares=''
    cont=0
    for c in texto_normal:
        if(cont%2==0):
            car_pares+=c
        else:
            car_impares+=c
        cont+=1
    texto_encriptado=car_impares+car_pares
    return texto_encriptado

def descodificar(texto_normal):
    texto_encriptado=encripta2(texto_normal)
    print("Texto Encriptado:", texto_encriptado)
    car_impares=texto_normal[1::2]
    car_pares=texto_normal[0::2]
    cont=0; cont_pares=0; cont_impares=0
    texto_descodificado=""
    for c in texto_encriptado:
        if(cont%2==0):
            texto_descodificado+=car_pares[cont_pares]
            cont_pares+=1
        else:
            texto_descodificado+=car_impares[cont_impares]
            cont_impares+=1
        cont+=1
    return texto_descodificado

#Ex 3.13
def prefixos(palavra):
    for c in range(len(palavra)):
        pref=palavra[0:c+1]
        print(pref)
        
#Ex 3.14
def sufixos(palavra):
    for c in range(len(palavra)):
        suf=palavra[len(palavra)-1-c:len(palavra)]
        print(suf)

#Ex 3.12
def subcadeias(palavra,n):
    cont=0
    for c in range(len(palavra)-(n-1)):
        subcadeias=palavra[cont:c+3]
        cont+=1
        print(subcadeias)

import math
#Ex 3.2
def area_triangulo(a,b,c):
    s=(a+b+c)/2
    area=math.sqrt(s*(s-a)*(s-b)*(s-c))
    print(area)

#Ex 3.15
def ex315(adn):
    turtle.down()
    for c in adn:
        if(c=="f"):
            turtle.forward(50)
        elif(c=="t"):
            turtle.back(50)
        elif(c=="e"):
            turtle.left(45)
        else:
            turtle.right(45)
    turtle.exitonclick()


#Ex 3.16
def ex316(adn):
    turtle.down()
    for c in adn:
        if(c=="f"):
            turtle.forward(random.randint(0,100))
        elif(c=="t"):
            turtle.back(random.randint(0,100))
        elif(c=="e"):
            turtle.left(random.randint(0,360))
        else:
            turtle.right(random.randint(0,360))
    turtle.exitonclick()

import random
#Ex 3.17
def ex317(tarefas):
    adn=''
    for c in range(tarefas):
        adn=adn+random.choice('fted')
    ex316(adn)
    turtle.exitonclick()

#Ex 3.18
   
    