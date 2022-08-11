.text
main:
	lui $t0,0x1001
	li $t1,0x0000000FF
	li $t2,0x00FF00FF
	li $t3,0	
	li $t4,0	
	
loop_azul:
	sw $t1,0($t0)
	addi $t0,$t0,4
	addi $t3,$t3,1
	beq $t3,28,loop_magenta
	loop_magenta:
		beq
		sw $t2,0($t0)
		addi $t0,$t0,4
		addi $t3,$t3,1
		beq $t4,36,loop_azul
		j loop_magenta
	beq $t3,64,loop_linhas
	j loop_azul
	loop_linhas:
		beq $t4,32,finish
		li $t3,0
		addi $t4,$t4,1
		j loop_azul
	
				
finish:
	li $v0,10
	syscall
