#include <stdio.h>

char choice;
int a,b;

int addition(int val1, int val2)
{
	return val1 + val2;
}

int subtraction(int val1, int val2)
{
	return val1 - val2;
}

int multiplication(int val1, int val2)
{
	return val2 * val1;
}

double division(int divden, int divsor)
{
	return (double) divden / (double) divsor;
}

int power_of_two(int exp)
{
	int x = 1;
	
	for(int i = 0; i < exp; i++)
	{
		x *= 2;
	}
	return x;
}

int get_integer_from_user()
{	
	printf("Enter two numbers:\n");
	scanf("%d%d",&a,&b);
}

char get_operation_type_from_user()
{
	char c;
	
	printf("Enter your choice: (+, -, *, /, 2)\n");
	scanf("%c",&c);
	return c;
}

int main()
{
	choice = get_operation_type_from_user();
	
	get_integer_from_user();
	
	if(choice == '+')
	{		
		printf("The addition of %d by %d is: %d\n", a, b, addition(a, b));
	}
	else if(choice == '-')
	{		
		printf("The subtraction of %d by %d is: %d\n", a, b, subtraction(a, b));
	}
	else if(choice == '*')
	{		
		printf("The multiplication of %d by %d is: %d\n", a, b, multiplication(a, b));
	}
	else if(choice == '/')
	{			
		if(b != 0)
		{
			printf("The division of %d by %d is: %lf\n", a, b, division(a, b));
		}
		else
		{
			printf("It is not possible.\n");
		}
	}
	else if(choice == '2')
	{
		printf("The power of two by %d is: %d\n", a, power_of_two(a));
		printf("The power of two by %d is: %d\n", b, power_of_two(b));
	}
}
