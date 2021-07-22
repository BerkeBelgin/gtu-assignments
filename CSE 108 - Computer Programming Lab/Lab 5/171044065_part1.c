#include <stdio.h>

void get_min_max(int *min,int *max)
{
	int a, b, c, res_min, res_max;
	
	printf("Input: ");
	scanf("%d%d%d", &a, &b, &c);
	
	if(a < c)
	{
		a = a + c;
		c = a - c;
		a = a - c;
	}
	if(b < c)
	{
		b = b + c;
		c = b - c;
		b = b - c;
	}
	if(a < b)
	{
		a = a + b;
		b = a - b;
		a = a - b;
	}
	
	*max = a;
	*min = c;
}

int main()
{
	int max, min;
	double avr;
	
	get_min_max(&min, &max);
	avr = (double) (max + min) / (double) 2;
	printf("Min: %d, Max: %d, Average: %.1f\n", min, max, avr);
}
