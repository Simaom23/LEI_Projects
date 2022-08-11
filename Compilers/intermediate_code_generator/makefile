compile: gocompiler.l gocompiler.y
	flex gocompiler.l
	yacc -d gocompiler.y
	gcc -g *.c -Wall -o gocompiler 