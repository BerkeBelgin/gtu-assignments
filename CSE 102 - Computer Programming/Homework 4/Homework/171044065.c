#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//************************************************************
//	Name:	Berke Belgin 
//	Id:  	171044065
//
//	Info: There are some features you should know before execute:
//		
//		*	Pokémons can move one unit up and one unit 
//		right in one turn which means pokémons are able to 
//		move one block diognal and two blocks straight.
//		*	AI can choose not to do anything in a turn
//		(+%10 chance according to its position).
//		* Only the pokémon player or ai choose during the turn
//		can make an attack. 
//		*	Please try not to enter any different data type
//		from the one wanted from you!
//
//************************************************************
typedef enum
{
	Charmander, Pikachu, Squirtle, Bulbasaur, Pidgeotto, Ratata, Mug, Caterpie, Zubat, Krabby, Null
}
pokemon;

typedef enum
{
	linear, quadratic
}
attack_type;

int StrCmp(char *str1, char *str2)
{
	int val = 1;
	int len1 = 0;
	int len2 = 0;
	
	for(int i = 0; str1[i] != '\0'; i++)
	{
		len1++;
	}
	for(int i = 0; str2[i] != '\0'; i++)
	{
		len2++;
	}
	if(len1 != len2)
	{
		val = 0;
	}
	
	for(int i = 0; i < len1; i++)
	{
		if(str1[i] != str2[i])
		{
			val = 0;
		}
	}
	
	return val;
}

void pokedex(char Pokemon_name[][11], int range[], attack_type type[], int attack_power[], int stamina[])
{
	char input[32];
	
	printf("Please type name of the Pokémon (type exit to close Pokedex):\n\n");
	scanf("%s", input);
	printf("\033[H\033[J");//Clears the console
	
	for(int i = 0; i < 10; i++)
	{
		if(StrCmp(Pokemon_name[i], input))
		{
			printf("Name: %s\n\n", Pokemon_name[i]);
			if(type[i] == 0)
			{
				printf("Attack Type: Linear\n\n");
			}
			else
			{
				printf("Attack Type: Quadratic\n\n");
			}
			printf("Range: %d\n\n", range[i]);
			printf("Attack Power: %d\n\n", attack_power[i]);
			printf("Stamina: %d\n\n", stamina[i]);
			break;
		}
		
		if(i == 9)
		{
			printf("The Pokémon you are looking could not found.\n\n\n");
		}
	}
}


void show_Pokemons(char Pokemon_name[][11], pokemon Pokemons[], int pokemon_count)
{
	for(int i = 0; i < pokemon_count; i++)
	{
		if(Pokemons[i] != 10)
		{
			printf("%d - %s\n", Pokemons[i], Pokemon_name[Pokemons[i]]);
		}
		else
		{
			printf("  - Empty Slot\n");
		}
	}
	printf("\n\n");
}

void catch_a_pokemon(char Pokemon_name[][11], pokemon Pokemons[], pokemon *my_pocket)
{
	int choice = 0;
	
	show_Pokemons(Pokemon_name, Pokemons, 10);
	printf("Id of the pokémon you want to catch: ");
	
	scanf("%d", &choice);
	printf("\033[H\033[J");//Clears the console
	
	int write = -1;//Holds both the first empty space and if the same pokémon exists (-1) in the array or not
	
	for(int i = 0; i < 4; i++)
	{
		if(my_pocket[i] == Null)
		{
			write = i;
			break;
		}
	}
	for(int i = 0; i < 4; i++)
	{		
		if(my_pocket[i] == Pokemons[choice])
		{
			write = -1;
		}
	}
	
	if(write != -1)
	{
		my_pocket[write] = Pokemons[choice];
		printf("The pokémon you choose successfuly added to your pocket.\n\n\n");
	}
	else
	{
		printf("The pokémon you choose could not be added to your pocket.\n\n\n");
	}
}

void release_a_pokemon(char Pokemon_name[][11], pokemon Pokemons[], pokemon *my_pocket)
{
	int choice = 0;
	
	show_Pokemons(Pokemon_name, my_pocket, 4);
	printf("Id of the pokémon you want to release: ");
	
	scanf("%d", &choice);
	printf("\033[H\033[J");//Clears the console
	
	for(int i = 0; i < 4; i++)
	{
		if(my_pocket[i] == choice)
		{
			my_pocket[i] = Null;
			printf("The pokémon you choose successfuly added to your pocket.\n\n\n");
		}
	}
}

