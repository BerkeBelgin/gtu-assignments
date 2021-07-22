#include <stdio.h>
#include <stdlib.h>
#include <string.h>
	
struct Person
{
	char name[24];
	char surname[24];
	char musical_work[24];
	int age;
	struct Person *next;
}*top;

void print_menu(int *choice)
{
	printf("****MENU****\n");
	printf(" 1- Add a Person to the Stack\n");
	printf(" 2- Pop a Person from the Stack\n");
	printf(" 3- Sort Alphabetical Order\n");
	printf(" 4- Sort Age in Increasing Order\n");
	printf(" 5- Exit Menu\n");
	printf(" Select your choice: ");
	scanf("%d%*c", choice);
	printf("************\n");
}

void print_stack()
{
	struct Person *node = top;
	
	printf("--------------------\n");
	for(int i = 1; node != NULL; i++)
	{
		printf("%d) %s %s %s %d\n",i , (*node).name, (*node).surname, (*node).musical_work, (*node).age);
		node = node -> next;
	}
	printf("--------------------\n");
}

void addNode(char *name, char *surname, char *musical_work, int age)
{
	struct Person *temp = (struct Person *)malloc(sizeof(struct Person));
	strcpy((*temp).name, name);
	strcpy((*temp).surname, surname);
	strcpy((*temp).musical_work, musical_work);
	(*temp).age = age;
	(*temp).next = top;
	top = temp;
}

void push()
{
	char name[24];
	char surname[24];
	char musical_work[24];
	int age;
	
	printf("Name: ");
	scanf("%[^\n]%*c", name);
	printf("Surname: ");
	scanf("%[^\n]%*c", surname);
	printf("Creation: ");
	scanf("%[^\n]%*c", musical_work);
	printf("Age: ");
	scanf("%d%*c", &age);
	
	addNode(name, surname, musical_work, age);
}

void deleteNode()
{
	if(top != NULL)
	{
		struct Person *newtop = top -> next;
		free(top);
		top = newtop;
	}
}

void Sort_Alphabetically()
{
	if(top != NULL && top -> next != NULL)
	{
		struct Person *node = top;
		struct Person *node2 = top -> next;
		struct Person *node3 = top -> next -> next;
	
		int n = 1;
		while(n)
		{
			n = 0;
			if(strcasecmp(node2 -> name, node -> name) < 0)
			{
				node -> next = node2 -> next;
				node2 -> next = node;
				top = node2;
				
				node = top;
				node2 = top -> next;
			}
			while(node3 != NULL)
			{
				if(strcasecmp(node3 -> name, node2 -> name) < 0)
				{
					node -> next = node3;
					node2 -> next = node3 -> next;
					node3 -> next = node2;
					
					node2 = node -> next;
					node3 = node2 -> next;
					n = 1;
				}
			
				node = node -> next;
				node2 = node2 -> next;
				node3 = node3 -> next;
			}
		
			node = top;
			node2 = top -> next;
			node3 = top -> next -> next;
		}
	}
}

void Sort_Increasingly()
{
	if(top != NULL && top -> next != NULL)
	{
		struct Person *node = top;
		struct Person *node2 = top -> next;
		struct Person *node3 = top -> next -> next;
	
		int n = 1;
		while(n)
		{
			n = 0;
			if(node2 -> age < node -> age)
			{
				node -> next = node2 -> next;
				node2 -> next = node;
				top = node2;
				
				node = top;
				node2 = top -> next;
			}
			while(node3 != NULL)
			{
				if(node3 -> age < node2 -> age)
				{
					node -> next = node3;
					node2 -> next = node3 -> next;
					node3 -> next = node2;
					
					node2 = node -> next;
					node3 = node2 -> next;
					n = 1;
				}
			
				node = node -> next;
				node2 = node2 -> next;
				node3 = node3 -> next;
			}
		
			node = top;
			node2 = top -> next;
			node3 = top -> next -> next;
		}
	}
}

int main()
{
	int choice;
	top = NULL;
	
	do
	{
		print_menu(&choice);
		switch (choice)
		{
		case 1:
			push();
			print_stack();
			break;
		case 2:
			deleteNode();
			print_stack();
			break;
		case 3:
			Sort_Alphabetically();
			print_stack();
			break;
		case 4:
			Sort_Increasingly();
			print_stack();
			break;
		}
	}
	while(choice != 5);
}
