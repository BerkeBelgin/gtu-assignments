#include<stdio.h>
#include <stdlib.h>

//******************** Addition ********************//

#include <time.h>
#define TABLE_SIZE 15

//******************** Addition ********************//

#define DICT_SIZE 15
#define WORD_LEN 10
#define LINE_LEN 18

int get_line_size(char *line) {
	char *ch_iter = line; // so as not to lose beginning of line
	int counter = 0;
	// go until you see new line or null char
	while(*ch_iter != '\n' && *ch_iter != '\0') {
		ch_iter++; // next char
		counter++; // increment counter
	}
	
	return counter;
}

void copy_string(char *source, char *destination) {
	// get iterators over original pointers
	char *src_iter = source;
	char *dst_iter = destination;
	// until null char
	while (*src_iter != '\0') {
		// copy pointers
		*dst_iter = *src_iter;
		// advance to next char
		src_iter++;
		dst_iter++;
   }
   // terminate string
   *dst_iter = '\0';
}

void remove_newline(char *line) {
	char *ch_iter = line;
	// go until you see new line
	while(*ch_iter != '\n') {
		ch_iter++; // next char
	}
	*ch_iter = '\0'; // overwrite new line
}

void print_dictionary(char *dict[]) {
	int i;
	for(i = 0 ; i < DICT_SIZE ; i++) {
		printf("%s\n", dict[i]);
	}
}

void print_coord(int coord[DICT_SIZE][4]) {
	int i, j;
	for(i = 0 ; i < DICT_SIZE ; i++) {
		for(j = 0 ; j < 4 ; j++) {
			printf("%d ", coord[i][j]);
		}
		printf("\n");
	}
}

//******************** Addition ********************//

//A function to compare if two strings are the same
int str_cmp(char *str1, char *str2)
{
	int res = 1;
	
	for(int i = 0; str1[i] != '\0' || str2[i] != '\0'; i++)
	{
		if(str1[i] != str2[i])
		{
			res = 0;
		}
	}
	return res;
}

//A function to create a random number between 97 - 122
int rand_num()
{
	return (rand() % 26) + 97;
}

//A function to return absolute value of an int
int absolute(int n)
{
	if(n < 0)
	{
		return (n * -1);
	}
}

//Function that prints the character table
void print_table(int table[TABLE_SIZE][TABLE_SIZE])
{
	for(int y = 0; y < TABLE_SIZE; y++)
	{
		for(int x = 0; x < TABLE_SIZE; x++)
		{
			printf(" %c ", table[y][x]);
		}
		printf("\n");
	}
}

//Function that fills tha table either with random characters or the words given
void fill_table(int table[TABLE_SIZE][TABLE_SIZE], char *dict[DICT_SIZE], int coord[DICT_SIZE][4])
{

	//First filled all tha table with random characters	
	for(int y = 0; y < TABLE_SIZE; y++)
	{
		for(int x = 0; x < TABLE_SIZE; x++)
		{
			table[y][x] = rand_num();
		}
	}
	
	int length;
	int x_step;
	int y_step;
	
	//Then replaced the words given with the random characters on the table
	for(int i = 0; i < DICT_SIZE; i++)
	{
		length = 0;
		x_step = 0;
		y_step = 0;
		
		//I take the length of the word and check which orientation the word placed on the table
		if(absolute(coord[i][2] - coord[i][0]) > 0)
		{
			length = absolute(coord[i][2] - coord[i][0]);
			x_step = absolute(coord[i][2] - coord[i][0]) / (coord[i][2] - coord[i][0]);
		}
		if(absolute(coord[i][3] - coord[i][1]) > 0)
		{
			length = absolute(coord[i][3] - coord[i][1]);
			y_step = absolute(coord[i][3] - coord[i][1]) / (coord[i][3] - coord[i][1]);
		}
		
		//Place the word on table
		for(int n = 0; n <= length; n++)
		{
			table[(coord[i][1] + (y_step * n))][coord[i][0] + (x_step * n)] = dict[i][n];
		}
	}
}

