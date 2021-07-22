#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define up -1
#define down 1
#define right 1
#define left -1

int nest_x;
int nest_y;
int ant_x;
int ant_y;
int mov;
int points = 0;

void print_the_grid(int x_pos_ant, int y_pos_ant, int x_pos_nest, int y_pos_nest)
{
	for(int y = 0;y < 10;y++)
	{
		for(int x = 0;x < 10;x++)
		{
			if(y == y_pos_nest && x == x_pos_nest)
			{
				printf("O\t");
			}
			else if(y == y_pos_ant && x == x_pos_ant)
			{
				printf("X\t");
			}
			else
			{
				printf(".\t");
			}
		}
		printf("\n");
	}
}

int find_min_path(int x_pos_ant, int y_pos_ant, int x_pos_nest, int y_pos_nest)
{
	printf("\n");
	if(x_pos_ant < x_pos_nest && y_pos_ant < y_pos_nest)
	{
		ant_x += right;
		ant_y += down;
		points += 5;
	}
	else if(x_pos_ant == x_pos_nest && y_pos_ant < y_pos_nest)
	{
		ant_y += down;
		points += 4;
	}
	else if(x_pos_ant > x_pos_nest && y_pos_ant < y_pos_nest)
	{
		ant_x += left;
		ant_y += down;
		points += 5;
	}
	else if(x_pos_ant < x_pos_nest && y_pos_ant == y_pos_nest)
	{
		ant_x += right;
		points += 3;
	}
	else if(x_pos_ant > x_pos_nest && y_pos_ant == y_pos_nest)
	{
		ant_x += left;
		points += 3;
	}
	else if(x_pos_ant < x_pos_nest && y_pos_ant > y_pos_nest)
	{
		ant_x += right;
		ant_y += up;
		points += 5;
	}
	else if(x_pos_ant == x_pos_nest && y_pos_ant > y_pos_nest)
	{
		ant_y += up;
		points += 4;
	}
	else if(x_pos_ant > x_pos_nest && y_pos_ant > y_pos_nest)
	{
		ant_x += left;
		ant_y += up;
		points += 5;
	}
}

void control()
{
	scanf("%d", &mov);
	
	switch(mov)
	{
		case 1:
		ant_x += left;
		ant_y += down;
		points += 5;
		break;
		
		case 2:
		ant_y += down;
		points += 4;
		break;
		
		case 3:
		ant_x += right;
		ant_y += down;
		points += 5;
		break;
		
		case 4:
		ant_x += left;
		points += 3;
		break;
		
		case 6:
		ant_x += right;
		points += 3;
		break;
		
		case 7:
		ant_x += left;
		ant_y += up;
		points += 5;
		break;
		
		case 8:
		ant_y += up;
		points += 4;
		break;
		
		case 9:
		ant_x += right;
		ant_y += up;
		points += 5;
		break;
	}
}

int main()
{	
	ant_x = 0;
	ant_y = 0;
	
	srand(time(NULL));
	do
	{
		nest_x = rand() % 10;
		nest_y = rand() % 10;
	}
	while(nest_x == 0 && nest_y == 0);
	
	while(nest_x != ant_x || nest_y != ant_y)
	{
		print_the_grid(ant_x, ant_y, nest_x, nest_y);
		find_min_path(ant_x, ant_y, nest_x, nest_y);
	}
	
	printf("The minimum distance of the trip is: %d\n", points);
}
