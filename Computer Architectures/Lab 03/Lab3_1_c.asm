.data
	display_right: .word 0xFFFF0010
	conta: .word 0x3F 0x06 0x5B 0x4F 0x66 0x6D 0x7d 0x07 0x7F 0x67 0x77 0x7C 0x39 0x5E 0x79 0x71
.text	
	main:
		la $t7, display_right
		lw $s0, 0($t7)
		la $t6, conta
		lw $s1,0($t6)
		li $t1,16
		li $t2,0
	loop:
		lw $s1,0($t6)
		sb $s1,0($s0)
		addi $t6,$t6,4
		addi $t2,$t2,1
		ble $t2,$t1,loop
		j main
	finish:
		li $v0,10
		syscall
