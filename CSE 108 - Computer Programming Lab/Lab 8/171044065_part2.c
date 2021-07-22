#include <stdio.h>

int result = 1;

int recursive_pow(int base, int exponent)
{
	if(exponent > 0)
	{
		result *= base;
		exponent--;
		recursive_pow(base, exponent);
	}
	if(base == 0 && exponent == 0)
	{
		result = -1;
	}
	if(base == 0)
	{
		result = 0;
	}
	return result;
}

int main()
{
	int base, exponent;
	
	printf("Enter base: ");
	scanf("%d", &base);
	printf("Enter exponent: ");
	scanf("%d", &exponent);
	
	printf("\nbase=%d, exponent=%d, result=%d\n", base, exponent, recursive_pow(base, exponent));
}
