.data 
	str:  .asciiz "Uma frase!0" 
	comp:  .word 0 
.text
la $t0,str
la $t1,comp
lw $s1,0($t0)
lw $s1,0($t1)
jal loop
add $a0,$a0,$s1
li $v0,34
syscall
loop: 
	addi $s1,$s1,1
	bne $s1,$0, loop
	jr $ra 
https://www.youtube.com/watch?v=8mZPMNgHhhE