					;Input Field
		load R1,3d			;Enter a value between 1d and 5d (n!)
		move R2,R1			;The value to store (n - 1), Equals to (n) at first
		
					;Assignments for Operations
		load R5,1d 			;+1 number
		load R6,-1d			;-1 number
		load R7,0d			;0 number
		load R8,10d			;10 number
		load R9,-10d		;-10 number
		load RA,100d		;100 number
		load RB,-100d		;-100 number
		load RC,30h			;30h number
		
					;Main Function to Operate Factorial Operation
Factorial:	addi R2,R2,R6		;R2 = (n - 1) also (R2 - 1)
		move R0,R7			;R0 = 0 (for if statement)
		jmpLE R2<=R0,Def		;If (n - 1) = 0 Go to printing phase 
		jmp MulAssign		;Go for multiplication phase

					;Assignments Before Multiplication
MulAssign:	move R0,R2			;R0 = (n - 1)
		load R3,0d			;Variable for Multiply Result
		load R4,0d			;Variable for Sum Counter
		jmp Multiply

					;Multiplication Operation
Multiply:	jmpEQ R4=R0,MulResult	;R4 = (n - 1) then go to Multiplication Result
		addi R3,R3,R1		;R3 +=(n)
		addi R4,R4,R5		;R4 += 1
		jmp Multiply		;Loop

					;Multiplication Result
MulResult:	move R1,R3			;Store Result at R1
		jmp Factorial		;Go back to factorial the operation

					;Define and Print
Def:		move R0,R1			;R0 = Factorial Result (for if statements)
		load RF,52h			;Write "R"
		load RF,65h			;Write "e"
		load RF,73h			;Write "s"
		load RF,75h			;Write "u"
		load RF,6Ch			;Write "l"
		load RF,74h			;Write "t"
		load RF,3Ah			;Write ":"
		load RF,20h			;Write " "
		jmp In100			;Go division by 100d phase

					;Check if the Result is Greater Than 100d
In100:	load RC,30h			;RC = 0 character in ACII
		jmpLE RA<=R0,Dv100	;if result is greater than 100d Divide by 100d
		move RF,RC			;else write 0
		jmp In10			;Go division by 10d phase

					;Divide by 100d
Dv100:	addi R0,R0,RB		;Result -= 100d
		addi RC,RC,R5		;ASCII character += 1
		jmpLE RA<=R0,Dv100	;if result still greater than 100d loop
		move RF,RC			;Write ASCII character
		jmp In10			;Go division by 10d phase

					;Check if the Result is Greater Than 10d
In10:		load RC,30h			;RC = 0 character in ACII
		jmpLE R8<=R0,Dv10		;if result is greater than 10d Divide by 10d
		move RF,RC			;else write 0
		jmp In1			;Go division by 1d phase

					;Divide by 10d
Dv10:		addi R0,R0,R9		;Result -= 10d
		addi RC,RC,R5		;ASCII character += 1
		jmpLE R8<=R0,Dv10		;if result still greater than 10d loop
		move RF,RC			;Write ASCII character
		jmp In1			;Go division by 1d phase

					;Check if the Result is Greater Than 1d
In1:		load RC,30h			;RC = 0 character in ACII
		jmpLE R5<=R0,Dv1		;if result is greater than 1d Divide by 1d
		move RF,RC			;else write 0
		jmp Stop			;Stop

					;Divide by 1d
Dv1:		addi R0,R0,R6		;Result -= 1d
		addi RC,RC,R5		;ASCII character += 1
		jmpLE R5<=R0,Dv1		;if result still greater than 1d loop
		move RF,RC			;else write 0
		jmp Stop			;Stop

Stop:		load RF,10d			;New Line
		halt				;Finish
