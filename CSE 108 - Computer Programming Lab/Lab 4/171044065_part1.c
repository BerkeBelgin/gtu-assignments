#include <stdio.h>

int num;
int cur;
int count;

int print;

int main()
{
	printf("Please enter a number to find prime numbers that are smaller than the number:\n");
	scanf("%d",&num);
	
	cur = 2;
	count = 0;
	
	while(cur < num)
	{
		print = 1;
		
		for(int i = 2;i < cur; i++)
		{
			if(cur % i == 0)
			{
				print = 0;
			}
		}
		
		if(print == 1 || cur == 2)
		{
			printf("%d ",cur);
			count++;
		}
		
		cur++;
	}
	
	printf("\nThere are %d prime numbers which are smaller than 100\n", count);
}
