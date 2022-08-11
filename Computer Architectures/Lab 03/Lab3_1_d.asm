.data
	display_right: .word 0xFFFF0010
	display_left: .word 0xFFFF0011
	conta_unidades: .word 0x3F 0x06 0x5B 0x4F 0x66 0x6D 0x7d 0x07 0x7F 0x67 0x77 0x7C 0x39 0x5E 0x79 0x71 0x3F
	conta_dezenas: .word 0x3F 0x06 0x5B 0x4F 0x66 0x6D 0x7d 0x07 0x7F 0x67 0x77 0x7C 0x39 0x5E 0x79 0x71 0x3f	
.text	
	main:
		la $t7, display_right
		la $t5, display_left
		la $t6, conta_dezenas
		lw $s0, 0($t7) #display right
		lw $s2, 0($t5) #display left 
		li $t1,17
		li $t2,0
		li $t3,17
	dezenas:
		li $t4,0
		la $t0, conta_unidades
		lw $s1,0($t6)
		sb $s1,0($s2)
		addi $t6,$t6,4
		addi $t2,$t2,1
		j unidades
	unidades:
		lw $s3,0($t0)
		sb $s3, 0($s0)
		addi $t0,$t0,4
		addi $t4,$t4,1
		blt $t4,$t3,unidades
		beq $t2,$t1,main
		beq $t4,$t3,dezenas

