#include <stdio.h>
#include <stdlib.h>

struct binarylist
{
	int node;
	struct binarylist *next;
};

int powr(int n, int m)
{
	int res = 1;
	
	for(int i = 0; i < m; i++)
	{
		res *= n;
	}
	return res;
}

int bin2int(struct binarylist *bn)
{
	int result = 0;
	
	for(int i = 0; i < 8; i++)
	{
		if((*bn).node > 0)
		{
			result += 1 * powr(2, 7 - i);
		}
		bn = (*bn).next;
	}
	
	printf("\n%d\n", result);
}

int main()
{
	int n;
	
	struct binarylist *Start = malloc(sizeof(struct binarylist));
	struct binarylist *Element = Start;
	
	scanf("%1d", &n);
	(*Element).node = n;
	(*Element).next = NULL;

	for(int i = 0; i < 7; i++)
	{
		(*Element).next = malloc(sizeof(struct binarylist));
		Element = (*Element).next;
		scanf("%1d", &n);
		(*Element).node = n;
		(*Element).next = NULL;
	}
	
	bin2int(Start);
	
	return 0;
}