void oaks_laboratory(char Pokemon_name[][11], pokemon Pokemons[], pokemon *my_Pokemons)
{	
	int choice = 0;	
	do
	{
		printf("Welcome to Laboratory of Professor Oak. How can I help you?\n\n");
		printf(" 1) Show Pokémons\n");
		printf(" 2) Catch a Pokémon\n");
		printf(" 3) Release a Pokémon\n");
		printf(" 4) Show my pocket\n");
		printf(" 5) Back\n\n");

		scanf("%d", &choice);
		printf("\033[H\033[J");//Clears the console
		
		switch (choice)
		{
			case 1:
				show_Pokemons(Pokemon_name, Pokemons, 10);
				break;
			
			case 2:
				catch_a_pokemon(Pokemon_name, Pokemons, my_Pokemons);
				break;
			
			case 3:
				release_a_pokemon(Pokemon_name, Pokemons, my_Pokemons);
				break;
			
			case 4:
				show_Pokemons(Pokemon_name, my_Pokemons, 4);
				break;
		}
	}
	while(choice != 5);
}

void show_area(char Pokemon_name[][11],int area[8][8],int pokemon_staminas[8][8])
{
	for(int y = 0; y < 8; y++)
	{
		printf(" ");
		for(int x = 0; x < 8; x++) 
		{
			printf("======== ");
		}
		printf("\n");
		
		printf("|");
		for(int x = 0; x < 8; x++) 
		{
			if(area[y][x] != -1)
			{
				printf("   %c%c   |", Pokemon_name[area[y][x]][0], Pokemon_name[area[y][x]][1]);
			}
			else
			{
				printf("        |");
			}
		}
		printf("\n");
		
		printf("|");
		for(int x = 0; x < 8; x++) 
		{
			if(area[y][x] != -1)
			{
				printf(" (%04d) |", pokemon_staminas[y][x]);
			}
			else
			{
				printf("        |");
			}
		}
		printf("\n");
	}
	
	printf(" ");
	for(int x = 0; x < 8; x++) {printf("======== ");}
	printf("\n");
}

