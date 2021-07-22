#include <stdio.h>

int notes[3];

void makeup_exam(int midterm, int final, int absenteeism)
{
	int value;
	
	value = (midterm * 40 + final * 60) / 100;
	
	if(value > 59.5 || absenteeism > 80)
	{
		printf("Not Allowed\n");
	}
	else
	{
		printf("Allowed\n");
	}
}

int main() 
{	
	for(int i = 0; i < 3; i++)
	{
		printf("Midterm input: ");
		scanf("%d",&notes[0]);
		printf("Final input: ");
		scanf("%d",&notes[1]);
		printf("Absenteeism input: ");
		scanf("%d",&notes[2]);
		
		makeup_exam(notes[0], notes[1], notes[2]);
	}
}
