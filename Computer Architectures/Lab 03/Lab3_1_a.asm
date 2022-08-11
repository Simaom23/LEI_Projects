.data
	display_right: .word 0xFFFF0010
	start: .word 0x00000001
.text	
	main:
		la $t7, display_right
		lw $s0, 0($t7)
		la $t6, start
		lw $s1,0($t6)
		li $t1,8
		li $t2,0
	loop:
		sb $s1,0($s0)
		sll $s1,$s1,1
		addi $t2,$t2,1
		ble $t2,$t1,loop
		j main
	finish:
		li $v0,10
		syscall
