In order to make shell.asm work, which is converted from shell.c, I did following changes:
	Added .data and .text segment flags,
	Wiped out generated data section and coded it by hand,
	Replaced generated parts like lui $2,%hi(s) and lw $3,%lo(s)($2) with lw $2,s.
