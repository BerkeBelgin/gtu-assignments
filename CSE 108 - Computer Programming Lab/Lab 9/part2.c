#include <stdio.h>

struct CN
{
	float x;
	float y;
};

struct CN add_complex(struct CN a, struct CN b)
{
	struct CN res;
	res.x = a.x + b.x;
	res.y = a.y + b.y;
	return res;
}

struct CN sub_complex(struct CN a, struct CN b)
{
	struct CN res;
	res.x = a.x - b.x;
	res.y = a.y - b.y;
	return res;
}

int main()
{
	struct CN cmpx1;
	struct CN cmpx2;
	
	struct CN add;
	struct CN sub;
	
	printf("Enter the 1st complex number: ");
	scanf("%f %f", &cmpx1.x, &cmpx1.y);
	
	printf("Enter the 2nd complex number: ");
	scanf("%f %f", &cmpx2.x, &cmpx2.y);
	
	add = add_complex(cmpx1, cmpx2);
	sub = sub_complex(cmpx1, cmpx2);
	
	printf("Addition: %g + %gi\n", add.x, add.y);
	printf("Subtraction: %g + %gi\n", sub.x, sub.y);
}
