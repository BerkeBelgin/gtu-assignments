#include <stdio.h>

int n;

void reverse_print(char *str)
{	
	if(n >= 0)
	{
		if(str[n] != '\n')
		{
			printf("%c", str[n]);
		}
		n--;
		reverse_print(str);		
	}
}

int main()
{
	char str[36];
	printf("Please enter a word: ");
	
	
	for(int i = 0; i < 36; i++)
	{
		scanf("%c", &str[i]);
		if(str[i] == '\n')
		{
			break;
		}
		n++;
	}
	
	reverse_print(str);
	printf("\n");
}
