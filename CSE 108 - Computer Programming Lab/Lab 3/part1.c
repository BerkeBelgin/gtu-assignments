#include <stdio.h>

int input, output;

int main() 
{
	printf("Enter a multi digit number: ");
	scanf("%d",&input);
	
	while(input > 0)
	{
		output = input % 10;
		input -= output;
		input /= 10;
		printf("%d",output);
	}
	printf("\n");
}
