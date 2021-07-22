#include <stdio.h>
#include <string.h>

typedef struct
{
	char name[12];
	char specs[12];
	int length;
	int weight;
	char nat_hab[12];
}animal;

void fill_struct_array(animal table[4])
{
	char t_name[4][12] = {{"Lion"}, {"Dolphin"}, {"Shark"}, {"Wolf"}};
	char t_specs[4][12] = {{"Mammals"}, {"Mammals"}, {"Fish"}, {"Mammals"}};
	int t_length[4] = {200, 300, 450, 160};
	int t_weight[4] = {130, 180, 250, 60};
	char t_nat_hab[4][12] = {{"Savannah"}, {"Oceans"}, {"Oceans"}, {"Forest"}};
	
	for(int i = 0; i < 4; i++)
	{
		strcpy(table[i].name, &t_name[i][0]);
		strcpy(table[i].specs, &t_specs[i][0]);
		table[i].length = t_length[i];
		table[i].weight = t_weight[i];
		strcpy(table[i].nat_hab, &t_nat_hab[i][0]);
	}
}

void length_info(animal table[4], int *min, double *avr, int *max)
{
	int res_min = table[0].length;
	int res_max = table[0].length;
	double res_avr = 0.0;
	for(int i = 0; i < 4; i++)
	{
		if(table[i].length > res_max)
		{
			res_max = table[i].length;
		}
		if(table[i].length < res_min)
		{
			res_min = table[i].length;
		}
		
		res_avr += table[i].length;
	}
	res_avr /= 4;
	
	*avr = res_avr;
	*min = res_min;
	*max = res_max;
}

void filter_mammals(animal table[4], animal filtered_animals[4])
{
	for(int i = 0; i < 4; i++)
	{
		if(table[i].weight > 100 && !strcmp(table[i].nat_hab, "Oceans"))
		{
			filtered_animals[i] = table[i];
		}
	}
}

void change_weight(animal *animal_to_change)
{
	int new_w = 0;
	
	printf("The new weight: ");
	scanf("%d", &new_w);
	(*animal_to_change).weight = new_w;
}

void print_animals(animal table[4])
{
	printf("%-14s%-14s%-8s%-8s%-14s\n", "Name", "Species", "Length", "Weight", "Nat. Hab.");
	for(int i = 0; i < 58; i++){printf("-");}
	printf("\n");
	for(int i = 0; i < 4; i++)
	{
		printf("%-14s%-14s%-8d%-8d%-14s\n", table[i].name, table[i].specs, table[i].length, table[i].weight, table[i].nat_hab);
	}
}

int main()
{
	int min, max;
	double avr;
	
	animal table[4];
	animal filtered_animals[4];
	
	fill_struct_array(table);
	length_info(table, &min, &avr, &max);
	printf("%d %d %g\n", min, max, avr);
	
	filter_mammals(table, filtered_animals);
	change_weight(&table[2]);
	print_animals(table);
}










