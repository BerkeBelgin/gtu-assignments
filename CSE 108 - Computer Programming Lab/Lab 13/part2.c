#include <stdio.h>
#include <stdlib.h>

struct Queue
{
	int value;
	struct Queue *next;
	struct Queue *prev;
};

void print_queue(struct Queue *queue)
{
	printf("Queue:");
	if(queue == NULL)
	{
		printf(" (empty)");
	}
	else
	{
		while(queue != NULL)
		{
			printf(" %d", (*queue).value);
			queue = (*queue).prev;
		}
	}
	printf("\n");
}

void enqueue(struct Queue **queue, int value)
{
	struct Queue *node = (struct Queue *)malloc(sizeof(struct Queue));
	(*node).value = value;
	(*node).prev = NULL;
	(*node).next = *queue;
	
	(*queue)->next = node;
	*queue = node;
}

int dequeue(struct Queue **queue)
{
	if(*queue == NULL)
	{
		printf("Output: -1\n");
	}
	else
	{
		printf("Output: %d\n", (*queue)->value);
		*queue = (*queue)->prev;
	}
}

int main()
{
	int choice;
	int input;
	
	struct Queue *top = (struct Queue *)malloc(sizeof(struct Queue));
	(*top).value = 10;
	(*top).next = NULL;
	(*top).prev = NULL;
	
	struct Queue *bot = (struct Queue *)malloc(sizeof(struct Queue));
	(*bot).value = 11;
	(*bot).next = NULL;
	(*bot).prev = NULL;
	
	(*top).prev = bot;
	(*bot).next = top;
		
	do
	{
		printf("Queue Operations:\n");
		printf("1. Print Stack\n");
		printf("2. Enqueue\n");
		printf("3. Dequeue\n");
		printf("\nOperation Code: ");
		scanf("%d", &choice);
	
		switch(choice)
		{
			case 1:
				print_queue(top);
				break;
			case 2:
				printf("Input: ");
				scanf("%d", &input);
				enqueue(&bot, input);
				print_queue(top);
				break;
			case 3:
				dequeue(&top);
				print_queue(top);
				break;
		}
		printf("\n\n");
	}
	while(choice != 0);
}
