.data
newline: .asciiz "\n"
prime: .asciiz " prime\n"

.text
.globl main
main:
	li      $s0, 1000	# i e kadar
	li      $s1, 2	# i

while1:	
    bge     $s1, $s0, endwhile1		
	li      $s2, 0			# notprime
	li      $s4, 2			# j = 2
	sra     $s5, $s1, 1			# i / 2

while2:	
    bgt     $s4, $s5, endwhile2
	move    $s6, $s1

while3:	
    blt     $s6, $s4, endwhile3 	# sayi > modu alınan  i ve j  
	sub     $s6, $s6, $s4
	j       while3

endwhile3:
	bne     $s6, $zero, endif1		#if mod sonucu 0 değilse jump
	li      $s2, 1
	j       endwhile2

endif1:
	addi    $s4, $s4, 1	# j++
	j       while2

endwhile2:
	li      $v0, 1
	move    $a0, $s1
	syscall

	beq     $s2, $zero, print_prime		#if prime 0sa jump
	bne     $s2, $zero, print_not_prime		#if not prime 0 değilse jump

print_prime:
	li      $v0, 4
	la      $a0, prime
	syscall
	j		end_print
print_not_prime:
	li      $v0, 4
	la      $a0, newline
	syscall
	j		end_print
end_print:
	addi    $s1, $s1, 1	# i++
	j       while1

endwhile1:
	li      $v0, 10
	syscall
