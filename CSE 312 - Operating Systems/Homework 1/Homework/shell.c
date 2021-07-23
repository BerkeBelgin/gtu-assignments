#include<stdio.h>
char *st0 = "----------MENU----------\n1) Show Primes\n2) Factorize\n3)Bubble Sort\n4)Exit\nSelection: ";
char *st1 = "ShowPrimes.asm";
char *st2 = "Factorize.asm";
char *st3 = "BubbleSort.asm";
int s = 0;

int main(){
	do {
        __asm__(
			"la $a0, st0\n\t"
			"li $v0, 4\n\t"
			"syscall\n\t"

			"li $v0, 5\n\t"
			"syscall\n\t"
            "sw $v0, s\n\t"
		);
		switch(s){
			case 1:
				__asm__(
					"la $a0, st1\n\t"
					"li $v0, 18\n\t"
					"syscall\n\t"
				);
				break;
			case 2:
				__asm__(
					"la $a0, st2\n\t"
					"li $v0, 18\n\t"
					"syscall\n\t"
				);
				break;
			case 3:
				__asm__(
					"la $a0, st3\n\t"
					"li $v0, 18\n\t"
					"syscall\n\t"
				);
				break;
			case 4:
				__asm__(
					"li $v0, 10\n\t"
					"syscall\n\t"
				);
				break;
		}
	} while(s != 4);
	return 0;
}
