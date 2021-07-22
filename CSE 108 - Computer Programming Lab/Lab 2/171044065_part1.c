#include <stdio.h>

float r, area;
float pi = 3.14;

int main()
{
	printf("r = ");
	scanf("%f",&r);
	area = 4 * pi * r * r;
	printf("Area of sphere: %f\n",area);
}
