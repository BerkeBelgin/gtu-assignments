#include <stdio.h>

//multiplies all elements in the array recursively
int common(int * arr, int n)
{
	if(n == 1)
	{
		return 1;
	}
	else
	{
		return arr[0] * common(&arr[1], n - 1);
	}
}

//main function for the first part
void divisors()
{
	int num[2];
	int temp;
	
	int arr_num[2][12];
	int m;
	
	int cmn[12];
	int k;
	
	printf("\e[1;1H\e[2J");
	
	printf("Enter two numbers.\n\n");
	printf("First number: \n");
	scanf("%d", &num[0]);
	printf("Second number: \n");
	scanf("%d", &num[1]);
	
	//for two of the numbers
	for(int n = 0; n < 2; n++)
	{
		m = 0;
		
		//if the number is negative add -1 to its divisors and multiply it with -1
		if(num[n] < 0)
		{
			arr_num[n][m] = -1;
			m++;
			temp = num[n] * -1;
		}
		else
		{
			temp = num[n];
		}
		
		//while the number is greater than 1 try to divide it to numbers and add divisors to the 2d array
		while(temp > 1)
		{
			for(int i = 2; i <= temp; i++)
			{
				if(temp % i == 0)
				{
					arr_num[n][m] = i;
					m++;
					
					temp = temp / i;					
					break;
				}
			}
		}
	}
	
	k = 0;

	//If there are any same divisors copy the number to the cmn array and replace them with 0's.
	for(int x = 0; x < 12; x++)
	{
		for(int y = 0; y < 12; y++)
		{
			if(arr_num[0][x] == arr_num[1][y] && arr_num[1][x] != 0 && arr_num[1][y] != 0)
			{
				cmn[k] = arr_num[0][x];
				k++;
				
				arr_num[1][x] = 0;
				arr_num[1][y] = 0;
				
				break;
			}
		}
	}

	printf("\nThe greatest common divisor is: %d\n\n", common(cmn, k));
}

//the part we compare merge the array
void merging(int low, int mid, int high, int *a, int *b) 
{
	int l1, l2, i;

	for(l1 = low, l2 = mid + 1, i = low; l1 <= mid && l2 <= high; i++) 
	{
		if(a[l1] <= a[l2])
		{
			b[i] = a[l1++];
		}
		else
		{
			b[i] = a[l2++];
		}
	}
   	
   	while(l1 <= mid)
   	{
   		b[i++] = a[l1++];
   	}

	while(l2 <= high)
	{   
		b[i++] = a[l2++];
	}

	for(i = low; i <= high; i++)
	{
		a[i] = b[i];
	}
}

//the part we call functions recursively and cut the array to half
void sort(int low, int high, int *a, int *b) 
{
   int mid;
   
   if(low < high) 
   {
      mid = (low + high) / 2;
      sort(low, mid, a, b);
      sort(mid+1, high, a, b);
      merging(low, mid, high, a, b);
   } 
   else 
   { 
      return;
   }
}

//main function for the merge-sort part
void merge_sort()
{
	printf("\e[1;1H\e[2J");
	
	int n;
	
	printf("Enter the length of the list: ");
	scanf("%d", &n);
	
	int a[n];
	int b[n];
	
	printf("Enter the elements of the list:\n");
	for(int i = 0; i < n; i++)
	{
		scanf("%d", &a[i]);
	}
	
	sort(0, n - 1, a, b);
	
	printf("\nThe sorted array is: ");
	for(int i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n\n");
}

//the function on the pdf we implament recursively
int fn(int n)
{
	printf(" %d", n);
	
	if(n > 1)
	{
		if(n % 2 == 0)
		{
			return fn(n/2);
		}
		else
		{
			return fn(3 * n + 1);
		}
	}
	else
	{
		return n;
	}
}
//main function for the 3rd part
void fn_menu()
{
	int n;
	printf("\e[1;1H\e[2J");
	
	printf("Input: ");
	scanf("%d", &n);
	
	printf("Output:");
	fn(n);
	printf("\n\n");
}

//a function to find power of a number recursively
int power(int n, int m)
{
	if(m > 0)
	{
		return n * power(n, m - 1);
	}
	else
	{
		return 1;
	}
}

//the function we implament the formula on the pdf
int formula(int n)
{
	if(n < 10000 && n >= 1000)
	{
		return power((n - (n % 1000)) / 1000, 4) + power(((n % 1000) - (n % 100)) / 100, 4) + power(((n % 100) - (n % 10)) / 10, 4) + power(n % 10, 4);
	}
	else if(n < 1000 && n >= 100)
	{
		return power((n - (n % 100)) / 100, 3) + power(((n % 100) - (n % 10)) / 10, 3) + power(n % 10, 3);
	}
	else if(n < 100 && n >= 10)
	{
		return power((n - (n % 10)) / 10, 2) + power(n % 10, 2);
	}
	else
	{
		return n;
	}
}

//main function for the 4th part
void formula_menu()
{
	int n;
	printf("\e[1;1H\e[2J");
	
	printf("Input: ");
	scanf("%d", &n);
	
	printf("Output: ");
	if(n == formula(n))
	{
		printf("Equal");
	}
	else
	{
		printf("Not Equal");
	}
	printf("\n\n");
}

//Checks if any capital letter exists recursively and returns it
char findcapital(char *str)
{
	if(str[0] >= 65 && str[0] <= 90)
	{
		return str[0];
	}
	else if(str[0] == '\n')
	{
		return '-';
	}
	else
	{
		return findcapital(&str[1]);
	}
}

//Main function for the 5th part
void cap_menu()
{
	char str[36];
	for(int i = 0; i < 36; i++){str[i] = '\0';}
	str[35] = '\n';

	printf("\e[1;1H\e[2J");
	
	printf("Input: ");
	scanf("%s", str);
	
	printf("Output: %c", findcapital(str));
	printf("\n\n");
}

//Main menu function
void menu()
{
	printf("\e[1;1H\e[2J");
	
	int choice;
	
	do
	{
		printf("1) The greatest common divisor\n");
		printf("2) Merge Sort\n");
		printf("3) f(n)\n");
		printf("4) Formula\n");
		printf("5) Find Capital\n");
		printf("6) Exit\n");
		
		scanf("%d", &choice);
		
		switch (choice)
		{
			case 1:
				divisors();
				break;
			case 2:
				merge_sort();
				break;
			case 3:
				fn_menu();
				break;
			case 4:
				formula_menu();
				break;
			case 5:
				cap_menu();
				break;
			case 6:
				break;
		}
	}
	while(choice != 6);
}

int main()
{
	menu();	
	return 0;
}

