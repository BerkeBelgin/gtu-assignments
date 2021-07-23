.data
enter_size: .asciiz "Enter Size: "
enter_nums: .asciiz "Enter Numbers:\n"
comma: .asciiz ", "
newline: .asciiz "\n"

.text
.globl main
main:
    li      $v0, 4
    la      $a0, enter_size
    syscall

    li      $v0, 5
    syscall
    move    $s0, $v0

    sub     $t0, $zero, $s0
    li      $t1, 4
    mul     $t0, $t0, $t1
    add     $sp, $sp, $t0
    move    $s1, $sp

    li      $v0, 4
    la      $a0, enter_nums
    syscall
    
    li      $t0, 0
    jal     fill
    jal     bubble_sort
    li      $t0, 0
    jal     print

    li      $v0, 10
    syscall

fill:
    bge     $t0, $s0, exit_fill
	
    li      $v0, 5
    syscall	
    li      $t2, 4
    mul     $t1, $t0, $t2
    add     $t1, $t1, $s1
    sw      $v0, 0($t1)
    addi    $t0, $t0, 1
    j       fill
exit_fill:
    jr      $ra

print:
    bge     $t0, $s0, exit_print

    bne     $t0, $zero, print_comma
continue_print:
    li      $t2, 4
    mul     $t1, $t0, $t2
    add     $t1, $t1, $s1
    lw      $a0, 0($t1)
    li      $v0, 1
    syscall
    
    addi    $t0, $t0, 1
    j       print
print_comma:
    li      $v0, 4
    la      $a0, comma
    syscall
    j       continue_print
exit_print:
    li      $v0, 4
    la      $a0, newline
    syscall
    jr $ra

swap:
    sw      $t6, 0($t2)
    sw      $t5, 0($t3)
    li      $t0, 1
    j       sort_continue

sort:
    bge     $t1, $s0, bubble_sort_continue
    li      $t4, 4

    addi    $t2, $t1, -1
    mul     $t2, $t2, $t4
    add     $t2, $t2, $s1
    lw      $t5, 0($t2)
    
    move    $t3, $t1
    mul     $t3, $t3, $t4
    add     $t3, $t3, $s1
    lw      $t6, 0($t3)
    
    bgt     $t5, $t6, swap
sort_continue:
    addi    $t1, $t1, 1
    j       sort

bubble_sort:
    li      $t0, 0
    li      $t1, 1
    j       sort
bubble_sort_continue:
    bne     $t0, $zero, bubble_sort
    jr		$ra