void battle(char Pokemon_name[][11], int range[], attack_type type[], int attack_power[], int stamina[], pokemon user_Pokemons[])
{
	int area[8][8] = 
	{
		{-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1}
	};
	int pokemon_staminas[8][8] = 
	{
		{-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1}
	};
	
	pokemon copy_Pockemons[4] = 
	{
		user_Pokemons[0],
		user_Pokemons[1],
		user_Pokemons[2],
		user_Pokemons[3]
	};
	
	int ai_data[4][4] =
	{
		{Null,-1,-1},
		{Null,-1,-1},
		{Null,-1,-1},
		{Null,-1,-1}
	};
	int pl_data[4][3] =
	{
		{user_Pokemons[0],-1,-1},
		{user_Pokemons[1],-1,-1},
		{user_Pokemons[2],-1,-1},
		{user_Pokemons[3],-1,-1}
	};
	
	//create ai_pocket
	int check;
	int value;
	for(int i = 0; i < 4; i++)
	{
		check = 1;
		while(check)
		{
			value = rand() % 10;
			check = 0;
			for(int i = 0; i < 4; i++)
			{			
				if(value == ai_data[i][0])
				{
					check = 1;
				}
			}
			ai_data[i][0] = value;
		}
	}
	
	//place ai pokémons
	int x = 0;
	int y = 0;
	int exit;
	for(int i = 0; i < 4; i++)
	{
		exit = 1;
		while(exit)
		{
			x = rand() % 8;
			y = rand() % 2;
			if(area[y][x] == -1)
			{
				area[y][x] = ai_data[i][0];
				pokemon_staminas[y][x] = stamina[ai_data[i][0]];
				
				ai_data[i][1] = y;
				ai_data[i][2] = x;
				
				exit = 0;
			}
		}
	}
	
	//place user pokémons
	int choice = 0;
	int place = 0;
	if(user_Pokemons[0] == 10 && user_Pokemons[1] == 10 && user_Pokemons[2] == 10 && user_Pokemons[3] == 10)
	{
		printf("Your pocket is empty. Please catch some pokémons and try again.\n\n\n");
		choice = -1;
	}
	
	while(choice != -1 && (user_Pokemons[0] != 10 || user_Pokemons[1] != 10 || user_Pokemons[2] != 10 || user_Pokemons[3] != 10))
	{
		show_area(Pokemon_name, area, pokemon_staminas);
		printf("\n(Enter \"-1\" to exit)\n\n");
		show_Pokemons(Pokemon_name, user_Pokemons, 4);
		printf("Please select a pokémon to place on the board:\n");
		printf("Id of the pokémon: ");
		
		choice = 0;
		scanf("%d", &choice);
		
		printf("\033[H\033[J");//Clears the console
		show_area(Pokemon_name, area, pokemon_staminas);
		
		for(int i = 0; i < 4; i++)
		{
			if(user_Pokemons[i] == choice)
			{
				printf("\n");
				printf("| 0 -  1 -  2 -  3 -  4 -  5 -  6 -  7|\n");
				printf("| 8 -  9 - 10 - 11 - 12 - 13 - 14 - 15|\n");
				printf("\n\nPlease enter a number between 0 and 15 to place your pokémon:\n");
				printf("Id of the box: ");
				
				place = 0;
				scanf("%d", &place);
				
				if(place >= 0 && place <= 15 && area[6 + place / 8][place % 8] == -1)
				{
					area[6 + place / 8][place % 8] = user_Pokemons[i];
					pokemon_staminas[6 + place / 8][place % 8] = stamina[user_Pokemons[i]];
					
					pl_data[i][1] = 6 + place / 8;
					pl_data[i][2] = place % 8;
					
					user_Pokemons[i] = 10;
				}
			}
		}
		printf("\033[H\033[J");//Clears the console
	}
	
	
	int pokemon_choice;
	int move_range;
	char move;
	
	int ai_choice;
	int ai_move;
	
	int battle = -1;
	
	int closest = 8;
	int closest2 = 8;
	
	//************************* Main Battle *************************
	if(choice != -1 && user_Pokemons[0] == 10 && user_Pokemons[1] == 10 && user_Pokemons[2] == 10 && user_Pokemons[3] == 10)
	{
		do
		{		
			//user move
			copy_Pockemons[0] = pl_data[0][0];
			copy_Pockemons[1] = pl_data[1][0];
			copy_Pockemons[2] = pl_data[2][0]; 
			copy_Pockemons[3] = pl_data[3][0];
			
			show_area(Pokemon_name, area, pokemon_staminas);
			printf("\n(Enter \"-1\" to exit)\n\n");
			show_Pokemons(Pokemon_name, copy_Pockemons, 4);
			printf("Please select a pokémon to move:\n");
			printf("Id of the pokémon: ");
			
			pokemon_choice = -1; 
			scanf("%d", &pokemon_choice);
			printf("\033[H\033[J");//Clears the console
			
			move_range = 2;
			move = '\0';
			while(move != 'e' && move_range > 0 && pokemon_choice != -1)
			{
				show_area(Pokemon_name, area, pokemon_staminas);
				printf("\nUse \"w\" \"a\" \"s\" \"d\" keys to move your pokémon or \"e\" to end turn:\n\n");
				printf("Moves left: %d\n", move_range);
				scanf("%c", &move);
				
				for(int i = 0; i < 4; i++)
				{
					if(pokemon_choice == pl_data[i][0])
					{
						pokemon_choice = i;
					}
				}
				
				switch(move)
				{
					case 'w':
						if(area[pl_data[pokemon_choice][1] - 1][pl_data[pokemon_choice][2]] == -1 &&
							pl_data[pokemon_choice][1] > 0 && pl_data[pokemon_choice][1] <= 7 && 
							pl_data[pokemon_choice][2] >= 0 && pl_data[pokemon_choice][2] <= 7)
							{
								area[pl_data[pokemon_choice][1]][pl_data[pokemon_choice][2]] = -1;
								pokemon_staminas[pl_data[pokemon_choice][1] - 1][pl_data[pokemon_choice][2]] = pokemon_staminas[pl_data[pokemon_choice][1]][pl_data[pokemon_choice][2]];
								
								pl_data[pokemon_choice][1]--;
								area[pl_data[pokemon_choice][1]][pl_data[pokemon_choice][2]] = pl_data[pokemon_choice][0];
								pokemon_staminas[pl_data[pokemon_choice][1] + 1][pl_data[pokemon_choice][2]] = -1;
								
								move_range--;
							}
						break;
					case 's':
						if(area[pl_data[pokemon_choice][1] + 1][pl_data[pokemon_choice][2]] == -1 &&
							pl_data[pokemon_choice][1] >= 0 && pl_data[pokemon_choice][1] < 7 && 
							pl_data[pokemon_choice][2] >= 0 && pl_data[pokemon_choice][2] <= 7)
							{
								area[pl_data[pokemon_choice][1]][pl_data[pokemon_choice][2]] = -1;
								pokemon_staminas[pl_data[pokemon_choice][1] + 1][pl_data[pokemon_choice][2]] = pokemon_staminas[pl_data[pokemon_choice][1]][pl_data[pokemon_choice][2]];
								
								pl_data[pokemon_choice][1]++;
								area[pl_data[pokemon_choice][1]][pl_data[pokemon_choice][2]] = pl_data[pokemon_choice][0];
								pokemon_staminas[pl_data[pokemon_choice][1] - 1][pl_data[pokemon_choice][2]] = -1;
								
								move_range--;
							}
						break;
					case 'a':
						if(area[pl_data[pokemon_choice][1]][pl_data[pokemon_choice][2] - 1] == -1 &&
							pl_data[pokemon_choice][1] >= 0 && pl_data[pokemon_choice][1] <= 7 && 
							pl_data[pokemon_choice][2] > 0 && pl_data[pokemon_choice][2] <= 7)
							{
								area[pl_data[pokemon_choice][1]][pl_data[pokemon_choice][2]] = -1;
								pokemon_staminas[pl_data[pokemon_choice][1]][pl_data[pokemon_choice][2] - 1] = pokemon_staminas[pl_data[pokemon_choice][1]][pl_data[pokemon_choice][2]];
								
								pl_data[pokemon_choice][2]--;
								area[pl_data[pokemon_choice][1]][pl_data[pokemon_choice][2]] = pl_data[pokemon_choice][0];
								pokemon_staminas[pl_data[pokemon_choice][1]][pl_data[pokemon_choice][2] + 1] = -1;
								
								move_range--;
							}
						break;
					case 'd':
						if(area[pl_data[pokemon_choice][1]][pl_data[pokemon_choice][2] + 1] == -1 &&
							pl_data[pokemon_choice][1] >= 0 && pl_data[pokemon_choice][1] <= 7 && 
							pl_data[pokemon_choice][2] >= 0 && pl_data[pokemon_choice][2] < 7)
							{
								area[pl_data[pokemon_choice][1]][pl_data[pokemon_choice][2]] = -1;
								pokemon_staminas[pl_data[pokemon_choice][1]][pl_data[pokemon_choice][2] + 1] = pokemon_staminas[pl_data[pokemon_choice][1]][pl_data[pokemon_choice][2]];
								
								pl_data[pokemon_choice][2]++;
								area[pl_data[pokemon_choice][1]][pl_data[pokemon_choice][2]] = pl_data[pokemon_choice][0];
								pokemon_staminas[pl_data[pokemon_choice][1]][pl_data[pokemon_choice][2] - 1] = -1;
								
								move_range--;
							}
						break;
				}
				
				printf("\033[H\033[J");//Clears the console
			}
			
			//user damage
			closest = 8;
			if(type[pl_data[pokemon_choice][0]] == linear)
			{
				for(int i = 1; i <= range[pl_data[pokemon_choice][0]]; i++)
				{
					for(int n = 0; n < 4; n++)
					{
						if(pl_data[pokemon_choice][1] + i == ai_data[n][1] && pl_data[pokemon_choice][2] == ai_data[n][2] && i < closest)
						{
							closest = i;
						}
						if(pl_data[pokemon_choice][1] - i == ai_data[n][1] && pl_data[pokemon_choice][2] == ai_data[n][2] && i < closest)
						{
							closest = i;
						}
						if(pl_data[pokemon_choice][1] == ai_data[n][1] && pl_data[pokemon_choice][2] + i == ai_data[n][2] && i < closest)
						{
							closest = i;
						}
						if(pl_data[pokemon_choice][1] == ai_data[n][1] && pl_data[pokemon_choice][2] - i == ai_data[n][2] && i < closest)
						{
							closest = i;
						}
					}
				}
				
				if(closest < 8)
				{
					for(int n = 0; n < 4; n++)
					{
						if
						(pl_data[pokemon_choice][1] + closest == ai_data[n][1] && pl_data[pokemon_choice][2] == ai_data[n][2] ||
						pl_data[pokemon_choice][1] - closest == ai_data[n][1] && pl_data[pokemon_choice][2] == ai_data[n][2] ||
						pl_data[pokemon_choice][1] == ai_data[n][1] && pl_data[pokemon_choice][2] + closest == ai_data[n][2] ||
						pl_data[pokemon_choice][1] == ai_data[n][1] && pl_data[pokemon_choice][2] - closest == ai_data[n][2])
						{
							pokemon_staminas[ai_data[n][1]][ai_data[n][2]] -= attack_power[pl_data[pokemon_choice][0]];
							
							if(pokemon_staminas[ai_data[n][1]][ai_data[n][2]] <= 0)
							{
								area[ai_data[n][1]][ai_data[n][2]] = -1;
								pokemon_staminas[ai_data[n][1]][ai_data[n][2]] = -1;
								
								ai_data[n][0] = 10;
								ai_data[n][1] = 8;
								ai_data[n][2] = 8;
							}
						}
					}
				}
			}
			else if(type[pl_data[pokemon_choice][0]] == quadratic)
			{
				for(int n = 0; n < 4; n++)
				{
					for(int y = pl_data[pokemon_choice][1] - range[pl_data[pokemon_choice][0]]; y <= pl_data[pokemon_choice][1] + range[pl_data[pokemon_choice][0]]; y++)
					{
						for(int x = pl_data[pokemon_choice][2] - range[pl_data[pokemon_choice][0]]; x <= pl_data[pokemon_choice][2] + range[pl_data[pokemon_choice][0]]; x++)
						{
							if(ai_data[n][1] == y && ai_data[n][2] == x)
							{
								pokemon_staminas[ai_data[n][1]][ai_data[n][2]] -= attack_power[pl_data[pokemon_choice][0]];
								
								if(pokemon_staminas[ai_data[n][1]][ai_data[n][2]] <= 0)
								{
									area[ai_data[n][1]][ai_data[n][2]] = -1;
									pokemon_staminas[ai_data[n][1]][ai_data[n][2]] = -1;
									
									ai_data[n][0] = 10;
									ai_data[n][1] = 8;
									ai_data[n][2] = 8;
								}
							}
						}
					}
				}
			}
			
			//ai move
			ai_choice = rand() % 4;
			
			for(int i = 0; i < 2; i++)
			{
				ai_move = rand() % 10;
				
				switch(ai_move)
				{
					case 0:
						break;
					case 1:
					case 5:
						if(area[ai_data[ai_choice][1] - 1][ai_data[ai_choice][2]] == -1 &&
							ai_data[ai_choice][1] > 0 && ai_data[ai_choice][1] <= 7 && 
							ai_data[ai_choice][2] >= 0 && ai_data[ai_choice][2] <= 7)
							{
								area[ai_data[ai_choice][1]][ai_data[ai_choice][2]] = -1;
								pokemon_staminas[ai_data[ai_choice][1] - 1][ai_data[ai_choice][2]] = pokemon_staminas[ai_data[ai_choice][1]][ai_data[ai_choice][2]];
								
								ai_data[ai_choice][1]--;
								area[ai_data[ai_choice][1]][ai_data[ai_choice][2]] = ai_data[ai_choice][0];
								pokemon_staminas[ai_data[ai_choice][1] + 1][ai_data[ai_choice][2]] = -1;
							}
						break;
					case 2:
					case 6:
					case 9:
							if(area[ai_data[ai_choice][1] + 1][ai_data[ai_choice][2]] == -1 &&
							ai_data[ai_choice][1] >= 0 && ai_data[ai_choice][1] < 7 && 
							ai_data[ai_choice][2] >= 0 && ai_data[ai_choice][2] <= 7)
							{
								area[ai_data[ai_choice][1]][ai_data[ai_choice][2]] = -1;
								pokemon_staminas[ai_data[ai_choice][1] + 1][ai_data[ai_choice][2]] = pokemon_staminas[ai_data[ai_choice][1]][ai_data[ai_choice][2]];
								
								ai_data[ai_choice][1]++;
								area[ai_data[ai_choice][1]][ai_data[ai_choice][2]] = ai_data[ai_choice][0];
								pokemon_staminas[ai_data[ai_choice][1] - 1][ai_data[ai_choice][2]] = -1;
							}
						break;
					case 3:
					case 7:
							if(area[ai_data[ai_choice][1]][ai_data[ai_choice][2] - 1] == -1 &&
							ai_data[ai_choice][1] >= 0 && ai_data[ai_choice][1] <= 7 && 
							ai_data[ai_choice][2] > 0 && ai_data[ai_choice][2] <= 7)
							{
								area[ai_data[ai_choice][1]][ai_data[ai_choice][2]] = -1;
								pokemon_staminas[ai_data[ai_choice][1]][ai_data[ai_choice][2] - 1] = pokemon_staminas[ai_data[ai_choice][1]][ai_data[ai_choice][2]];
								
								ai_data[ai_choice][2]--;
								area[ai_data[ai_choice][1]][ai_data[ai_choice][2]] = ai_data[ai_choice][0];
								pokemon_staminas[ai_data[ai_choice][1]][ai_data[ai_choice][2] + 1] = -1;
							}
						break;
					case 4:
					case 8:
							if(area[ai_data[ai_choice][1]][ai_data[ai_choice][2] + 1] == -1 &&
							ai_data[ai_choice][1] >= 0 && ai_data[ai_choice][1] <= 7 && 
							ai_data[ai_choice][2] >= 0 && ai_data[ai_choice][2] < 7)
							{
								area[ai_data[ai_choice][1]][ai_data[ai_choice][2]] = -1;
								pokemon_staminas[ai_data[ai_choice][1]][ai_data[ai_choice][2]+ 1] = pokemon_staminas[ai_data[ai_choice][1]][ai_data[ai_choice][2]];
								
								ai_data[ai_choice][2]++;
								area[ai_data[ai_choice][1]][ai_data[ai_choice][2]] = ai_data[ai_choice][0];
								pokemon_staminas[ai_data[ai_choice][1]][ai_data[ai_choice][2] - 1] = -1;
							}
						break;
				}
			}
			
			//ai damage
			closest2 = 8;
			
			if(type[ai_data[ai_choice][0]] == linear)
			{
				for(int i = 1; i <= range[ai_data[ai_choice][0]]; i++)
				{
					for(int n = 0; n < 4; n++)
					{
						if(ai_data[ai_choice][1] + i == pl_data[n][1] && ai_data[ai_choice][2] == pl_data[n][2] && i < closest2)
						{
							closest2 = i;
						}
						if(ai_data[ai_choice][1] - i == pl_data[n][1] && ai_data[ai_choice][2] == pl_data[n][2] && i < closest2)
						{
							closest2 = i;
						}
						if(ai_data[ai_choice][1] == pl_data[n][1] && ai_data[ai_choice][2] + i == pl_data[n][2] && i < closest2)
						{
							closest2 = i;
						}
						if(ai_data[ai_choice][1] == pl_data[n][1] && ai_data[ai_choice][2] - i == pl_data[n][2] && i < closest2)
						{
							closest2 = i;
						}
					}
				}
				
				if(closest2 < 8)
				{
					for(int n = 0; n < 4; n++)
					{
						if
						(ai_data[ai_choice][1] + closest2 == pl_data[n][1] && ai_data[ai_choice][2] == pl_data[n][2] ||
						 ai_data[ai_choice][1] - closest2 == pl_data[n][1] && ai_data[ai_choice][2] == pl_data[n][2] ||
						 ai_data[ai_choice][1] == pl_data[n][1] && ai_data[ai_choice][2] + closest2 == pl_data[n][2] ||
						 ai_data[ai_choice][1] == pl_data[n][1] && ai_data[ai_choice][2] - closest2 == pl_data[n][2])
						{
							pokemon_staminas[pl_data[n][1]][pl_data[n][2]] -= attack_power[ai_data[ai_choice][0]];
							
							if(pokemon_staminas[pl_data[n][1]][pl_data[n][2]] <= 0)
							{
								area[pl_data[n][1]][pl_data[n][2]] = -1;
								pokemon_staminas[pl_data[n][1]][pl_data[n][2]] = -1;
								
								pl_data[n][0] = 10;
								pl_data[n][1] = -1;
								pl_data[n][2] = -1;
							}
						}
					}
				}
			}
			else if(type[ai_data[ai_choice][0]] == quadratic)
			{
				for(int n = 0; n < 4; n++)
				{
					for(int y = ai_data[ai_choice][1] - range[ai_data[ai_choice][0]]; y <= ai_data[ai_choice][1] + range[ai_data[ai_choice][0]]; y++)
					{
						for(int x = ai_data[ai_choice][2] - range[ai_data[ai_choice][0]]; x <= ai_data[ai_choice][2] + range[ai_data[ai_choice][0]]; x++)
						{
							if(pl_data[n][1] == y && pl_data[n][2] == x)
							{
								pokemon_staminas[pl_data[n][1]][pl_data[n][2]] -= attack_power[ai_data[ai_choice][0]];
								
								if(pokemon_staminas[pl_data[n][1]][pl_data[n][2]] <= 0)
								{
									area[pl_data[n][1]][pl_data[n][2]] = -1;
									pokemon_staminas[pl_data[n][1]][pl_data[n][2]] = -1;
									
									pl_data[n][0] = 10;
									pl_data[n][1] = -1;
									pl_data[n][2] = -1;
								}
							}
						}
					}
				}
			}
			
			battle = 0;
			for(int i = 0; i < 4; i++)
			{
				if(pl_data[i][0] >= 0 && pl_data[i][0] < 10)
				{
					battle = -1;
				}
			}
			
			if(battle == -1)
			{
				battle = 1;
				for(int i = 0; i < 4; i++)
				{
					if(ai_data[i][0] >= 0 && ai_data[i][0] < 10)
					{
						battle = -1;
					}
				}
			}
		}
		while((battle != 0 && battle != 1) && pokemon_choice != -1);
		
		//ending message
		if(battle == 1)
		{
			printf("\033[H\033[J");//Clears the console
			printf("You win!\n\n");
		}
		else if(battle == 0)
		{
			
			printf("\033[H\033[J");//Clears the console
			printf("You have been defeated.\n\n");
		}
	}
	//************************* Main Battle *************************
}


