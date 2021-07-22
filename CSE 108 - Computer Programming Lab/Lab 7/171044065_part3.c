#include <stdio.h>

int find_longest_word(char text[1000])
{
	char word[24];
	
	int word_n = 0;
	int length = 0;
	
	int result_word_n = 0;
	int result_len = 0;
	
	for(int i = 0; i < 1000; i++)
	{
		if(text[i] == ' ' || text[i] == '.' || text[i] == ',')
		{
			if(length > result_len)
			{
				result_len = length;
				result_word_n = word_n;
			}
			word_n = i + 1;
			length = 0;
		}
		length++;
	}
	
	for(int i = 0; i < 24; i++)
	{
		word[i] = text[result_word_n + i];
		
		if(text[result_word_n + i] == ' ' || text[result_word_n + i] == '.' || text[result_word_n + i] == ',')
		{
			word[i] = '\0';
			break;
		}
	}
	result_len--;
	printf("The longest word is %s with the number of %d letters.\n", word, result_len );
	
	return result_len;
}

int main()
{
	char text[1000] = "The Silmarillion is a collection of mythopoeic works by English writer J. R. R. Tolkien, edited and published posthumously by his son, Christopher Tolkien, in 1977, with from fdgdhggfdhgfhgfhfdhgfdgfdg Guy Gavriel Kay...";
	
	find_longest_word(text);
}
