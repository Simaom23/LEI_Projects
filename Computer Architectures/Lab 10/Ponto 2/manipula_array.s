		.data

		.text
		.globl	manipula_array
manipula_array:
  li $t0,0
	move $s0,$a0
	move $s1,$a1
loop:
  	beq $t0,$s1,fim
	lw $s2,0($s0)
	mul $s2,$s2,2
	sw $s2,0($s0)
	addi $s0,$s0,4
	addi $t0,$t0,1
	j loop
fim:		
	addi $sp,$sp,-4 
	sw $ra,4($sp)
	jal inverte_array
	lw $ra,4($sp)
	addi $sp,$sp,4
	jr	$ra
