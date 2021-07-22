#include <stdio.h>

int notes[2];
int avr;
char grade;

int main() 
{
	for(int i = 0; i < 3; i++)
	{
		for(int i = 0; i < 2; i++)
		{
			printf("Input: ");
			scanf("%d", &notes[i]);
		}
	
		avr = (notes[0] * 40 + notes[1] * 60) / 100;
	
		if(avr >= 90)
		{
			grade = 'A';
		}
		else if(avr < 90 && avr >= 80)
		{
			grade = 'B';
		}
		else if(avr < 80 && avr >= 70)
		{
			grade = 'C';
		}
		else if(avr < 70 && avr >= 60)
		{
			grade = 'D';
		}
		else if(avr < 60)
		{
			grade = 'F';
		}
	
		printf("%c\n", grade);
	}
}
