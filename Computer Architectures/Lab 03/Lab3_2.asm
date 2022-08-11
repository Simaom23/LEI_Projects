.data
	display_right: .word 0xFFFF0010
	display_left: .word 0xFFFF0011
	linha: .word  0x3F 0x06 0x5B 0x4F 0x66 0x6D 0x7D 0x07 0x7F 0x67 0x77 0x7C 0x39 0x5E 0x79 0x71 
	coluna: .word 0x3F 0x06 0x5B 0x4F 0x66 0x6D 0x7D 0x07 0x7F 0x67 0x77 0x7C 0x39 0x5E 0x79 0x71 
	ler_linha: .word 0xFFFF0012 
	tecla_premida: .word 0xFFFF0014 
.text	
	main:	
		la $t9,tecla_premida
		la $t8,ler_linha
		la $t7, display_right
		la $t5, display_left
		la $t6, conta_dezenas
		lw $s0, 0($t7) 
		lw $s2, 0($t5) 
		li $t1,0
		li $t2,3
		
	ler_linha:
		lw $s3,0($t8)
		sb $t1,0($s3)
		addi $t1,$t1,1
		j testar
		
		testar:
			add $s1,$s1,$0
			la $t9,tecla_premida
			lw $s1,0($t9)
			bne $s1,$0,display
			ble $t1,$t2,ler_linha
	display:
		
			

