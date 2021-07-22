#include <stdio.h>

int F(char *str,int n, int size)
{
	if((size - n) >= 2)
	{
		if(str[n] == str[size])
		{
			F(str, n + 1, size -1);
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 1;
	}
}

int main()
{
	char str[36];
	int size;
	
	printf("Enter a string: ");
	for(int i = 0; i < 36; i++)
	{
		scanf("%c", &str[i]);
		if(str[i] == '\n')
		{
			break;
		}
		size = i;
	}
	printf("Result = %d\n", F(str, 0, size));
}
