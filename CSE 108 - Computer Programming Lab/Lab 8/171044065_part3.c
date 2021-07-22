#include <stdio.h>

int F(int n)
{
	if(n > 1)
	{
		return 2 * F(n / 2) + 1;
	}
	else
	{
		return 1;
	}
}

int main()
{
	int n;
	printf("Enter a number: ");
	scanf("%d", &n);
	
	printf("Result = %d\n", F(n));
}
