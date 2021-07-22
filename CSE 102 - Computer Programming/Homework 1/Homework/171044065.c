#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define PI 3.14
#define Red 0
#define Yellow 1
#define Blue 2
#define Black 3
#define White 4
#define Square 1
#define Rectangular 2
#define Circular 3

int fsqrt(int x)
{
	for(int i =  0; i <= x; i++)
	{
		if(i * i == x)
		{
			return i;
			break;
		}
	}
}

void Print_Rect(double vol)
{
	for(int i = 0; i < 5; i++)
	{
		for(int i = 0; i < ((int) vol) / 5; i++)
		{
			printf("X");
		}
		printf("\n");
	}
}

void Print_Circ(double vol)
{
	int x = fsqrt((int) (vol / PI));
	int y;
	
	if(x < 1)
	{
		printf("Please enter a number that greater than 0.\n");
	}
	else if(x % 2 == 0)
	{
		y = (x - 2)/2;
		
		//Top	
		for(int i = 0;i < (x - 2)/2;i++)
		{
			printf("\t");
		}
		printf("    X\n");
		
		//Decreasing
		for(int i = 0;i < (x - 2)/2;i++)
		{
			for(int i = 0;i < y;i++)
			{
				printf("\t");
			}
			printf("X");
			for(int i = 0;i < (x - 1) - y * 2;i++)
			{
				printf("\t");
			}
			printf("X\n");
			y--;
		}
		
		//Middle
		printf("X");
		for(int i = 0;i < x - 1;i++)
		{
			printf("\t");
		}
		printf("X\n");
		
		//Increasing
		for(int i = 0;i < (x - 2)/2;i++)
		{
			y++;
			for(int i = 0;i < y;i++)
			{
				printf("\t");
			}
			printf("X");
			for(int i = 0;i < (x - 1) - y * 2;i++)
			{
				printf("\t");
			}
			printf("X\n");
		}
		
		//Bottom
		for(int i = 0;i < (x - 2)/2;i++)
		{
			printf("\t");
		}
		printf("    X\n");
	}
	else
	{	
		if(x == 1)
		{
			printf("X\n");
		}
		else
		{
			y = (x - 1)/2;
			
			//Top
			for(int i = 0; i < (x - 1)/2; i++)
			{
				for(int i = 0; i < y; i++)
				{
					printf("\t");
				}
				printf("X");
				
				for(int i = y; i < (x - 1)/2; i++)
				{
					printf("\t\t");
				}
				if(y < (x - 1)/2)
				{
					printf("X");
				}
				
				printf("\n");
				y--;
			}
			
			//Middle
			printf("X");
			for(int i = 0; i < x - 1; i++)
			{
				printf("\t");
			}
			printf("X\n");
			
			//Bottom
			for(int i = 0; i < (x - 1)/2; i++)
			{
				y++;
				
				for(int i = 0; i < y; i++)
				{
					printf("\t");
				}
				printf("X");
				
				for(int i = y; i < (x - 1)/2; i++)
				{
					printf("\t\t");
				}
				if(y < (x - 1)/2)
				{
					printf("X");
				}
				
				printf("\n");
			}
		}
	}
}

void Print_Cube(double vol)
{
	for(int i = 0; i < fsqrt((int) vol); i++)
	{
		for(int i = 0; i < fsqrt((int) vol); i++)
		{
			printf("X");
		}
		printf("\n");
	}
}

double CreateBody(int shape)
{
	int size, size2;
	
	printf("Enter a length: ");
	scanf("%d",&size);
	printf("\n");
	
	if(shape == Square)
	{
		return (double) (size * size);
	}
	else if(shape == Rectangular)
	{
		printf("Enter the other length: ");
		scanf("%d",&size2);
		printf("\n");
		
		return (double) (size * size2);
	}
	else if(shape == Circular)
	{
		return (double) size * (double) size * PI;
	}
}

int SetColor(int color)
{
	if(color >= 0 && color <= 1000)
	{
		return color % 5;
	}
	else
	{
		return 1;
	}
}

double LoadMoves(int shape, double size_of_body)
{
	if(shape == Square)
	{
		return 4.0 * (double) fsqrt((int) size_of_body);
	}
	else if(shape == Rectangular)
	{
		return ((size_of_body)/5.0 + 5.0) * 2.0;
	}
	else if(shape == Circular)
	{
		return 2.0 * PI * (double) fsqrt((int) (size_of_body / PI));
	}
}

int SetAttackPower(int lower_bound, int upper_bound)
{
	srand(time(NULL));
	return (rand() % ((upper_bound + 1) - lower_bound)) + lower_bound;
}

void ShowPokemon(int shape, double body_size, int color, double move_length, int attack_power)
{
	char colr[7];
	
	switch (color)
	{
		case Red:
			strcpy(colr, "Red");
			break;
		
		case Yellow:
			strcpy(colr, "Yellow");
			break;
			
		case Blue:
			strcpy(colr, "Blue");
			break;
			
		case Black:
			strcpy(colr, "Black");
			break;
			
		case White:
			strcpy(colr, "White");
			break;
	}
	
	if(shape == Square)
	{
		Print_Cube(body_size);
		printf("Name: Square Pokémon\n");
		printf("Size: %d\n", (int) body_size);
		printf("Color: %s\n",colr);
		printf("Move: %d\n", (int) move_length);
	}
	else if(shape == Rectangular)
	{
		Print_Rect(body_size);
		printf("Name: Rectangular Pokémon\n");
		printf("Size: %d\n", (int) body_size);
		printf("Color: %s\n",colr);
		printf("Move: %g\n", move_length);
	}
	else if(shape == Circular)
	{
		Print_Circ(body_size);
		printf("Name: Circular Pokémon\n");
		printf("Size: %g\n", body_size);
		printf("Color: %s\n",colr);
		printf("Move: %g\n", move_length);
	}
	
	printf("Attack Power: %d\n", attack_power);
}

int main ()
{
	int shape, color, attack_power;
	double size_of_body, move_length;
	
	shape = Square;
	size_of_body = CreateBody(shape);
	color = 798;
	color = SetColor(color);
	move_length = LoadMoves(shape, size_of_body);
	attack_power = SetAttackPower (0, 150);
	ShowPokemon(shape, size_of_body, color, move_length, attack_power);
}