//Main game function
void game(int table[TABLE_SIZE][TABLE_SIZE])
{
	char guess[24];
	int len = 0;
	
	int x;
	int y;
	
	int end = 0;
	
	//2d array that stores values to check the entered word on 8 directions
	int check[3][8] = 
	{
		{1, 1, 1,  1,  1,  1,  1,  1},
		{0, 1, 1,  1,  0, -1, -1, -1},
		{1, 1, 0, -1, -1, -1,  0,  1}
	};
	
	//while the amount of the words guessed correctly is less than the dictionary size
	while(end < DICT_SIZE)
	{
		//clear screen than print table		
		printf("\e[1;1H\e[2J");
		print_table(table);

		printf("\nWord (Enter \"exit game\" to quit): ");
		scanf(" %[^\n]", guess);
		
		//if entered "exit game" quit game
		if(str_cmp(guess, "exit game"))
		{
			break;
		}

		//printf("Top-left corner is on [0,0] point.\n\n");
		
		printf("Column: ");
		scanf("%d", &x);
		
		printf("Row: ");
		scanf("%d", &y);
		
		//takes the length of the guessed word
		for(int i = 0; i < 24; i++)
		{
			if(guess[i] != '\n' && guess[i] != '\0' && guess[i] != ' ')
			{
				len = i + 1;
			}
			else
			{
				break;
			}
		}
		
		//sets true (the word guessed exists for 8 directions) all directions
		for(int i = 0; i < 8; i++)
		{
			check[0][i] = 1;
		}
		
		//for 8 directions		
		for(int n = 0; n < 8; n++)
		{
			//for the every character of the word			
			for(int i = 0; i < len; i++)
			{
				//if the character isn't equal to the character on the table				
				if(guess[i] != table[y + (check[1][n] * i)][x + (check[2][n] * i)] && guess[i] != table[y + (check[1][n] * i)][x + (check[2][n] * i)] + 32
				&& guess[(len - i) - 1] != table[y + (check[1][n] * i)][x + (check[2][n] * i)] && guess[(len - i) - 1] != table[y + (check[1][n] * i)][x + (check[2][n] * i)] + 32)
				{
					check[0][n] = 0;
				}
			}
			
			//if the word is correct swap every character with capital ones
			if(check[0][n] == 1)
			{
				for(int i = 0; i < len; i++)
				{
					if(table[y + (check[1][n] * i)][x + (check[2][n] * i)] >= 97)
					{
						table[y + (check[1][n] * i)][x + (check[2][n] * i)] -= 32;
					}
				}
				end++; //increases the amount of correctly guessed words by one
			}
		}
		if(end == DICT_SIZE)
		{
			printf("\n\nCongratulations, you win!\n\n");
		}
	}
}

//******************** Addition ********************//

int main(){
	char *dict[DICT_SIZE];
    int coord[DICT_SIZE][4];    
    char line[LINE_LEN];
	FILE *fp = fopen("word_hunter.dat", "r");
	
	int line_counter = 0;
	int dict_counter = 0;
	while(fgets(line, LINE_LEN, fp) != NULL) {
		if(line_counter%5 == 0) {
			dict[dict_counter] = (char*) malloc(sizeof(char) * get_line_size(line));
			remove_newline(line);
			copy_string(line, dict[dict_counter]);
		} else if (line_counter%5 == 1){
			coord[dict_counter][0] = atoi(line);
		} else if (line_counter%5 == 2){			
			coord[dict_counter][1] = atoi(line);		
		} else if (line_counter%5 == 3){
			coord[dict_counter][2] = atoi(line);
		} else if (line_counter%5 == 4){
			coord[dict_counter][3] = atoi(line);
			dict_counter++;
		}
		line_counter++;
	}
	
	fclose(fp);
	//print_dictionary(dict);
	//print_coord(coord);
	
	// WRITE HERE...
	//******************** Addition ********************//
	srand(time(NULL));
	
	//the 2d array that stores table data
	int table[TABLE_SIZE][TABLE_SIZE];
	
	fill_table(table, dict, coord);
	
	game(table);
	
	//******************** Addition ********************//
		
	return 0;
}






