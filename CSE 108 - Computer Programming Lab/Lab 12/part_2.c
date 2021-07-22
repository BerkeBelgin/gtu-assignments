#include <stdio.h>
#include <stdlib.h>

struct list
{
	int node;
	struct list *next;
};

void reverse_nodes_between_n_to_m(struct list *li, int n, int m)
{
	int n1 = n;
	int n2 = m;
	int temp = 0;
	
	struct list *Start = li; 
	
	struct list *l1;
	struct list *l2;
	
	while(l1 != l2 && (*l1).next != l2)
	{
		//printf("%d", (*li).node);
		printf("%d ", n1);
		printf("%d\n", n2);
		
		if((*li).node == n1)
		{
			l1 = li;
		}
		
		if((*(*li).next).node == n2)
		{
			l2 = (*li).next;
			n2 =  (*li).node;
		}
		
		if((*(*li).next).node == -1 && (*(*li).next).next == NULL)
		{
			//printf("\n***\n");
			n1 = (*(*l1).next).node;
			
			temp = (*l1).node;
			(*l1).node = (*l2).node;
			(*l2).node = temp;
			temp = 0;
			
			li = Start;
		}
		else
		{
			//printf("\n*!*\n");
			li = (*li).next;
		}
	}
	
	li = Start;
	do
	{
		printf("%d ", (*li).node);
		li = (*li).next;
	}
	while((*li).next != NULL);
	printf("%d\n", (*li).node);
}

int main()
{
	int n;
	
	struct list *Start = malloc(sizeof(struct list));
	struct list *Element = Start;
	
	scanf("%d", &n);
	(*Element).node = n;
	(*Element).next = NULL;

	while(n != -1)
	{
		(*Element).next = malloc(sizeof(struct list));
		Element = (*Element).next;
		scanf("%d", &n);
		(*Element).node = n;
		(*Element).next = NULL;
	}

	reverse_nodes_between_n_to_m(Start, 4, 6);
	return 0;
}
