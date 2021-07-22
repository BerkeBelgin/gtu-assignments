#include <stdio.h>
#include <math.h>

void calc_roots(int a, int b, int c, double *root1, double *root2)
{
	*root1 = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
	*root2 = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
}

int main()
{
	int a, b, c;
	double root1, root2;
	
	printf("a = ");
	scanf("%d", &a);
	printf("b = ");
	scanf("%d", &b);
	printf("c = ");
	scanf("%d", &c);
	
	calc_roots(a, b, c, &root1, &root2);
	
	printf("root1 = %.1f & root2 = %.1f\n", root1, root2);
}
