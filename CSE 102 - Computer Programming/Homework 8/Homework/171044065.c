#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum
{
	noone, cap, car
}player_type;

typedef enum
{
	start, property, tax, punish, fortune
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
	struct block *next;
};

struct fortune_card
{
	int card_id;
	char *name;
};

void init_the_board(struct block *list)
{
	//I define the values to assign
	int block_id[24] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23};
	char *name[24] = {"Start", "Esenyurt", "Car Park", "Fortune Card", "Tuzla", "Arnavutkoy", "Wait 2 Turns", "Catalca", "Beykoz", "Fortune Card", "Car Fix", "Maltepe", "Bills", "Sisli", "Oil", "Fortune Card", "Atasehir", "Sariyer", "Wait 1 Turn", "Kadikoy", "Besiktas", "Fortune Card", "Vocation", "Bebek"};
	int price[24] = {0, 16000, 0, 0, 16500, 17000, 0, 20000, 23000, 0, 0, 30000, 0, 33000, 0, 0, 35000, 40000, 0, 43000, 60000, 0, 0, 70000};
	int rent[24] = {0, 800, 1500, 0, 850, 875, 2, 1000, 1100, 0, 1750, 1350, 2000, 1500, 2250, 0, 1600, 1750, 1, 1900, 2500, 0, 5000, 3500};
	int rent_1[24] = {0, 4000, 0, 0, 4250, 4500, 0, 5000, 5500, 0, 0, 7000, 0, 8000, 0, 0, 8500, 9500, 0, 11000, 15000, 0, 0, 20000};
	int rent_2[24] = {0, 9000, 0, 0, 9500, 10000, 0, 12000, 12500, 0, 0, 15000, 0, 16000, 0, 0, 17000, 19000, 0, 21500, 28000, 0, 0, 35500};
	int rent_3[24] = {0, 25000, 0, 0, 26000, 28000, 0, 30000, 33000, 0, 0, 40000, 0, 42000, 0, 0, 45000, 48000, 0, 55000, 60000, 0, 0, 65000};
	int house_price[24] = {0, 10000, 0, 0, 12000, 12000, 0, 13000, 13000, 0, 0, 15000, 0, 16000, 0, 0, 17000, 19000, 0, 23000, 30000, 0, 0, 35000};
	int house_count[24] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	block_type type[24] = {start, property, tax, fortune, property, property, punish, property, property, fortune, tax, property, tax, property, tax, fortune, property, property, punish, property, property, fortune, tax, property};
	
	struct block *element = list;
	
	//Assign the values here
	for(int i = 0; i < 24; i++)
	{
		(*element).block_id = block_id[i];
		(*element).name = name[i];
		(*element).price = price[i];
		(*element).rent = rent[i];
		(*element).rent_1 = rent_1[i];
		(*element).rent_2 = rent_2[i];
		(*element).rent_3 = rent_3[i];
		(*element).house_price = house_price[i];
		(*element).house_count = house_count[i];
		(*element).owner.type = noone;
		(*element).type = type[i];
		
		if(i < 23)
		{
			(*element).next = (struct block *)malloc(sizeof(struct block));
			element = (*element).next;
		}
		else
		{
			(*element).next = NULL;
		}
	}
}

void init_fortune_cards(struct fortune_card cards[5])
{
	int card_id[5] = {0, 1, 2, 3, 4};
	char *name[5] = {"Free House", "Time Travel", "Garnishment", "Generosity", "Treasure Hunter"};
	
	for(int i = 0; i < 5; i++)
	{
		cards[i].card_id = card_id[i];
		cards[i].name = name[i];
	}
}

struct block *find_element_by_id(struct block *list, int n)
{
	struct block *element = list;
	
	while(element != NULL)
	{
		if((*element).block_id == n)
		{
			break;
		}
		element = (*element).next;
	}
	
	return element;
}

