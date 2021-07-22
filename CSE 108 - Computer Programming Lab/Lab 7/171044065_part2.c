#include <stdio.h>
#include <string.h>

void word_counter(char text[300], int counters[150], char words[150][20])
{
	char word[20];
	int word_n = 0;
	int len = 0;
	int n = 0;
	
	for(int i = 0; i < 300; i++)
	{
		len++;
		if(text[i] == ' ' || text[i] == '.' || text[i] == ',')
		{
			for(int i = 0; i < 150; i++)
			{
				if(strcmp(word, words[i]))
				{
					counters[i]++;
				}
			}
			
			//clean
			for(int i = 0; i < 20; i++)
			{
				word[i] = '\0';
			}
			n = 0;
			word_n++;
		}
		word[n] = text[i];
		n++;
	}
	
	for(int i = 0; i < 150; i++)
	{
		printf("%d\n", counters[i]);
	}
}

int main()
{
	char text[300] = "This is a text which has some typos. You should correct the text, because you will use the text to test your check_typos function. Therefore, try to correct all typos in the test. This part of the text is correct, so no correction should be done on this part.";
	int counters[150];
	char words[150][20];
	
	word_counter(text, counters, words);
}
