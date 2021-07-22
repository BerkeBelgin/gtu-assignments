#include <stdio.h>

void fix(char *str)
{
	int n = 0;
	
	for(int i = n; i < 300; i++)
	{
		if(str[i] == '\0')
		{
			n++;
		}
		if(str[i] != '\0')
		{
			str[i - n] = str[i];
		}
	}
	
	for(int i = n; i >= 0; i--)
	{
		str[299 - i] = '\0';
	}
}


void leavespace(char *str, int n)
{
	for(int i = 299; i > n; i--)
	{
		str[i] = str[i - 1];
	}
	
	str[n] = ' ';
}


void typo_check(char *text)
{
	for (int i = 0; i < 299; i++)
	{
		if(text[i] == ' ' && text[i + 1] == ' ')
		{
			text[i] = '\0';
		}
	}
	fix(text);
	
	
	for(int i = 0; i < 300; i++)
	{
		if((text[i] == ',' || text[i] == '.') && text[i + 1] != ' ')
		{
			leavespace(text, i + 1);
		}
	}
	
	
	for(int i = 0; i < 300; i++)
	{
		if((text[i] >= 97 && text[i] <= 122) && (i == 0 || text[i - 2] == '.'))
		{
			text[i] -= 32;
		}
		if((text[i] <= 90 && text[i] >= 65) && ( i != 0 && text[i - 2] != '.'))
		{
			text[i] += 32;
		}
	}
	
	//last fix
	for(int i = 299; i >= 0; i--)
	{
		if( text[i] != '\0' && text[i + 1] == '\0')
		{
			text[i + 1] = '.';
		}
	}
}

int main()
{
	char plain_text[300] = "this Is a text which has some typos.   should         correct tHe text,because you will use the Text to test your check_typos function.therefore, try to correct all typos iN the test. This PART of the text is correct, so no correction should be done on this part.";
	
	typo_check(plain_text);
	
	printf("%s\n", plain_text);
	
	return 0;
}
