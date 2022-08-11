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
	add $t1,$t1,$t2 # Paragem do Loop
	
	li $t0,0 	# Contador
	
loop:
	move $a0,$t2
	jal print_int
	li  $a0,0x0A
	jal print_char
	addi $t2,$t2,1
	addi $t0,$t0,1
	blt  $t0,$t1,loop

finish:
	li $v0, 10
	syscall
	
print_int:
	li $v0,1
	syscall
	jr $ra

print_char:
	li $v0,11
	syscall
	jr $ra
