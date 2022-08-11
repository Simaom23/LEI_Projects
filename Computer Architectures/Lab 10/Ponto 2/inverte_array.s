		.data

		.text
		.globl	inverte_array
inverte_array:
	move $s0,$a0
  	li $t1,0
	div $s2,$a1,2
	mul $t2,$a1,4
	add $s3,$s0,$t2
	addi $s3,$s3,-4
loop1:
  beq $t1,$s2,final
	lw $s4,0($s0)
	lw $s5,0($s3)
	sw $s5,0($s0)
	sw $s4,0($s3)
	addi $s0,$s0,4
	addi $s3,$s3,-4
	addi $t1,$t1,1
	j loop1
final:	
	jr	$ra
