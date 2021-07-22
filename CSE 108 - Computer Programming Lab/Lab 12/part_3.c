#include <stdio.h>
#include <stdlib.h>

struct binarylist
{
	int node;
	struct binarylist *next;
};

int main()
{
	int n;
	int sum = 0;
	
	struct binarylist *Start = malloc(sizeof(struct binarylist));
	struct binarylist *Element = Start;
	
	scanf("%d", &n);
	(*Element).node = n;
	(*Element).next = NULL;
	
	if(n != -1)sum += n;
	
	while(n != -1)
	{
		(*Element).next = malloc(sizeof(struct binarylist));
		Element = (*Element).next;
		scanf("%d", &n);
		(*Element).node = n;
		(*Element).next = NULL;
		
		if(n != -1)sum += n;
	}
	printf("\n%d\n", sum);
	
	return 0;
}
