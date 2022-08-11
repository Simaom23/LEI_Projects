# O cabeçalho da função bin_img em C é
#
# void bin_img(unsigned char *ptr, int w, int h, unsigned char limiar);

	.data
	
	.text
	.globl	bin_img
	
bin_img:
	li $t0,0
  mul $s2,$a1,$a2
  addi $sp,$sp,-4
	sw $ra,4($sp)
	jal calcula_limiar
	lw $ra,4($sp)
	addi $sp,$sp,4
  move $a3, $v0
loop:
  beq $t0,$s2,fim
  lbu $s0,0($a0)
  addi $t0,$t0,1
  blt $s0,$a3,bin0
  li $s1,255
  sb $s1,0($a0)
  addi $a0,$a0,1
  j loop  
bin0:
  li $s1,0
  sb $s1,0($a0)
  addi $a0,$a0,1
	j loop
fim:
		jr	$ra
