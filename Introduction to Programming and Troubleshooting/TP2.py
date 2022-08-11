#VOLUME DO CILINDRO
def VolumeCilindro(raio, altura): # Raio e altura: parametros de entrada.
    #Processamento
    pi=3.1416
    area_base=pi * raio**2
    volume = area_base * altura
    print(volume) # O valor apenas é imprimido.
    
#VOLUME DO CILINDRO INTERATIVO
def VolumeCilindro_interativo():
    #Entrada
    raio = eval(input("Introduza o raio: "))
    altura = eval(input("Introduza o raio: "))
    #Processamento
    pi=3.1416
    area_base=pi * raio**2
    volume = area_base * altura
    return(volume)  # Retorna o valor e pode ser reutilizado.

# Parametros formais: sem valores associados.
# Parametros reais: com valores associados.

#IMC
def imc_interativo():
    peso = eval(input("Introduza o peso: "))
    altura = eval(input("Introduza a altura: "))
    imc=peso/altura**2
    return(round(imc))


#PESO IDEAL
#HOMEM
def ideal_homem():
    altura = eval(input("Introduza a altura: "))
    ideal_homem = 72.7*altura-58
    return(ideal_homem)
#MULHER
def ideal_mulher():
    altura = eval(input("Introduza a altura: "))
    ideal_mulher = 62.1*altura-44.7
    return(ideal_mulher)

#PESO IDEAL HOMEM E MULHER JUNTOS
def peso_ideal():
    genero = "s"
    while(genero != "h" or genero != "m"):
        genero=input("Introduza o seu genero (h ou m): ")
        if (genero=="h"):
            altura = eval(input("Introduza a altura: "))
            ideal_homem = 72.7*altura-58
            print("O seu peso ideal é: ", ideal_homem)
            break
        if(genero=="m"):
            altura = eval(input("Introduza a altura: "))
            ideal_mulher = 62.1*altura-44.7
            print("O seu peso ideal é: ", ideal_mulher)
            break
        print("Introduza o seu genero corretamente!")
        
#ADIVINHA
import random 
def adivinha():
    secreto=random.randint(0,100)
    numero=eval(input("Palpito: "))
    if(numero==secreto):
        print("Acertou!")
        return True
    else:
        print("Falhou!")
        return False
    
#ADVINHA VÁRIAS VEZES
def adivinha_mais_tentativas():
    secreto=random.randint(0,100)
    for i in range (15):
        numero=eval(input("Palpito: "))
        if(numero==secreto):
            print("Acertou!")
            break
        else:
            print("Falhou!")
    return

#ADVINHA DICAS
def adivinha_dicas():
    secreto=random.randint(0,100)
    for i in range (15):
        numero=eval(input("Palpite: "))
        if(numero==secreto):
            print("Acertou!")
            break
        else:
            print("Falhou!")
            if(numero>secreto):
                print("Maior que o número secreto!\n")
            if(numero<secreto):
                print("Menor que o número secreto!\n")
    return

                    
    