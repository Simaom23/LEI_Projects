.text
main:
	lui $t0,0x1001
	li $t1,0x00000000	
	li $t3,1	
	li $t4,1	
	
loop_colunas:
	or $t1,$s1,$s2
	sw $t1,0($t0)
	addi $t0,$t0,4
	mul $s2,$t3,4
	sll $s2,$s2,8
	addi $t3,$t3,1
	beq $t3,64,loop_linhas
	j loop_colunas
	loop_linhas:
		beq $t4,33,finish
		li $t3,0
		mul $s1,$t4,4
		sll $s1,$s1,16
		addi $t4,$t4,1
		j loop_colunas
		
finish:
	li $v0,10
	syscall
