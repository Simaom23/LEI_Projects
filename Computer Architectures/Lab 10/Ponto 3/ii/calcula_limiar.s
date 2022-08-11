	.data
	
	.text
	.globl	calcula_limiar
	
calcula_limiar:
  li $t1,0
  li $t2,0
	move $t3,$s2
	move $t4,$a0
loop:
  beq $t2,$t3,fim
	lbu $s4,0($t4)
	add $t1,$t1,$s4
	addi $t4,$t4,1
  addi $t2,$t2,1
	j loop
fim:
  div $t1,$t3
  mflo $v0  
  jr $ra
  