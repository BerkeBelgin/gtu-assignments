#include <stdio.h>
#include <string.h>
#include <ctype.h>

//We define a struct type with 4 empty arrays which will help us hold data temporarily.
struct Accounts 
{
	char name[60];
	char surname[60];
	char mail[60];
	char id[60];
};

//We instantiate an instance of the struct above.
struct Accounts Temp;

//Two variables to hold all of a line in the text and to hold a word in that line.
char line[60];
char word[60];

//n'th character of the "word" array.
int n;

//Values that check if a word is a mail, name or surname.
int isID;
int isSurname;
int isMail;

//Two file pointers, one is for reading and the other one is for writing.
FILE *read_fp;
FILE *write_fp;

//The function that understands which one is name, surname etc. and stores.
void Fill(char input[60])
{	
	isID = 1;
	isSurname = 1;
	isMail = 0;

	for(int i = 0; i < strlen(input); i++)
	{
		if(input[i] == '@')
		{
			isMail = 1;
			break;
		}

		if(!isdigit(input[i]))
		{
			isID = 0;
		}

		if(!isupper(input[i]))
		{
			isSurname = 0;
		}
	}

	if(isMail)
	{
		strcpy(Temp.mail, input);
	}
	else if(isID)
	{
		strcpy(Temp.id, input);
	}
	else if(isSurname)
	{
		strcpy(Temp.surname, input);
	}
	else
	{
		strcpy(Temp.name, input);
	}
}

//The function that reads the text and takes the whole word to the Fill() function.
void Read()
{
	n = 0;

	//We assign one line of read_fp to "line" array.
	fgets(line, 60, read_fp);

	for(int i = 0;line[i] != '\0';i++)
	{		
		if(isspace(line[i]) && word[n - 1] != '\0')
		{
			Fill(word);
			memset(word,'\0',60);
			n = 0;
		}
		else if(!isspace(line[i]) || word[n - 1] != '\0')
		{
			word[n] = line[i];
			n++;
		}
	}
}

//We print the values everytime this function called.
void Write()
{	
	fprintf(write_fp, "%-12s%-12s%-30s%-12s\n", Temp.name, Temp.surname, Temp.mail, Temp.id);
}

int main()
{	
	//We call files as fopen("filename.txt", purpose of operation ("r" for read, "w" for write)).
	read_fp = fopen("hw4_disordered_people.txt", "r");
	write_fp = fopen("hw4_ordered_people.txt", "w");

	//Titles of every column and values below them. 	
	fprintf(write_fp, "%-12s%-12s%-30s%-12s\n\n", "Name", "Surname", "Mail", "ID");

	while(!feof(read_fp))
	{
		Read();
		Write();
	}

	//We close the files in order to drop them from RAM.
	fclose(read_fp);
	fclose(write_fp);
}
