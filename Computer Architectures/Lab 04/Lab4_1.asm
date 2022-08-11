.data
num: .word 0x10203040
.text
main:	lw $t0,num
	lw $t1,num
	li $v0,34
	jal func
	add $a0,$t2,$zero
	
print_num:
	li $v0,34
	syscall
	
finish:
	li $v0,10
	syscall
	
func:	sra $t0,$t0,16
	sll $t1,$t1,16
	add $t2,$t1,$t0
	jr $ra
	