void show_board(struct block *list,struct player human, struct player computer)
{
	char *types[3] = {" ", "Cap", "Car"};
	int order[24] = {0, 1, 2, 3, 4, 5, 6, 23, 7, 22, 8, 21, 9, 20, 10, 19, 11, 18, 17, 16, 15, 14, 13, 12};
	
	//Variables to store index of every line in the boxes
	int line_1 = 0;
	int line_2 = 0;
	int line_3 = 0;
	
	printf("\033[H\033[J");//Clear Screen
	
	for(int y = 0; y < (7 * 4) + 1; y++)
	{
		for(int x = 0; x < (7 * 24) + 1; x++)
		{
			if(y % 4 == 0)
			{
				if((x <= 1 * 24 || x >= 6 * 24) || (y <= 1 * 4 || y >= 6 * 4))
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
				if(x % 24 == 0 && ((x <= 1 * 24 || x >= 6 * 24) || (y <= 1 * 4 || y >= 6 * 4)))
				{
					printf("|");
				}
				else
				{
					if((x <= 1 * 24 || x >= 6 * 24) || (y <= 1 * 4 || y >= 6 * 4))
					{
						if(x % 24 < 8)
						{
							printf(" ");
						}
						else if(x % 24 == 8)
						{
							if(y % 4 == 1)
							{
								printf("%-16s", (*find_element_by_id(list, order[line_1])).name);
								line_1++;
							}
							else if(y % 4 == 2)
							{
								if((*find_element_by_id(list, order[line_2])).type == property)printf("$%-15d", (*find_element_by_id(list, order[line_2])).price);
								else if((*find_element_by_id(list, order[line_2])).type == tax)printf("$%-15d", (*find_element_by_id(list, order[line_2])).rent);
								else for(int i = 0; i < 16; i++)printf(" ");
								line_2++;
							}
							else if(y % 4 == 3)
							{
								if(human.current_block_id == order[line_3] && computer.current_block_id == order[line_3])printf("%-4s%-12s", types[human.type], types[computer.type]);
								else if(human.current_block_id == order[line_3])printf("%-16s", types[human.type]);
								else if(computer.current_block_id == order[line_3])printf("%-16s", types[computer.type]);
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

//The function to roll the dice
int roll_the_dice(struct player current_player)
{
	return (current_player.current_block_id + (rand() % 6) + 1) % 24;
}

void show_properties(struct block *list)
{
	int n;
	
	printf("\033[H\033[J");//Clear Screen
	do
	{
		printf("Please select a property to see details:\n");
		for(int i = 0; i < 24; i++)if((*find_element_by_id(list, i)).type == property)printf("%-2d -    %s\n", (*find_element_by_id(list, i)).block_id, (*find_element_by_id(list, i)).name);
		printf("0  -    Exit\n");
		scanf("%d", &n);
		
		printf("\033[H\033[J");//Clear Screen
		if((*find_element_by_id(list, n)).type == property)
		{
			for(int i = 0; i < 33; i++)printf("-");
			printf("\n");
			
			printf("|           %-20s|\n", (*find_element_by_id(list, n)).name);
			
			for(int i = 0; i < 33; i++)printf("-");
			printf("\n");
			
			printf("|       %-16s$%-7d|\n", "Rent", (*find_element_by_id(list, n)).rent);
			printf("|       %-16s$%-7d|\n", "Rent 1 H", (*find_element_by_id(list, n)).rent_1);
			printf("|       %-16s$%-7d|\n", "Rent 2 H", (*find_element_by_id(list, n)).rent_2);
			printf("|       %-16s$%-7d|\n", "Rent 3 H", (*find_element_by_id(list, n)).rent_3);
			
			for(int i = 0; i < 33; i++)printf("-");
			printf("\n");
			
			printf("|       %-16s$%-7d|\n", "House Price", (*find_element_by_id(list, n)).house_price);
			
			for(int i = 0; i < 33; i++)printf("-");
			printf("\n\n");
		}
	}
	while(n != 0);
}

void show_my_account(struct player current_player)
{
	int n;
	
	do
	{
		printf("\033[H\033[J");//Clear Screen
		for(int i = 0; i < 33; i++)printf("-");
		printf("\n|%8s $%-21d|\n", "Account:", current_player.account);
		for(int i = 0; i < 33; i++)printf("-");
		printf("\n\nPress 0 to exit...\n");
		scanf("%d", &n);
	}
	while(n != 0);
}

void show_my_properties(struct player current_player, struct block *list)
{
	int n;
	
	do
	{
		printf("\033[H\033[J");//Clear Screen
		printf("The properties you have:\n");
		for(int i = 0; i < 12; i++)
		{
			if(current_player.owned_block_ids[i] != -1)
			{
				printf("%-2d -    %s (Houses: %d)\n", current_player.owned_block_ids[i], (*find_element_by_id(list, current_player.owned_block_ids[i])).name, (*find_element_by_id(list, current_player.owned_block_ids[i])).house_count);
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
		printf("\033[H\033[J");//Clear Screen
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
	
	printf("\033[H\033[J");//Clear Screen
	do
	{
		printf("Press the amount of houses if you want to buy or 0 to exit...\n");
		scanf("%d", &n);
		
		printf("\033[H\033[J");//Clear Screen
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

void sell_property(struct player *current_player, struct block *list)
{
	int n;
	
	printf("\033[H\033[J");//Clear Screen
	do
	{
		printf("The properties you have:\n");
		for(int i = 0; i < 12; i++)
		{
			if((*current_player).owned_block_ids[i] != -1)
			{
				printf("%-2d -    %s (Houses: %d)\n", (*current_player).owned_block_ids[i], (*find_element_by_id(list, (*current_player).owned_block_ids[i])).name, (*find_element_by_id(list, (*current_player).owned_block_ids[i])).house_count);
			}
		}
		printf("\nPress the id of the property to sell or 0 to exit...\n");
		scanf("%d", &n);
		if(n == -1)n = 0;
		
		printf("\033[H\033[J");//Clear Screen
		for(int i = 0; i < 12; i++)
		{
			if((*current_player).owned_block_ids[i] == n)
			{
				(*find_element_by_id(list, n)).owner.type = noone;
				(*current_player).owned_block_ids[i] = -1;
				(*current_player).account += ((*find_element_by_id(list, n)).price / 2) + ((*find_element_by_id(list, n)).house_count * (*find_element_by_id(list, n)).house_price / 2);
				printf("You have sold %s for $%d succesfuly.\n", (*find_element_by_id(list, n)).name, ((*find_element_by_id(list, n)).price / 2) + ((*find_element_by_id(list, n)).house_count * (*find_element_by_id(list, n)).house_price / 2));
				(*find_element_by_id(list, n)).house_count = 0;
				break;
			}
		}
	}
	while(n != 0);
}

void manage(struct block *list, struct fortune_card cards[5], struct player *human, struct player *computer)
{
	int n;
	int total;
	int card;
	int d;
	
	show_board(list, *human, *computer);
	
	if((*find_element_by_id(list, (*human).current_block_id)).type == fortune)
	{
		//Fortune Card
		card = rand() % 5;
		
		printf("You have picked the \"%s\" card\nPress any number to continue...\n", cards[card].name);
		scanf("%d", &d);
		
		if(card == 0)
		{
			int valid = 0;
			
			for(int i = 0; i < 12; i++)
			{
				if((*human).owned_block_ids[i] != -1 && (*find_element_by_id(list, (*human).owned_block_ids[i])).house_count < 3)
				{
					valid = 1;
				}
			}
			while(valid)
			{
				for(int i = 0; i < 12; i++)
				{
					if((*human).owned_block_ids[i] != -1 && (*find_element_by_id(list, (*human).owned_block_ids[i])).house_count < 3)
					{
						printf("%-2d -    %s (Houses: %d)\n", (*human).owned_block_ids[i], (*find_element_by_id(list, (*human).owned_block_ids[i])).name, (*find_element_by_id(list, (*human).owned_block_ids[i])).house_count);
					}
				}
				printf("Choose one of the properties above, to build a house: ");
				scanf("%d", &n);
				for(int i = 0; i < 12; i++)
				{
					if((*human).owned_block_ids[i] == n && (*find_element_by_id(list, (*human).owned_block_ids[i])).house_count < 3)
					{
						(*find_element_by_id(list, (*human).owned_block_ids[i])).house_count += 1;
						valid = 0;
					}
				}
			}
		}
		else if(card == 1)
		{
			if((rand() % 6) + 1 <= 3)
			{
				(*human).current_block_id += 2;
			}
			else
			{
				(*human).current_block_id -= 2;
			}
		}
		else if(card == 2)
		{
			(*human).account -= 5000;
		}
		else if(card == 3)
		{
			(*human).account -= 10000;
			(*computer).account += 10000;
		}
		else if(card == 4)
		{
			(*human).account += 20000;
		}
	}
	
	if((*find_element_by_id(list, (*human).current_block_id)).type == property)
	{
		if((*find_element_by_id(list, (*human).current_block_id)).owner.type == noone)
		{
			//Ask to buy property
			do
			{
				show_board(list, *human, *computer);
				printf("Do you want to buy %s for %d? (yes: 1/no: 0)\n", (*find_element_by_id(list, (*human).current_block_id)).name, (*find_element_by_id(list, (*human).current_block_id)).price);
				scanf("%d", &n);
				
				if(n == 1)
				{
					buy_property(find_element_by_id(list, (*human).current_block_id), human);
				}
			}
			while(n != 1 && n != 0);
		}
		
		if((*find_element_by_id(list, (*human).current_block_id)).owner.type == (*human).type)
		{
			//Ask to buy house
			show_board(list, *human, *computer);
			buy_house(find_element_by_id(list, (*human).current_block_id), human);
		}
		
		if((*find_element_by_id(list, (*human).current_block_id)).owner.type == (*computer).type)
		{
			//Pay the rent
			if((*find_element_by_id(list, (*human).current_block_id)).house_count == 0)
			{
				(*human).account -= (*find_element_by_id(list, (*human).current_block_id)).rent;
				(*computer).account += (*find_element_by_id(list, (*human).current_block_id)).rent;
			}
			else if((*find_element_by_id(list, (*human).current_block_id)).house_count == 1)
			{
				(*human).account -= (*find_element_by_id(list, (*human).current_block_id)).rent_1;
				(*computer).account += (*find_element_by_id(list, (*human).current_block_id)).rent_1;
			}
			else if((*find_element_by_id(list, (*human).current_block_id)).house_count == 2)
			{
				(*human).account -= (*find_element_by_id(list, (*human).current_block_id)).rent_2;
				(*computer).account += (*find_element_by_id(list, (*human).current_block_id)).rent_2;
			}
			else if((*find_element_by_id(list, (*human).current_block_id)).house_count == 3)
			{
				(*human).account -= (*find_element_by_id(list, (*human).current_block_id)).rent_3;
				(*computer).account += (*find_element_by_id(list, (*human).current_block_id)).rent_3;
			}
		}
	}
	else if((*find_element_by_id(list, (*human).current_block_id)).type == tax)
	{
		//Pay the tax
		(*human).account -= (*find_element_by_id(list, (*human).current_block_id)).rent;
	}
	else if((*find_element_by_id(list, (*human).current_block_id)).type == punish)
	{
		//Get punished
		(*human).turn_to_wait += (*find_element_by_id(list, (*human).current_block_id)).rent;
	}
	
	//Ask to sell property if necessary
	if((*human).account < 0)
	{	
		total = 0;
		for(int i = 0; i < 12; i++)
		{
			if((*human).owned_block_ids[i] != -1)
			{
				total += ((*find_element_by_id(list, (*human).owned_block_ids[i])).price / 2) + ((*find_element_by_id(list, (*human).owned_block_ids[i])).house_price * (*find_element_by_id(list, (*human).owned_block_ids[i])).house_count / 2);
			}
		}
		while((*human).account < 0 && (*human).account + total > 0);
		{
			show_board(list, *human, *computer);
			printf("You are in debt, you should sell a property.\n");
			sell_property(human, list);
		}
	}
}

void human_play(struct block *list, struct fortune_card cards[5], struct player *human, struct player *computer)
{
	int choice;
	int move_to;
	
	do
	{
		if((*human).turn_to_wait > 0)
		{
			(*human).turn_to_wait--;
			break;
		}
		
		show_board(list, *human, *computer);
		printf("1 - Roll the dice\n");
		printf("2 - Show my account\n");
		printf("3 - Show my properties\n");
		printf("4 - Show property deeds\n");
		printf("5 - Buy property\n");
		printf("6 - Buy house\n");
		printf("7 - Sell property\n");
		printf("Please select an option to continue: ");
		scanf("%d", &choice);
		
		switch(choice)
		{
			case 1:
				move_to = roll_the_dice(*human);
				if(move_to < (*human).current_block_id)(*human).account += 10000;
				(*human).current_block_id = move_to;
				
				manage(list, cards, human, computer);
				break;
			case 2:
				show_my_account(*human);
				break;
			case 3:
				show_my_properties(*human, list);
				break;
			case 4:
				show_properties(list);
				break;
			case 5:
				buy_property(find_element_by_id(list, (*human).current_block_id), human);
				break;
			case 6:
				buy_house(find_element_by_id(list, (*human).current_block_id), human);
				break;
			case 7:
				sell_property(human, list);
				break;
		}
	}
	while(choice != 1);
}

void computer_play(struct block *list, struct fortune_card cards[5], struct player *human, struct player *computer)
{
	int move_to;
	int dice;
	int d;
	double avg;
	int prop_count;
	int total;
	int highest;
	int id;
	int n;
	int card;
	
	if((*computer).turn_to_wait > 0)
	{
		(*computer).turn_to_wait--;
		return;
	}
	
	struct block *current_block;
	
	move_to = roll_the_dice(*computer);
	if(move_to < (*computer).current_block_id)
	{
		(*computer).account += 10000;
		dice = move_to - (*computer).current_block_id + 24;
	}
	else
	{
		dice = move_to - (*computer).current_block_id;
	}
	(*computer).current_block_id = move_to;
	
	show_board(list, *human, *computer);
	printf("The Computer has $%d.\n", (*computer).account);
	printf("Computer rolled the dice: %d\n", dice);
	
	current_block = find_element_by_id(list, (*computer).current_block_id);
	
	//After dice
	if((*find_element_by_id(list, (*computer).current_block_id)).type == fortune)
	{
		//Fortune Card
		card = rand() % 5;
		printf("The computer picked the \"%s\" card.\n", cards[card].name);
		if(card == 0)
		{
			for(int i = 23; i > -1; i--)
			{
				if((*find_element_by_id(list, i)).owner.type == (*computer).type && (*find_element_by_id(list, i)).house_count < 3)
				{
					printf("The computer has placed a house on %s.\n", (*find_element_by_id(list, i)).name);
					(*find_element_by_id(list, i)).house_count += 1;
					break;
				}
			}
		}
		else if(card == 1)
		{
			if((rand() % 6) + 1 <= 3)
			{
				printf("The computer moved two steps forward.\n");
				(*computer).current_block_id += 2;
			}
			else
			{
				printf("The computer moved two steps back.\n");
				(*computer).current_block_id -= 2;
			}
		}
		else if(card == 2)
		{
			printf("The computer paid $5000 to the bank.\n");
			(*computer).account -= 5000;
		}
		else if(card == 3)
		{
			printf("The computer paid $10000 to you.\n");
			(*computer).account -= 10000;
			(*human).account += 10000;
		}
		else if(card == 4)
		{
			printf("The computer took $20000 from the bank.\n");
			(*computer).account += 20000;
		}
	}
	
	if((*find_element_by_id(list, (*computer).current_block_id)).type == property)
	{
		if((*find_element_by_id(list, (*computer).current_block_id)).owner.type == (*human).type)
		{
			//Pay the rent
			if((*find_element_by_id(list, (*computer).current_block_id)).house_count == 0)
			{
				printf("The computer paid $%d rent to you.\n", (*find_element_by_id(list, (*computer).current_block_id)).rent);
				(*computer).account -= (*find_element_by_id(list, (*computer).current_block_id)).rent;
				(*human).account += (*find_element_by_id(list, (*computer).current_block_id)).rent;
			}
			else if((*find_element_by_id(list, (*computer).current_block_id)).house_count == 1)
			{
				printf("The computer paid $%d rent to you.\n", (*find_element_by_id(list, (*computer).current_block_id)).rent_1);
				(*computer).account -= (*find_element_by_id(list, (*computer).current_block_id)).rent_1;
				(*human).account += (*find_element_by_id(list, (*computer).current_block_id)).rent_1;
			}
			else if((*find_element_by_id(list, (*computer).current_block_id)).house_count == 2)
			{
				printf("The computer paid $%d rent to you.\n", (*find_element_by_id(list, (*computer).current_block_id)).rent_2);
				(*computer).account -= (*find_element_by_id(list, (*computer).current_block_id)).rent_2;
				(*human).account += (*find_element_by_id(list, (*computer).current_block_id)).rent_2;
			}
			else if((*find_element_by_id(list, (*computer).current_block_id)).house_count == 3)
			{
				printf("The computer paid $%d rent to you.\n", (*find_element_by_id(list, (*computer).current_block_id)).rent_3);
				(*computer).account -= (*find_element_by_id(list, (*computer).current_block_id)).rent_3;
				(*human).account += (*find_element_by_id(list, (*computer).current_block_id)).rent_3;
			}
		}
	}
	else if((*find_element_by_id(list, (*computer).current_block_id)).type == tax)
	{
		//Pay the tax
		printf("The computer paid $%d tax to the bank.\n", (*find_element_by_id(list, (*computer).current_block_id)).rent);
		(*computer).account -= (*find_element_by_id(list, (*computer).current_block_id)).rent;
	}
	else if((*find_element_by_id(list, (*computer).current_block_id)).type == punish)
	{
		//Get punished
		printf("The computer will wait for %d turns.\n", (*find_element_by_id(list, (*computer).current_block_id)).rent);
		(*computer).turn_to_wait += (*find_element_by_id(list, (*computer).current_block_id)).rent;
	}
		
	//AI part
	if((*current_block).type == property && (*current_block).owner.type == noone && (*computer).account >= (*current_block).price)
	{
		avg = 0;
		prop_count = 0;
		for(int i = 0; i < 24; i++)
		{
			if((*find_element_by_id(list, i)).type == property)
			{
				avg += (double) (*find_element_by_id(list, i)).price;
				prop_count++;
			}
		}
		avg /= (double) prop_count;
		
		if((double) (*find_element_by_id(list, (*computer).current_block_id)).price < avg || (rand() % 6) + 1 <= 3)
		{
			for(int i = 0; i < 12; i++)
			{
				if((*computer).owned_block_ids[i] == -1)
				{
					(*current_block).owner.type = (*computer).type;
					(*computer).owned_block_ids[i] = (*current_block).block_id;
					(*computer).account -= (*current_block).price;
					printf("The computer has bought %s for $%d.\n", (*current_block).name, (*current_block).price);
					break;
				}
			}
		}
	}
	
	prop_count = 0;
	for(int i = 0; i < 12; i++)
	{
		if((*computer).owned_block_ids[i] != -1)
		{
			prop_count++;
		}
	}
	if((*current_block).type == property && (*current_block).owner.type == (*computer).type && (*computer).account >= (*current_block).house_price &&  (*current_block).house_count < 3 && prop_count > 4 && (rand() % 6) + 1 <= 3)
	{
		printf("The computer has bought a house for $%d.\n", (*current_block).house_price);
		(*computer).account -= (*current_block).house_price;
		(*current_block).house_count ++;
	}
	
	if((*computer).account < 0)
	{	
		total = 0;
		for(int i = 0; i < 12; i++)
		{
			if((*computer).owned_block_ids[i] != -1)
			{
				total += ((*find_element_by_id(list, (*computer).owned_block_ids[i])).price / 2) + ((*find_element_by_id(list, (*computer).owned_block_ids[i])).house_price * (*find_element_by_id(list, (*computer).owned_block_ids[i])).house_count / 2);
			}
		}
		
		while((*computer).account < 0 && (*computer).account + total > 0)
		{
			id = -1;
			n = -1;
			highest = 0;
			for(int i = 0; i < 12; i++)
			{
				if((*computer).owned_block_ids[i] != -1 && (*find_element_by_id(list, (*computer).owned_block_ids[i])).price > highest)
				{
					highest = (*find_element_by_id(list, (*computer).owned_block_ids[i])).price;
					id = (*computer).owned_block_ids[i];
					n = i;
				}
			}
			
			printf("The computer has sold %s for $%d.\n", (*find_element_by_id(list, id)).name, ((*find_element_by_id(list, id)).price / 2) + ((*find_element_by_id(list, id)).house_count * (*find_element_by_id(list, id)).house_price / 2));
			(*find_element_by_id(list, id)).owner.type = noone;
			(*computer).owned_block_ids[n] = -1;
			(*computer).account += ((*find_element_by_id(list, id)).price / 2) + ((*find_element_by_id(list, id)).house_count * (*find_element_by_id(list, id)).house_price / 2);
			(*find_element_by_id(list, id)).house_count = 0;
		}
	}
	
	printf("Press any number to continue...\n");
	scanf("%d", &d);
}

int check_win(struct block *list, struct player human, struct player computer)
{
	int total;
	
	total = 0;
	for(int i = 0; i < 12; i++)
	{
		if(human.owned_block_ids[i] != -1)
		{
			total += ((*find_element_by_id(list, human.owned_block_ids[i])).price / 2) + ((*find_element_by_id(list, human.owned_block_ids[i])).house_price * (*find_element_by_id(list, human.owned_block_ids[i])).house_count / 2);
		}
	}
	if(human.account + total < 0)
	{
		printf("%s has won the game!\n", computer.name);
		return 1;
	}
	
	total = 0;
	for(int i = 0; i < 12; i++)
	{
		if(computer.owned_block_ids[i] != -1)
		{
			total += ((*find_element_by_id(list, computer.owned_block_ids[i])).price / 2) + ((*find_element_by_id(list, computer.owned_block_ids[i])).house_price * (*find_element_by_id(list, computer.owned_block_ids[i])).house_count / 2);
		}
	}
	if(computer.account + total < 0)
	{
		printf("%s has won the game!\n", human.name);
		return 1;
	}
}

void gameplay(struct block *list, struct player human, struct player computer)
{
	struct fortune_card cards[5];
	
	init_fortune_cards(cards);
	init_the_board(list);
	
	int end = 0;
	
	while(end != 1)
	{
		human_play(list, cards, &human, &computer);
		end = check_win(list, human, computer);
		if(end == 1)break;
		
		computer_play(list, cards, &human, &computer);
		end = check_win(list, human, computer);
		if(end == 1)break;
	}
}

int main()
{
	srand(time(NULL));
	
	struct block *list = (struct block *)malloc(sizeof(struct block));
	struct player human;
	struct player computer;
	
	human.type = car;
	human.current_block_id = 0;
	for(int i = 0; i < 12; i++)human.owned_block_ids[i] = -1;
	human.account = 100000;
	human.turn_to_wait = 0;
	human.name = "Player";
	
	computer.type = cap;
	computer.current_block_id = 0;
	for(int i = 0; i < 12; i++)computer.owned_block_ids[i] = -1;
	computer.account = 100000;
	computer.turn_to_wait = 0;
	computer.name = "Computer";

	gameplay(list, human, computer);
}
