#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//A function that returns absolute value of a number
int abs(int num)
{
	if(num < 0)
	{
		num *= -1;
	}
	
	return num;
}

//A function that returns n'th power of two
int pow2(int x)
{
	int res = 1;
	
	for(int i = 0;i < x;i++)
	{
		res *= 2;
	}
	
	return res;
}

int make_a_guess(int trial, int min, int max)
{
	int guess;
	
	printf("(Trial: %d) Make a guess between %d and %d: ", trial, min, max);
	scanf("%d", &guess);
	
	return guess;
}

void show_scores(int score_human, int score_program)
{
	printf("Your Score: %d\nProgram Score: %d\n", score_human, score_program);
}

void lucky_number(int *usr_p, int *mchn_p)
{
	int ln = (rand() % 1024) + 1;	
	int user_guess;
	int try = 8;
	int num_min = 1;
	int num_max = 1024;
	int distance = 10;
	
	for(int i = 1; (i <= try) && distance != 0; i++)
	{
		user_guess = make_a_guess(i, num_min, num_max);
		
		for(int i = 0; i < 10; i++)
		{
			if(abs(user_guess - ln) >= pow2(i) && abs(user_guess - ln) < pow2(i + 1))
			{
				distance = i + 1;
			}
			else if(user_guess == ln)
			{
				distance = 0;
			}
		}
		
		if(distance == 0)
		{
			printf("Distance: %d You win!\n\n", distance);
			++*usr_p;
		}
		else if(i == 8 && distance != 0)
		{
			printf("Distance: %d\n", distance);
			++*mchn_p;
		}
		else
		{
			printf("Distance: %d\n", distance);
		}
		
				
		if(user_guess > num_min && user_guess < ln)
		{
			num_min = user_guess;
		}
		else if(user_guess < num_max && user_guess > ln)
		{
			num_max = user_guess;
		}
	}
	show_scores(*usr_p, *mchn_p);
	printf("\n");
}

void draw_hourglass (int height)
{
	int cpy = 0;
	
	printf("\n");
	for(int i = 0; i < (height - 1) / 2; i++)
	{
		for(int i = 0; i < cpy / 2; i++)
		{
			printf(" ");
		}
		for(int i = 0; i < height - cpy; i++)
		{
			printf("*");
		}
		cpy += 2;
		printf("\n");
	}
	for(int i = 0; i < (height + 1) / 2; i++)
	{
		for(int i = 0; i < cpy / 2; i++)
		{
			printf(" ");
		}
		for(int i = 0; i < height - cpy; i++)
		{
			printf("*");
		}
		cpy -= 2;
		printf("\n");
	}
	printf("\n");
}

void draw_mountain_road (int length, int max_radius)
{
	int r;
	int spc;
	int start_orientation = rand() % 2;
	
	for(int i = 0; i < length; i++)
	{
		r = rand() % max_radius + 1;
		
		if((i + start_orientation) % 2 == 1)//!!!
		{
			spc = r;
			for(int i = 0; i < r; i++)
			{
				for(int i = 0; i < max_radius - r; i++)
				{
					printf(" ");
				}
				for(int i = 0; i < spc; i++)
				{
					printf(" ");
				}
				printf("/\n");
				spc--;
			}
			
			spc++;
			for(int i = 0; i < max_radius - r; i++)
			{
				printf(" ");
			}
			printf("|\n");
			
			for(int i = 0; i < r; i++)
			{
				for(int i = 0; i < max_radius - r; i++)
				{
					printf(" ");
				}
				for(int i = 0; i < spc; i++)
				{
					printf(" ");
				}
				printf("\\\n");
				spc++;
			}
		}		
		else if((i + start_orientation) % 2 == 0)//!!!
		{
			spc = 1;
			for(int i = 0; i < r; i++)
			{
				for(int i = 0; i < max_radius; i++)
				{
					printf(" ");
				}
				for(int i = 0; i < spc; i++)
				{
					printf(" ");
				}
				printf("\\\n");
				spc++;
			}
			
			for(int i = 0; i < max_radius; i++)
			{
				printf(" ");
			}
			for(int i = 0; i < spc; i++)
			{
				printf(" ");
			}
			printf("|\n");
			spc--;
			
			for(int i = 0; i < r; i++)
			{
				for(int i = 0; i < max_radius; i++)
				{
					printf(" ");
				}
				for(int i = 0; i < spc; i++)
				{
					printf(" ");
				}
				printf("/\n");
				spc--;
			}
		}
	}
	printf("\n");
}

void menu()
{
	int user_score = 0;
	int machine_score = 0;
	
	int hourglass_h = 1;
	
	int length;
	int max_r;
	
	int choice;
	
	while(choice != 4)
	{
		printf("***** MENU *****\n");
		printf("1. Play Lucky Number\n");
		printf("2. Draw Hourglass\n");
		printf("3. Draw Mountain Road\n");
		printf("4. Exit\n");
		printf("\nPlease enter a number between 1 and 4.\n");
		do
		{
			//This line below prevents program to enter infinite loop in case user enters a float or double.
			choice = 4;
			
			printf("Choice: ");
			scanf("%d",&choice);
			printf("\n");
			
			switch(choice)
			{
				case 1:
					lucky_number(&user_score, &machine_score);
					break;
					
				case 2:
					do
					{
						printf("Enter a height: ");
						scanf("%d", &hourglass_h);
						if(hourglass_h % 2 == 0)
						{
							printf("\nPlease enter an odd number.\n");
						}
					}
					while(hourglass_h % 2 == 0);
					
					draw_hourglass (hourglass_h);
					break;
					
				case 3:
					printf("Enter the length: ");
					scanf("%d", &length);
					
					printf("Enter the maximum radius: ");
					scanf("%d", &max_r);
					
					if(max_r > 0)
					{
						draw_mountain_road(length, max_r);
					}
					break;
			}
			
			if(choice < 1 || choice > 4)
			{
				printf("This is an invalid choice. Try again!\n");
			}
		}
		while(choice < 1 || choice > 4);
	}
}

int main()
{
	srand(time(NULL));
	menu();
}
