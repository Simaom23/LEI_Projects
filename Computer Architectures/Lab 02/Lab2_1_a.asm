.text
main:
	lui $t0,0x1001
	li $t1,0x00ffff00 	# $t1=amarelo
	
	li $t3,32	# Contador Horizontal
	li $t4,0
	li $t5,16	# Contador Vertical
	li $t6,0	
	
loop_colunas:
	sw $t1,0($t0)
	addi $t0,$t0,4
	addi $t4,$t4,1
	beq $t4,32,loop_linhas
	j loop_colunas
	loop_linhas:
		beq $t6,16,finish
		addi $t0,$t0,128
		li $t4,0
		addi $t6,$t6,1
		j loop_colunas
		
finish:
	li $v0,10
	syscall
		
	
