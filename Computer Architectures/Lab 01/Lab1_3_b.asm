.data 
	numero: .asciiz "Introduza o número: "
.text
main:
	li $v0,4
	la $a0,numero 	# Print da String Numero
	syscall
	
	li $v0,5
	syscall   	
	move $t2,$v0	# Leitura do número
	
	add $t1,$t2,$0
	addi $t1,$t1,-1 # Contador Decremental
	
	li $t0,1	# Paragem do Loop
	
loop:
	mult $t2,$t1
	mflo $t3	
	move $t2,$t3
	addi $t1,$t1,-1
	blt  $t0,$t1,loop

finish:
	move $a0,$t3
	jal print_int 	# Print do fatorial
	li $v0, 10
	syscall
	
print_int:
	li $v0,1
	syscall
	jr $ra

