#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 20

struct stack
{
	int data;
	struct stack *next;
};

struct queue
{
	int data;
	struct queue *prev;
};

struct bst
{
	int data;
	struct bst *left;
	struct bst *right;
};

typedef struct stack stack;
typedef struct queue queue;
typedef struct bst bst;

void push_stack(stack **stack_, int data)
{
	stack *node = (stack *)malloc(sizeof(stack));
	node -> data = data;
	node -> next = *stack_;
	*stack_ = node;
}

void enqueue(queue **queue_, int data)
{
	queue **tail = queue_;
	if(*tail != NULL)
	{
		while(*tail != NULL)
		{
			tail = &((*tail) -> prev);
		}
	}
	
	queue *node = (queue *)malloc(sizeof(queue));
	node -> data = data;
	node -> prev = NULL;
	*tail = node;
}

void insert_bst(bst **bst_, int data)
{
	if(*bst_ != NULL)
	{
		if(data > (*bst_) -> data)
		{
			insert_bst(&((*bst_) -> left), data);
		}
		else if(data < (*bst_) -> data)
		{
			insert_bst(&((*bst_) -> right), data);
		}
	}
	else
	{
		bst *node = (bst *)malloc(sizeof(bst));
		node -> data = data;
		node -> left = NULL;
		node -> right = NULL;
		*bst_ = node;
	}
}

void fill_structures(stack **stack_, queue **queue_, bst **bst_, int data[ARRAY_SIZE])
{
	clock_t start;
	clock_t stop;
	double stack_t;
	double queue_t;
	double bst_t;
	
	start = clock();
	for(int i = 0; i < ARRAY_SIZE; i++)
	{
		push_stack(stack_, data[i]);
	}
	stop = clock();
	stack_t = (double)(stop - start) / CLOCKS_PER_SEC;
	
	start = clock();
	for(int i = 0; i < ARRAY_SIZE; i++)
	{
		enqueue(queue_, data[i]);
	}
	stop = clock();
	queue_t = (double)(stop - start) / CLOCKS_PER_SEC;
	
	start = clock();
	for(int i = 0; i < ARRAY_SIZE; i++)
	{
		insert_bst(bst_, data[i]);
	}
	stop = clock();
	bst_t = (double)(stop - start) / CLOCKS_PER_SEC;
	
	printf("%-16s%-16s%-16s%s\n", "Structures", "Stack", "Queue", "BST");
	printf("%-16s%-16f%-16f%f\n", "Exec. Time", stack_t, queue_t, bst_t);
}

void print_binary(bst *bst_)
{
	if(bst_ -> left != NULL)print_binary(bst_ -> left);
	printf("%d, ", bst_ -> data);
	if(bst_ -> right != NULL)print_binary(bst_ -> right);
}

void ordered_print(stack *stack_, queue *queue_, bst *bst_)
{
	if(stack_ != NULL)
	{
		clock_t start;
		clock_t stop;
		double time;
		
		start = clock();
		
		stack *copy = stack_;
		stack *head = NULL;
		stack *node = NULL;
		stack *temp = NULL;
		
		while(copy != NULL)
		{
			if(head == NULL)
			{
				temp = (stack *)malloc(sizeof(stack));
				temp -> data = copy -> data;
				temp -> next = NULL;
				head = temp;
			}
			else
			{
				if(copy -> data > head -> data)
				{
					temp = (stack *)malloc(sizeof(stack));
					temp -> data = copy -> data;
					temp -> next = head;
					head = temp;
				}
				else
				{
					node = head;
					while(node != NULL)
					{
						if(node -> next == NULL || node -> next -> data < copy -> data)
						{
							temp = (stack *)malloc(sizeof(stack));
							temp -> data = copy -> data;
							temp -> next = node -> next;
							node -> next = temp;
							break;
						}
						node = node -> next;
					}
				}
			}
			copy = copy -> next;
		}
		
		printf("\n%-16s", "Ordered Stack: ");
		node = head;
		while(node != NULL)
		{
			printf("%d", node -> data);
			if(node -> next != NULL)printf(", ");
			
			temp = node -> next;
			free(node);
			node = temp;
		}
		
		stop = clock();
		
		time = (double)(stop - start) / CLOCKS_PER_SEC;
		printf("\n%-16s%f\n", "Time: ", time);
	}
	
	if(queue_ != NULL)
	{
		clock_t start;
		clock_t stop;
		double time;
		
		start = clock();
		
		queue *copy = queue_;
		queue *head = NULL;
		queue *node = NULL;
		queue *temp = NULL;
		
		while(copy != NULL)
		{
			if(head == NULL)
			{
				temp = (queue *)malloc(sizeof(stack));
				temp -> data = copy -> data;
				temp -> prev = NULL;
				head = temp;
			}
			else
			{
				if(copy -> data > head -> data)
				{
					temp = (queue *)malloc(sizeof(stack));
					temp -> data = copy -> data;
					temp -> prev = head;
					head = temp;
				}
				else
				{
					node = head;
					while(node != NULL)
					{
						if(node -> prev == NULL || node -> prev -> data < copy -> data)
						{
							temp = (queue *)malloc(sizeof(stack));
							temp -> data = copy -> data;
							temp -> prev = node -> prev;
							node -> prev = temp;
							break;
						}
						node = node -> prev;
					}
				}
			}
			copy = copy -> prev;
		}
		
		printf("\n%-16s", "Ordered Queue: ");
		node = head;
		while(node != NULL)
		{
			printf("%d", node -> data);
			if(node -> prev != NULL)printf(", ");
			
			temp = node -> prev;
			free(node);
			node = temp;
		}		
		stop = clock();
		
		time = (double)(stop - start) / CLOCKS_PER_SEC;
		printf("\n%-16s%f\n", "Time: ", time);
	}
	
	if(bst_ != NULL)
	{
		clock_t start;
		clock_t stop;
		double time;
		
		start = clock();
		printf("\n%-16s", "Ordered BST: ");
		print_binary(bst_);
		printf("\b\b  ");
		stop = clock();
		
		time = (double)(stop - start) / CLOCKS_PER_SEC;
		printf("\n%-16s%f\n", "Time: ", time);
	}
}

