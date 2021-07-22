#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
	int *pntr;
	int limit;
	int EI;
}Dyn_arr;

void init(Dyn_arr *arr)
{
	(*arr).pntr = calloc(5, sizeof(int));
	(*arr).limit = 5;
	(*arr).EI = -1;
}

void insert(Dyn_arr *arr, int index, int value)
{
	if((*arr).limit == (*arr).EI + 1)
	{
		(*arr).pntr = realloc((*arr).pntr, sizeof(int) * ((*arr).limit + 5));
		(*arr).limit += 5;
	}
	
	if(index == (*arr).EI + 1)
	{
		(*arr).EI++;
		(*arr).pntr[(*arr).EI] = value;
	}
	else if(index > (*arr).EI + 1)
	{
		(*arr).EI++;
		(*arr).pntr[(*arr).EI] = value;
		printf("Input inserted at the end of the array\n\n");
	}
	else if(index < (*arr).EI + 1)
	{
		(*arr).EI++;
		for(int i = (*arr).EI; i > index; i--)
		{
			(*arr).pntr[i] = (*arr).pntr[i - 1];
		}
		(*arr).pntr[index] = value;
	}
}

void delete(Dyn_arr *arr, int index)
{
	if(index < (*arr).EI)
	{
		(*arr).pntr[index] = 0;
		for(int i = index; i < (*arr).EI; i++)
		{
			(*arr).pntr[i] = (*arr).pntr[i + 1];
		}
		(*arr).pntr[(*arr).EI] = 0;
		(*arr).EI--;
	}
	else if(index == (*arr).EI)
	{
		(*arr).pntr[index] = 0;
		(*arr).EI--;
	}
}

int main()
{
	Dyn_arr arr;
	init(&arr);
	
	int value;
	int index;
	
	while(1)
	{
		printf("Array: [");
		for(int i = 0; i < arr.limit; i++)
		{
			printf("%d", arr.pntr[i]);
			if(i < arr.limit - 1){printf(", ");}
		}
		printf("] Limit: %d EI: %d\n", arr.limit, arr.EI);
	
		printf("User Input Value: ");
		scanf("%d", &value);
	
		printf("User Insertion Index: ");
		scanf("%d", &index);
		printf("\n");
		
		if(value == -1)
		{
			delete(&arr, index);
		}
		else
		{
			insert(&arr, index, value);
		}
	}
}
