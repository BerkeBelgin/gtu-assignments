.data 
st0:
		.asciiz  "----------MENU----------\n1) Show Primes\n2) Factorize\n3) Bubble Sort\n4) Exit\nSelection:"
st1:
		.asciiz  "ShowPrimes.asm"
st2:
		.asciiz  "Factorize.asm"     
st3:
		.asciiz  "BubbleSort.asm"
s:
		.word	0

.text
.globl main
main:
        addiu   $sp,$sp,-8
        sw      $fp,4($sp)
        move    $fp,$sp
$L8:
        la $a0, st0
        li $v0, 4
        syscall
        li $v0, 5
        syscall
        sw $v0, s

        lw      $2,s
        li      $3,2                        # 0x2
        beq     $2,$3,$L3
        slt     $3,$2,3
        beq     $3,$0,$L4
        li      $3,1                        # 0x1
        beq     $2,$3,$L5
        b       $L2
$L4:
        li      $3,3                        # 0x3
        beq     $2,$3,$L6
        li      $3,4                        # 0x4
        beq     $2,$3,$L7
        b       $L2
$L5:
        la $a0, st1
        li $v0, 18
        syscall

        b       $L2
$L3:
        la $a0, st2
        li $v0, 18
        syscall

        b       $L2
$L6:
        la $a0, st3
        li $v0, 18
        syscall

        b       $L2
$L7:
        li $v0, 10
        syscall

        nop
$L2:
        lw      $3,s
        li      $2,4                        # 0x4
        bne     $3,$2,$L8
        move    $2,$0
        move    $sp,$fp
        lw      $fp,4($sp)
        addiu   $sp,$sp,8
        j       $31
        syscall

        b       $L2