int binary_search(bst *bst_, int data)
{
	printf("%d >", bst_ -> data);
	if(data == bst_ -> data)
	{
		return 0;
	}
	else if(data > bst_ -> data)
	{
		return 1 + binary_search(bst_ -> left, data);
	}
	else if(data < bst_ -> data)
	{
		 return 1 + binary_search(bst_ -> right, data);
	}
}

int check_search(bst *bst_, int data)
{
	if(data > bst_ -> data && bst_ -> left != NULL)
	{
		return check_search(bst_ -> left, data);
	}
	else if(data < bst_ -> data && bst_ -> right != NULL)
	{
		return check_search(bst_ -> right, data);
	}
	else if(data == bst_ -> data)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void search(stack *stack_, queue *queue_, bst *bst_, int val_to_search)
{
	if(stack_ != NULL)
	{
		printf("\n%-16s", "Stack Search: ");
		int found = 0;
		 
		stack *node = stack_;
		while(node != NULL)
		{
			if(node -> data == val_to_search)
			{
				found = 1;
				break;
			}
			node = node -> next;
		}
		
		if(found)
		{
			node = stack_;
			int steps = 0;
			while(node != NULL)
			{
				printf("%d > ", node -> data);
				if(node -> data == val_to_search)
				{
					printf("\b\b\b   \nFound after %d steps.\n", steps);
					break;
				}
				steps++;
				node = node -> next;
			}
		}
		else
		{
			printf("The number you are looking is missing.\n");
		}
	}
	
	if(queue_ != NULL)
	{
		printf("\n%-16s", "Queue Search: ");
		int found = 0;
		 
		queue *node = queue_;
		while(node != NULL)
		{
			if(node -> data == val_to_search)
			{
				found = 1;
				break;
			}
			node = node -> prev;
		}
		
		if(found)
		{
			node = queue_;
			int steps = 0;
			while(node != NULL)
			{
				printf("%d < ", node -> data);
				if(node -> data == val_to_search)
				{
					printf("\b\b\b   \nFound after %d steps.\n", steps);
					break;
				}
				steps++;
				node = node -> prev;
			}
		}
		else
		{
			printf("The number you are looking is missing.\n");
		}
	}
	
	if(bst_ != NULL)
	{
		printf("\n%-16s", "BST Search: ");
		
		if(check_search(bst_, val_to_search))
		{
			printf("\b\b  \nFound after %d steps.\n", binary_search(bst_, val_to_search));
		}
		else
		{
			printf("The number you are looking is missing.\n");
		}
	}
}

void swap(int *a, int *b)
{
	int c;
	
	c = *a;
	*a = *b;
	*b = c;
}

void  push_array(int *arr, int data)
{
	int n = 0;
	while(arr[n] != 0)
	{
		n++;
	}
	arr[n] = data;
}

void binary_to_array(bst *bst_, int *arr)
{
	if(bst_ -> left != NULL)binary_to_array(bst_ -> left, arr);
	push_array(arr, bst_ -> data);
	if(bst_ -> right != NULL)binary_to_array(bst_ -> right, arr);
}

void special_traverse(stack *stack_, queue *queue_, bst *bst_)
{
	if(stack_ != NULL)
	{
		int ord[ARRAY_SIZE];
		int n = 0;
		
		int new_max;
		int max = stack_ -> data;
		int min = stack_ -> data;
		for(stack *node = stack_; node != NULL; node = node -> next)
		{
			if(node -> data > max)max = node -> data;
			if(node -> data < min)min = node -> data;
		}
		
		while(n < ARRAY_SIZE)
		{
			new_max = min;
			for(stack *node = stack_; node != NULL; node = node -> next)
			{
				if(new_max < node -> data && node -> data < max)new_max = node -> data;
			}
			
			for(stack *node = stack_; node != NULL; node = node -> next)
			{
				if(node -> data == max)
				{
					ord[n] = node -> data;
					n++;
				}
			}
			max = new_max;
		}
		
		printf("%-16s", "\nStack Traverse: ");
		for(int i = 0; i < (ARRAY_SIZE - 1) - i; i++)
		{
			printf("%d, ", ord[i]);
			if(i == (ARRAY_SIZE - 1) - i)break;
			printf("%d, ", ord[(ARRAY_SIZE - 1) - i]);
		}
		printf("\b\b  \n");
	}
	
	if(queue_ != NULL)
	{
		int ord[ARRAY_SIZE];
		int n = 0;
		
		int new_max;
		int max = queue_ -> data;
		int min = queue_ -> data;
		for(queue *node = queue_; node != NULL; node = node -> prev)
		{
			if(node -> data > max)max = node -> data;
			if(node -> data < min)min = node -> data;
		}
		
		while(n < ARRAY_SIZE)
		{
			new_max = min;
			for(queue *node = queue_; node != NULL; node = node -> prev)
			{
				if(new_max < node -> data && node -> data < max)new_max = node -> data;
			}
			
			for(queue *node = queue_; node != NULL; node = node -> prev)
			{
				if(node -> data == max)
				{
					ord[n] = node -> data;
					n++;
				}
			}
			max = new_max;
		}
		
		printf("%-16s", "\nQueue Traverse: ");
		for(int i = 0; i < (ARRAY_SIZE - 1) - i; i++)
		{
			printf("%d, ", ord[i]);
			if(i == (ARRAY_SIZE - 1) - i)break;
			printf("%d, ", ord[(ARRAY_SIZE - 1) - i]);
		}
		printf("\b\b  \n");
	}
	
	if(bst_ != NULL)
	{
		int *ord = calloc(ARRAY_SIZE, sizeof(int));
		int size = ARRAY_SIZE;
		
		binary_to_array(bst_, ord);
		while(ord[size - 1] == 0)size--;
		
		printf("%-16s", "\nBST Traverse: ");
		for(int i = 0; i <= (size - 1) - i; i++)
		{
			printf("%d, ", ord[i]);
			if(i == (size - 1) - i)break;
			printf("%d, ", ord[(size - 1) - i]);
		}
		printf("\b\b  \n");
	}
}

int main()
{
	int data[ARRAY_SIZE]={5, 2, 7, 8, 11, 3, 21, 7, 6, 15, 19, 35, 24, 1, 8, 12, 17, 8, 23, 4};
	
	bst *bst_ = NULL;
	queue *queue_ = NULL;
	stack *stack_ = NULL;

	fill_structures(&stack_, &queue_, &bst_, data);
	ordered_print(stack_, queue_, bst_);
	search(stack_, queue_, bst_, 5);
	special_traverse(stack_, queue_, bst_);

	//------------------
	/*stack *node1 = stack_;
	while(node1 != NULL)
	{
		printf("%d", node1 -> data);
		if(node1 -> next != NULL)printf(" -> ");
		node1 = node1 -> next;
	}
	
	printf("\n");
	
	queue *node2 = queue_;
	while(node2 != NULL)
	{
		printf("%d", node2 -> data);
		if(node2 -> prev != NULL)printf(" -> ");
		node2 = node2 -> prev;
	}
	
	printf("\n");
	
	bst *node3 = bst_;
	while(node3 != NULL)
	{
		printf("   %-2d   \n", node3 -> data);
		if(node3 -> left != NULL)printf("%-2d", node3 -> left -> data);
		else printf("  ");
		if(node3 -> right != NULL)printf("    %-2d", node3 -> right -> data);
		printf("\n--------\n");
		node3 = node3 -> left;
	}*/
	//-------------------
	
	return 0;
}
