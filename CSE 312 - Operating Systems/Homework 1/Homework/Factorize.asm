.data
comma: .asciiz ", "
newline: .asciiz "\n"

.text
.globl main
main:
    li      $v0, 5
    syscall

    addi    $sp, $sp, -4
    sw      $v0, 0($sp)

    li      $t0, 1
    addi    $sp, $sp, -4
    sw      $t0, 0($sp)

    jal     factors

    li      $v0, 10
    syscall

factors:
    lw      $t0, 4($sp)
    lw      $t1, 0($sp)
    bgt     $t1, $t0, exit_factors
    div     $t2, $t0, $t1
    mul     $t2, $t2, $t1
    beq     $t2, $t0, print_factors
continue_factors:
    addi    $t1, $t1, 1
    sw      $t1, 0($sp)
    j       factors

print_factors:
    li      $t4, 1
    bne     $t1, $t4, print_comma
    j print_factor

print_comma:
    li      $v0, 4
    la      $a0, comma
    syscall
    j       print_factor

print_factor:
    li      $v0, 1
    move    $a0, $t1
    syscall
    j       continue_factors
    
exit_factors:
    li      $v0, 4
    la      $a0, newline
    syscall
    jr      $ra
