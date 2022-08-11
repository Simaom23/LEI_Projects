.data
masc: .word 0x00000001
num: .word 0x00000007

.text
main:	lw $a0,masc
	lw $a1,num
	li $a2,32
	li $a3,0
	beq $a1,$zero,fim_
	j conta

return:	move $a0,$v0
	li $v0,34
	syscall
	j fim

conta:	move $s4,$a3

loop:	beq $a2,$zero,return
	and $s4,$a0,$a1
	beq $s4,$zero,repeat
	srl $a1,$a1,1
	subi $a2,$a2,1
	addi $s3,$s3,1
	move $v0,$s3
	j loop

repeat:	srl $a1,$a1,1
	subi $a2,$a2,1
	j loop

fim_:	li $v0,34
	li $a0,0
	syscall
		
fim: