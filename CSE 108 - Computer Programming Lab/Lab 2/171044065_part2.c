#include <stdio.h>
#include <math.h>
//execute with -lm

double calc_quadratic_eq_roots(int x,int y, int z,int q)
{
	double res;
	
	if(q == 0)
	{
		res = ((-1 * y) + sqrt((y * y) - (4 * x * z))) / (2 * x);
	}
	
	else if (q == 1)
	{
		res = ((-1 * y) - sqrt((y * y) - (4 * x * z))) / (2 * x);
	}
	
	return res;
}

int main()
{
	int choice, a, b, c;

	printf("Enter three numbers:\n");
	
	printf("a = ");
	scanf("%d", &a);
	
	printf("b = ");
	scanf("%d", &b);
	
	printf("c = ");
	scanf("%d", &c);
	
	printf("Enter your choice:\n");
	do
	{
		scanf("%d", &choice);
		if(choice != 1 && choice != 0)
		{
			printf("Enter a valid value.\n");
		}
	}
	while(choice != 1 && choice != 0);
	
	printf("x = %f\n",calc_quadratic_eq_roots(a,b,c,choice));
}
