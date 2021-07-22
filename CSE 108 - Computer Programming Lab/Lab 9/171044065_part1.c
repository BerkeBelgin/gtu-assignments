#include <stdio.h>

struct Cost 
{
	int rent;
	int bill;
	int food;
	int amount;
};

int main()
{
	struct Cost house;
	
	printf("Enter the cost of rent, bill and foods: ");
	scanf("%d %d %d", &house.rent, &house.bill, &house.food);
	
	printf("Enter the number of people: ");
	scanf("%d", &house.amount);
	
	printf("\nTotal cost: %d\n", house.rent + house.bill + house.food);
	printf("Cost per student: %d\n", (house.rent + house.bill + house.food) / house.amount);
}
