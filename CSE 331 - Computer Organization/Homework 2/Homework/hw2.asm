.data
in_arr_size: .asciiz "Array size: "
in_tar_num: .asciiz "Target number: "
in_arr: .asciiz "Numbers:\n"
msg_pos: .asciiz "Possible!\n"
msg_nps: .asciiz "Not Possible!\n"
space_char: .asciiz " "
.text

# $s0 -> array pointer
# $s1 -> array size
# $s2 -> target number

# $s4 -> return value

# $t0 -> program counter pointer
# $t1 -> array size
# $t2 -> target number

Main:	
	# Print Get Array Size Text
	li $v0, 4
	la $a0, in_arr_size
	syscall
	
	# Get Array Size
	li $v0, 5
	syscall
	move $s1, $v0
	
	# Print Get Target Number Text
	li $v0, 4
	la $a0, in_tar_num
	syscall
	
	# Get Target Number
	li $v0, 5
	syscall
	move $s2, $v0

	# Print Get Array Text
	li $v0, 4
	la $a0, in_arr
	syscall

	# Call Read Array Loop
	move $s0, $sp
	jal ReadStart
	
	# Call Recursive Function
	jal CheckSumPossibilityStart
	
	beq $s4, $zero, MainIf
	
	#Print Possible
	li $v0, 4
	la $a0, msg_pos
	syscall
	
	j Halt
MainIf: 
	# Print Not Possible
	li $v0, 4
	la $a0, msg_nps
	syscall
	
	j Halt

#Read loop Initial
ReadStart:
	move $t0 $s0
	move $t1, $s1
	li $t2, 0
	
	j Read
#Read loop
Read:
	beq $t2, $t1, ReadEnd
	
	li $v0, 5
	syscall
	sw $v0, 0($t0)
	addi $sp, $sp, -4
	addi $t0, $t0, -4
	
	addi $t2, $t2, 1
	j Read
#Read loop end
ReadEnd:
	jr $ra

#Push Recursive func data to sp
Push:
	addi $sp, $sp, -12
	sw $t2, 8($sp)
	sw $t1, 4($sp)
	sw $t0, 0($sp)
	jr $ra
#Pop Recursive func data from sp
Pop:
	lw $t0, 0($sp)
	
	sw $zero, 8($sp)
	sw $zero, 4($sp)
	sw $zero, 0($sp)
	
	addi $sp, $sp, 12
	lw $t2, 8($sp)
	lw $t1, 4($sp)
	
	jr $ra

# Initial Recursive Function
CheckSumPossibilityStart:
	li $s4, 0
	
	move $t0, $ra
	move $t1, $s1
	move $t2, $s2
	jal Push
	j CheckSumPossibility

# Recursive dunction
CheckSumPossibility:
blez $t1, IfCheck1
bltz $t2, IfCheck1
beqz $t2, IfCheck2
bgtz $t2, IfCheck3

IfCheck1: # If n <= 0 || sum < 0
	li $s4, 0
	jal Pop
	jr $t0
IfCheck2: # If sum == 0
	li $s4, 1
	jal Pop
	jr $t0
IfCheck3: # If sum > 0
	la $t0, Recursion1End
	addi $t1, $t1, -1
	move $t2, $t2
	jal Push
	j CheckSumPossibility
Recursion1End:	#Recursive function return PC
	bnez $s4, Recursion2End

	la $t0, Recursion2End
	addi $t1, $t1, -1
	
	mul $t3, $t1, 4
	sub $t3, $s0, $t3
	lw $t3, 0($t3)
	sub $t2, $t2, $t3
	
	jal Push
	j CheckSumPossibility
Recursion2End:	#Recursive function return PC
	jal Pop
	jr $t0

#Halt		
Halt:
	li $v0 10
	syscall
