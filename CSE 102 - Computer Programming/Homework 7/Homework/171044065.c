#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum
{
	noone, cap, car
}player_type;

typedef enum
{
	start, property, tax, punish
}block_type;

struct player
{
	player_type type;
	int current_block_id;
	int owned_block_ids[12];
	int account;
	int turn_to_wait;
	char *name;
};

struct block
{
	int block_id;
	char *name;
	int price;
	int rent;
	int rent_1;
	int rent_2;
	int rent_3;
	int house_price;
	int house_count;
	struct player owner;
	block_type type;
};

void init_the_board(struct block board[20])
{
	//I define the values to assign
	int block_id[20] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
	char *name[20] = {"Start", "Esenyurt", "Car Park", "Tuzla", "Arnavutkoy", "Wait 2 Turns", "Catalca", "Beykoz", "Car Fix", "Maltepe", "Bills", "Sisli", "Oil", "Atasehir", "Sariyer", "Wait 1 Turn", "Kadikoy", "Besiktas", "Vocation", "Bebek"};
	int price[20] = {0, 16000, 0, 16500, 17000, 0, 20000, 23000, 0, 30000, 0, 33000, 0, 35000, 40000, 0, 43000, 60000, 0, 70000};
	int rent[20] = {0, 800, 1500, 850, 875, 2, 1000, 1100, 1750, 1350, 2000, 1500, 2250, 1600, 1750, 1, 1900, 2500, 5000, 3500};
	int rent_1[20] = {0, 4000, 0, 4250, 4500, 0, 5000, 5500, 0, 7000, 0, 8000, 0, 8500, 9500, 0, 11000, 15000, 0, 20000};
	int rent_2[20] = {0, 9000, 0, 9500, 10000, 0, 12000, 12500, 0, 15000, 0, 16000, 0, 17000, 19000, 0, 21500, 28000, 0, 35500};
	int rent_3[20] = {0, 25000, 0, 26000, 28000, 0, 30000, 33000, 0, 40000, 0, 42000, 0, 45000, 48000, 0, 55000, 60000, 0, 65000};
	int house_price[20] = {0, 10000, 0, 12000, 12000, 0, 13000, 13000, 0, 15000, 0, 16000, 0, 17000, 19000, 0, 23000, 30000, 0, 35000};
	int house_count[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	block_type type[20] = {start, property, tax, property, property, punish, property, property, tax, property, tax, property, tax, property, property, punish, property, property, tax, property};
	
	//Assign the values here
	for(int i = 0; i < 20; i++)
	{
		board[i].block_id = block_id[i];
		board[i].name = name[i];
		board[i].price = price[i];
		board[i].rent = rent[i];
		board[i].rent_1 = rent_1[i];
		board[i].rent_2 = rent_2[i];
		board[i].rent_3 = rent_3[i];
		board[i].house_price = house_price[i];
		board[i].house_count = house_count[i];
		board[i].owner.type = noone;
		board[i].type = type[i];
	}
}

void show_board(struct block board[20],struct player player_one, struct player player_two)
{
	char *types[3] = {" ", "Cap", "Car"};
	int order[20] = {0, 1, 2, 3, 4, 5, 19, 6, 18, 7, 17, 8, 16, 9, 15, 14, 13, 12, 11, 10};
	
	//Variables to store index of every line in the boxes
	int line_1 = 0;
	int line_2 = 0;
	int line_3 = 0;
	
	printf("\033[H\033[J");
	
	for(int y = 0; y < (6 * 4) + 1; y++)
	{
		for(int x = 0; x < (6 * 24) + 1; x++)
		{
			if(y % 4 == 0)
			{
				if((x <= 1 * 24 || x >= 5 * 24) || (y <= 1 * 4 || y >= 5 * 4))
				{
					printf("-");
				}
				else
				{
					printf(" ");
				}
			}
			else
			{
				if(x % 24 == 0 && ((x <= 1 * 24 || x >= 5 * 24) || (y <= 1 * 4 || y >= 5 * 4)))
				{
					printf("|");
				}
				else
				{
					if((x <= 1 * 24 || x >= 5 * 24) || (y <= 1 * 4 || y >= 5 * 4))
					{
						if(x % 24 < 8)
						{
							printf(" ");
						}
						else if(x % 24 == 8)
						{
							if(y % 4 == 1)
							{
								printf("%-16s", board[order[line_1]].name);
								line_1++;
							}
							else if(y % 4 == 2)
							{
								if(board[order[line_2]].type == property)printf("$%-15d", board[order[line_2]].price);
								else if(board[order[line_2]].type == tax)printf("$%-15d", board[order[line_2]].rent);
								else for(int i = 0; i < 16; i++)printf(" ");
								line_2++;
							}
							else if(y % 4 == 3)
							{
								if(player_one.current_block_id == order[line_3] && player_two.current_block_id == order[line_3])printf("%-4s%-12s", types[player_one.type], types[player_two.type]);
								else if(player_one.current_block_id == order[line_3])printf("%-16s", types[player_one.type]);
								else if(player_two.current_block_id == order[line_3])printf("%-16s", types[player_two.type]);
								else for(int i = 0; i < 16; i++)printf(" ");
								line_3++;
							}
						}
					}
					else
					{
						printf(" ");
					}
				}
			}
		}
		printf("\n");
	}
	printf("\n");
}

void show_properties(struct block board[20])
{
	int n;
	
	printf("\033[H\033[J");
	do
	{
		printf("Please select a property to see details:\n");
		for(int i = 0; i < 20; i++)if(board[i].type == property)printf("%-2d -    %s\n", board[i].block_id, board[i].name);
		printf("0  -    Exit\n");
		scanf("%d", &n);
		
		printf("\033[H\033[J");
		if(board[n].type == property)
		{
			for(int i = 0; i < 33; i++)printf("-");
			printf("\n");
			
			printf("|           %-20s|\n", board[n].name);
			
			for(int i = 0; i < 33; i++)printf("-");
			printf("\n");
			
			printf("|       %-16s$%-7d|\n", "Rent", board[n].rent);
			printf("|       %-16s$%-7d|\n", "Rent 1 H", board[n].rent_1);
			printf("|       %-16s$%-7d|\n", "Rent 2 H", board[n].rent_2);
			printf("|       %-16s$%-7d|\n", "Rent 3 H", board[n].rent_3);
			
			for(int i = 0; i < 33; i++)printf("-");
			printf("\n");
			
			printf("|       %-16s$%-7d|\n", "House Price", board[n].house_price);
			
			for(int i = 0; i < 33; i++)printf("-");
			printf("\n\n");
		}
	}
	while(n != 0);
}

//The function to roll the dice
int roll_the_dice(struct player current_player)
{
	return (current_player.current_block_id + (rand() % 6) + 1) % 20;
}

void show_my_account(struct player current_player)
{
	int n;
	
	do
	{
		printf("\033[H\033[J");
		for(int i = 0; i < 33; i++)printf("-");
		printf("\n|%8s $%-21d|\n", "Account:", current_player.account);
		for(int i = 0; i < 33; i++)printf("-");
		printf("\n\nPress 0 to exit...\n");
		scanf("%d", &n);
	}
	while(n != 0);
}

void show_my_properties(struct player current_player, struct block board[20])
{
	int n;
	
	do
	{
		printf("\033[H\033[J");
		printf("The properties you have:\n");
		for(int i = 0; i < 12; i++)
		{
			if(current_player.owned_block_ids[i] != -1)
			{
				printf("%-2d -    %s (Houses: %d)\n", current_player.owned_block_ids[i], board[current_player.owned_block_ids[i]].name, board[current_player.owned_block_ids[i]].house_count);
			}
		}
		printf("\nPress 0 to exit...\n");
		scanf("%d", &n);
	}
	while(n != 0);
}

void buy_property(struct block *current_block, struct player *current_player)
{
	int n;
	
	do
	{
		printf("\033[H\033[J");
		if((*current_block).type == property && (*current_block).owner.type == noone && (*current_player).account >= (*current_block).price)
		{
			for(int i = 0; i < 12; i++)
			{
				if((*current_player).owned_block_ids[i] == -1)
				{
					(*current_block).owner.type = (*current_player).type;
					(*current_player).owned_block_ids[i] = (*current_block).block_id;
					(*current_player).account -= (*current_block).price;
					printf("You have bought %s for $%d succesfuly.\n", (*current_block).name, (*current_block).price);
					break;
				}
			}
		}
		else
		{
			printf("You can't buy this property.\n");
		}
		printf("\nPress 0 to exit...\n");
		scanf("%d", &n);
	}
	while(n != 0);
}

void buy_house(struct block *current_block, struct player *current_player)
{
	int n;
	
	printf("\033[H\033[J");
	do
	{
		printf("Press the amount of houses if you want to buy or 0 to exit...\n");
		scanf("%d", &n);
		printf("\033[H\033[J");
		if((*current_block).type == property && (*current_block).owner.type == (*current_player).type && (*current_player).account >= (*current_block).house_price * n && n >= 1 && n <= 3 && (*current_block).house_count + n <= 3)
		{
			printf("You have bought %d house/houses for $%d succesfuly.\n", n, (*current_block).house_price * n);
			(*current_player).account -= (*current_block).house_price * n;
			(*current_block).house_count += n;
		}
		else
		{
			printf("You can't buy that amount of house for this property.\n");
		}
	}
	while(n != 0);
}

void sell_property(struct player* current_player, struct block board[20])
{
	int n = 0;
	
	do
	{
		printf("\033[H\033[J");
		for(int i = 0; i < 12; i++)
		{
			if((*current_player).owned_block_ids[i] == n)
			{
				board[n].owner.type = noone;
				(*current_player).owned_block_ids[i] = -1;
				(*current_player).account += (board[n].price / 2) + (board[n].house_count * board[n].house_price / 2);
				printf("You have sold %s for $%d succesfuly.\n", board[n].name, (board[n].price / 2) + (board[n].house_count * board[n].house_price / 2));
				board[n].house_count = 0;
				break;
			}
		}
		printf("The properties you have:\n");
		for(int i = 0; i < 12; i++)
		{
			if((*current_player).owned_block_ids[i] != -1)
			{
				printf("%-2d -    %s (Houses: %d)\n", (*current_player).owned_block_ids[i], board[(*current_player).owned_block_ids[i]].name, board[(*current_player).owned_block_ids[i]].house_count);
			}
		}
		printf("\nPress the id of the property to sell or 0 to exit...\n");
		scanf("%d", &n);
		
	}
	while(n != 0);
}

void gameplay(struct block board[20], struct player player_one, struct player player_two)
{
	struct player *players[2] = {&player_one, &player_two};
	int t_turn = 0;
	int p_turn = 0;
	
	int move_to;
	
	int choice;
	
	int n;
	int total;
	
	init_the_board(board);
	do
	{
		t_turn++;
		p_turn %= 2;
		
		total = 0;
		for(int i = 0; i < 12; i++)
		{
			if((*players[p_turn]).owned_block_ids[i] != -1)
			{
				total += (board[(*players[p_turn]).owned_block_ids[i]].price / 2) + (board[(*players[p_turn]).owned_block_ids[i]].house_price * board[(*players[p_turn]).owned_block_ids[i]].house_count / 2);
			}
		}
		if((*players[p_turn]).account + total < 0)
		{
			printf("%s has won the game!\n", (*players[(p_turn + 1) % 2]).name);
			choice = 0;
			break;
		}
		
		for(int i = 0; i < 12; i++)
		{
			if((*players[(p_turn + 1) % 2]).owned_block_ids[i] != -1)
			{
				total += (board[(*players[(p_turn + 1) % 2]).owned_block_ids[i]].price / 2) + (board[(*players[(p_turn + 1) % 2]).owned_block_ids[i]].house_price * board[(*players[(p_turn + 1) % 2]).owned_block_ids[i]].house_count / 2);
			}
		}
		if((*players[(p_turn + 1) % 2]).account + total < 0)
		{
			printf("%s has won the game!\n", (*players[p_turn]).name);
			choice = 0;
			break;
		}
		
		do
		{
			if((*players[p_turn]).turn_to_wait > 0)
			{
				(*players[p_turn]).turn_to_wait--;
				p_turn++;
				break;
			}
			
			show_board(board, player_one, player_two);
			printf("%s (Turn %d)\n\n", (*players[p_turn]).name, t_turn);
			printf("1 - Roll the dice\n");
			printf("2 - Show my account\n");
			printf("3 - Show my properties\n");
			printf("4 - Show property deeds\n");
			printf("5 - Buy property\n");
			printf("6 - Buy house\n");
			printf("7 - Sell property\n");
			printf("0 - Exit Game\n\n");
			printf("Please select an option to continue: ");
			scanf("%d", &choice);
			
			switch(choice)
			{
				case 1:
					move_to = roll_the_dice(*players[p_turn]);
					if(move_to < (*players[p_turn]).current_block_id)(*players[p_turn]).account += 10000;
					(*players[p_turn]).current_block_id = move_to;
					
					printf("\033[H\033[J");
					show_board(board, player_one, player_two);
					
					if(board[(*players[p_turn]).current_block_id].type == property)
					{
						if(board[(*players[p_turn]).current_block_id].owner.type == noone)
						{
							n = 0;
							
							printf("Do you want to buy %s for %d? (yes: 1/no: 0)\n", board[(*players[p_turn]).current_block_id].name, board[(*players[p_turn]).current_block_id].price);
							do
							{
								scanf("%d", &n);
								if(n == 1)
								{
									buy_property(&board[(*players[p_turn]).current_block_id], players[p_turn]);//Ask to buy property
								}
							}
							while(n != 1 && n != 0);
						}
						if(board[(*players[p_turn]).current_block_id].owner.type == (*players[p_turn]).type)
						{
							buy_house(&board[(*players[p_turn]).current_block_id], players[p_turn]);//Ask to buy house
						}
						if(board[(*players[p_turn]).current_block_id].owner.type == (*players[(p_turn + 1) % 2]).type)
						{
							if(board[(*players[p_turn]).current_block_id].house_count == 0)
							{
								(*players[p_turn]).account -= board[(*players[p_turn]).current_block_id].rent;
								(*players[(p_turn + 1) % 2]).account += board[(*players[p_turn]).current_block_id].rent;
							}
							else if(board[(*players[p_turn]).current_block_id].house_count == 1)
							{
								(*players[p_turn]).account -= board[(*players[p_turn]).current_block_id].rent_1;
								(*players[(p_turn + 1) % 2]).account += board[(*players[p_turn]).current_block_id].rent_1;
							}
							else if(board[(*players[p_turn]).current_block_id].house_count == 2)
							{
								(*players[p_turn]).account -= board[(*players[p_turn]).current_block_id].rent_2;
								(*players[(p_turn + 1) % 2]).account += board[(*players[p_turn]).current_block_id].rent_2;
							}
							else if(board[(*players[p_turn]).current_block_id].house_count == 3)
							{
								(*players[p_turn]).account -= board[(*players[p_turn]).current_block_id].rent_3;
								(*players[(p_turn + 1) % 2]).account += board[(*players[p_turn]).current_block_id].rent_3;
							}
							
							if((*players[p_turn]).account < 0)
							{
								//Ask to sell property
								
								printf("You are in debt, you should sell a property.\n");
								do
								{
									sell_property(players[p_turn], board);
									total = 0;
									for(int i = 0; i < 12; i++)
									{
										if((*players[p_turn]).owned_block_ids[i] != -1)
										{
											total += (board[(*players[p_turn]).owned_block_ids[i]].price / 2) + (board[(*players[p_turn]).owned_block_ids[i]].house_price * board[(*players[p_turn]).owned_block_ids[i]].house_count / 2);
										}
									}
								}
								while((*players[p_turn]).account < 0 && (*players[p_turn]).account + total > 0);
							}
						}
					}
					else if(board[(*players[p_turn]).current_block_id].type == tax)
					{
						(*players[p_turn]).account -= board[(*players[p_turn]).current_block_id].rent;
						
						if((*players[p_turn]).account < 0)
						{
							//Ask to sell property
							n = 0;
							
							printf("Do you want to sell any property? (yes: 1/no: 0)\n");
							do
							{
								scanf("%d", &n);
								if(n == 1)
								{
									sell_property(players[p_turn], board);
								}
							}
							while(n != 1 && n != 0);
						}
					}
					else if(board[(*players[p_turn]).current_block_id].type == punish)
					{
						(*players[p_turn]).turn_to_wait += board[(*players[p_turn]).current_block_id].rent;
					}
					
					p_turn++;
					break;
				case 2:
					show_my_account(*players[p_turn]);
					break;
				case 3:
					show_my_properties(*players[p_turn], board);
					break;
				case 4:
					show_properties(board);
					break;
				case 5:
					buy_property(&board[(*players[p_turn]).current_block_id], players[p_turn]);
					break;
				case 6:
					buy_house(&board[(*players[p_turn]).current_block_id], players[p_turn]);
					break;
				case 7:
					sell_property(players[p_turn], board);
					break;
			}
		}
		while(choice != 0 && p_turn != 2);
	}
	while(choice != 0);
}

int main()
{
	srand(time(NULL));
	
	struct block board[20];
	struct player player_one;
	struct player player_two;
	
	player_one.type = cap;
	player_one.current_block_id = 0;
	for(int i = 0; i < 12; i++)player_one.owned_block_ids[i] = -1;
	player_one.account = 100000;
	player_one.turn_to_wait = 0;
	player_one.name = "Player 1";
	
	player_two.type = car;
	player_two.current_block_id = 0;
	for(int i = 0; i < 12; i++)player_two.owned_block_ids[i] = -1;
	player_two.account = 100000;
	player_two.turn_to_wait = 0;
	player_two.name = "Player 2";
	
	gameplay(board, player_one, player_two);
	return 0;
}