void main_menu()
{
	pokemon my_Pokemons[4] = {Null, Null, Null, Null};
	
	pokemon Pokemons[10] = {Charmander, Pikachu, Squirtle, Bulbasaur, Pidgeotto, Ratata, Mug, Caterpie, Zubat, Krabby};
	char Pokemon_name[10][11] = {"Charmander", "Pikachu", "Squirtle", "Bulbasaur", "Pidgeotto", "Ratata", "Mug", "Caterpie", "Zubat", "Krabby"};
	int range[10] = {1, 3, 4, 3, 2, 2, 1, 2, 3, 2};
	attack_type type[10] = {quadratic, linear, linear, linear, quadratic, linear, quadratic, quadratic, linear, linear};
	int attack_power[10] = {500, 350, 300, 400, 250, 250, 350, 200, 350, 300};
	int stamina[10] = {2200, 1500, 1700, 2500, 1900, 2500, 3000, 1200, 1250, 2600};
	
	
	int choice = 0;
	
	do
	{
		printf("Please select an option to continue:\n\n");
		printf(" 1) Open Pokedex\n");
		printf(" 2) Go to Oak’s Laboratory\n");
		printf(" 3) Enter the tournament\n");
		printf(" 4) Exit\n\n");	
		
		scanf("%d", &choice);
		printf("\033[H\033[J");//Clears the console
		
		switch (choice)
		{
			case 1:
				pokedex(Pokemon_name, range, type, attack_power, stamina);
				break;
			
			case 2:
				oaks_laboratory(Pokemon_name, Pokemons, my_Pokemons);
				break;
			
			case 3:
				battle(Pokemon_name, range, type, attack_power, stamina, my_Pokemons);
				break;
		}
	}
	while(choice != 4);
}

int main()
{
	srand(time(NULL));
	printf("\033[H\033[J");//Clears the console
	main_menu();
}
