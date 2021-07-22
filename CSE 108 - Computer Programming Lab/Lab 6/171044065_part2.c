#include <stdio.h>

float powr(float x, int y)
{
	float z = 1;
	for(int i = 0; i < y; i++)
	{
		z *= x;
	}
	return z;
}

long long fac(int n)
{
	long long res = 1;
	
	while(n > 0)
	{
		res *= n;
		n--;
	}
	
	return res;
}

double mysine(double x)
{
	double result = 0;
	
	x = x  * 3.14 / 180;
	
	for(int i = 0; i < 8; i++)
	{
		result += powr(-1, i) * (powr(x, 2 * i + 1)/fac(2 * i + 1));
	}
	
	return result;
}

int main()
{
	double input;
	printf("Sinus: ");
	scanf("%lf", &input);
	printf("sin(%g) = %.2g\n", input, mysine(input));
}
