		load	R0,0d		;0
		load	R1,1d		;1
		load	R2,Input	;Address
		move	R3,R2		;Address Copy
		load	R4,[R3]	;Address Value
		load	R5,-1d	;-1

Count:	jmpEQ	R4=R0,Write	;If the Cell Value = 00 Go Write
		addi	R3,R3,R1	;Address ++
		load	R4,[R3]	;R4 = Next Cell Value
		jmp	Count		;Loop

Write:	move	R0,R2		;R0 = Start Address
		addi	R3,R3,R5	;Address --
		load	RF,[R3]	;Print Cell Value
		jmpEQ	R3=R0,Stop	;If Current Address = Start Address, Stop
		jmp	Write		;Loop

Stop:		halt			;Stop

Input:	db	10
		db	"Berke Belgin 171044065"
		db	10
