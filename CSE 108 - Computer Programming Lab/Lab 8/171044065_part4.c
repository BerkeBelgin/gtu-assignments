#include <stdio.h>

int max(int *n, int size)
{
	if(size > 0)
	{
		size--;
		if(n[size] > n[size - 1])
		{
			n[size - 1] = n[size];
		}
		max(n, size);
	}
	
	return n[0];
}

int main()
{
	int n[] = {-10, -5 ,-2};
	int size = sizeof(n) / sizeof(n[0]);
	
	printf("Max = %d\n", max(n, size));
}
