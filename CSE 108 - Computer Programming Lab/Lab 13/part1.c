#include <stdio.h>
#include <stdlib.h>

struct Stack
{
	int value;
	struct Stack *prev;
};

void print_stack(struct Stack *stack)
{
	printf("Stack:");
	if(stack == NULL)
	{
		printf(" (empty)");
	}
	else
	{
		while(stack != NULL)
		{
			printf(" %d", (*stack).value);
			stack = (*stack).prev;
		}
	}
	printf("\n");
}

void push(struct Stack **stack, int value)
{
	struct Stack *node = (struct Stack *)malloc(sizeof(struct Stack));
	(*node).value = value;
	(*node).prev = *stack;
	*stack = node;
}

int pop(struct Stack **stack)
{
	if(*stack == NULL)
	{
		printf("Output: -1\n");
	}
	else
	{
		printf("Output: %d\n", (*stack)->value);
		*stack = (*stack)->prev;
	}
}

int main()
{
	int choice;
	int input;
	
	struct Stack *top = (struct Stack *)malloc(sizeof(struct Stack));
	(*top).value = 11;
	(*top).prev = NULL;
		
	do
	{
		printf("Stack Operations:\n");
		printf("1. Print Stack\n");
		printf("2. Push\n");
		printf("3. Pop\n");
		printf("\nOperation Code: ");
		scanf("%d", &choice);
	
		switch(choice)
		{
			case 1:
				print_stack(top);
				break;
			case 2:
				printf("Input: ");
				scanf("%d", &input);
			
				push(&top, input);
				print_stack(top);
				break;
			case 3:
				pop(&top);
				print_stack(top);
				break;
		}
		printf("\n\n");
	}
	while(choice != 0);
}










