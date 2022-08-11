.data
a: .word 0x00000fff
b: .word 0x000000ff

.text
main:		lw $a0,a
		lw $a1,b
		slt $t2,$a1,$a0
		bne $t2,$zero,a_maior
		j b_maior
return:		move $a0,$v0
		li $v0,34
		syscall
		j fim
	
a_maior:	move $s0,$a0
		move $s1,$a1
		sub $v0,$s0,$s1
		j return

b_maior:	move $s0,$a0
		move $s1,$a1
		sub $v0,$s1,$s0
		j return 
		
fim: