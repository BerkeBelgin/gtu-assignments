#include <stdio.h>

void read_forecast(float wf[4][7])
{
	printf("\n");
	for(int i = 0; i < 4; i++)
	{
		for(int n = 0; n < 7; n++)
		{
			printf("%-6.1f", wf[i][n]);
		}
		printf("\n");
	}
}

void city_avr(float wf[4][7], float ave[4][3])
{
	printf("\n");
	
	float total;
	
	for(int y = 0; y < 4; y++)
	{
		for(int z = 0; z < 3; z++)
		{
			total = 0;
			for(int x = 0; x < 5; x++)
			{
				total += wf[y][x + z];
			}
			ave[y][z] = total / 5.0;
			printf("%-6.1f", ave[y][z]);
		}
		printf("\n");
	}
}

void select_city_and_day(float ave[4][3])
{
	printf("\n");
	for(int y = 0; y < 4; y++)
	{
		for(int x = 0; x < 3; x++)
		{
			if(ave[y][x] >= 20.0)
			{
				printf("City %d, Days %d: %.1f\n", y + 1, x + 1, ave[y][x]);
			}
		}
	}
}

int main()
{
	float wf[4][7]= 
	{
	(0, 8), (0 ,12), (0 ,17), (0 ,19), (0 ,19), (0 ,17), (0 ,14),
	(1, 12.5), (1 ,16), (1 ,19.5), (1 ,18), (1 ,17), (1 ,12), (1 ,11.5),
	(2, 4), (2 ,21), (2 ,19), (2 ,20), (2 ,20), (2 ,19), (2 ,18),
	(3, 18), (3 ,21.5), (3 ,21), (3 ,19), (3 ,20), (3 ,22), (3 ,21)
	};
	float ave[4][3];
	
	read_forecast(wf);
	city_avr(wf, ave);
	select_city_and_day(ave);
}




















