#include <stdio.h>

//part 5 int *min

typedef struct
{
	char pixel;
	int x;
	int y;
}
pixel;

void fill_canvas(pixel canvas[8][14])
{
	char table[8][14] = 
	{
		{".............."},
		{".ssssssssssss."},
		{".| ---  --- |."},
		{".| (-)  (-) |."},
		{".|    /_    |."},
		{".|   ____   |."},
		{".|__________|."},
		{".............."},
	};
	
	for(int r = 0; r < 8; r++)
	{
		for(int c = 0; c < 14; c++)
		{
			canvas[r][c].x = c;
			canvas[r][c].y = r;
			canvas[r][c].pixel = table[r][c];
		}
	}
}

void show_canvas(pixel canvas[8][14])
{
	for(int r = 0; r < 8; r++)
	{
		for(int c = 0; c < 14; c++)
		{
			printf("%c", canvas[r][c].pixel);
		}
		printf("\n");
	}
}

void find_shape(pixel canvas[8][14], char *shape)
{
	int check = 0;
	
	for(int r = 0; r < 8; r++)
	{
		for(int c = 0; c < 14; c++)
		{
			if(canvas[r][c].pixel == shape[0])
			{
				check = 1;
				for(int i = 0; shape[i] != '\0';i++)
				{
					if(shape[i] != canvas[r][c + i].pixel)
					{
						check = 0;
					}
				}
				if(check == 1)
				{
					printf("The shape \"%s\" exists at: (%d,%d)\n", shape, c, r);
				}
			}
		}
	}
}

int main()
{
	pixel canvas[8][14];
	fill_canvas(canvas);
	show_canvas(canvas);
	find_shape(canvas, "(-)");
}
