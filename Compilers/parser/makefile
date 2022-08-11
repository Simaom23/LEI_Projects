compile: gocompiler.l gocompiler.y
	flex gocompiler.l
	yacc -d gocompiler.y
	gcc lex.yy.c y.tab.c tree.c -o gocompiler 