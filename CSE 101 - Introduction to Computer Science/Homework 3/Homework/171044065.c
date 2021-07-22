	#include <stdio.h>
	#include <math.h>
	#define TRUE 1
	#define FALSE 0
	
	int number1, number2, sum, sub, len, res;
	float div, len_temp, num_temp;
	char wanttoexit = FALSE;
	char c;
	int choice, choice2;
	int i,j;
	int myArray[100];
	int max;
	int pivot;
	int temp;
	int x,y;
	int p,q;
	
	int PrintSelection (int selection)
	{
		printf("Selected Menu item is:");
		printf("%d\n",selection);
		
		return 1;	 
	}
	
	int DisplayMenu ()
	{
		int selection;
		printf("\e[2J"); // clears screen
		 
		printf("%s","\e[5;31;47mWELCOME TO ADDING PROGRAM\e[0m\n");
		printf("%s","(1) Add two numbers\n");
		printf("%s","(2) Sort an array\n");
		printf("%s","(3) Subtract two numbers\n");
		printf("%s","(4) Divide numbers\n");
		printf("%s","(5) Summarize numbers with words\n");
		printf("%s","(6) Exponent two numbers x to the y\n");
		printf("%s","(0) quit\n");
		printf("Selection:");	
		scanf("%d",&selection);
		PrintSelection(selection);
		
		return selection;
	}
	
	//Power() function allows us to have the number a^b.
	int Power (int a, int b)
	{
		p = a;
		q = a;
		
		if (a < 0 && b)
		{
			a *= -1;
		}
		
		if (b == 0)
		{
			p = 1;
		}
		
		else if (b < 0) 
		{
			p = 0;
		}
		
		else
		{
			for (y = 1; y < b; y++)
			{
				for (x = 1; x < a; x++)
				{
					p += q;
				}
				q = p;
			}
		}
		
		if(p < 0 && b % 2 == 0)
		{
			p *= -1;
		}
		
		return p;
	}
	
	int main ()
	{	
		// main loop
		while (wanttoexit == FALSE)
		{
		
			// display menu and get result	
			choice = DisplayMenu();
						
			if (choice == 1)
			{
				printf("%s","PLEASE  ENTER FIRST NUMBER\n");
				scanf("%d",&number1);
				printf("%s","PLEASE  ENTER SECOND NUMBER\n");
				scanf("%d",&number2);
				sum = number1 + number2;
				printf("The result is: ");
				printf("%d\n",sum);
				c=getchar();
				c=getchar();
			}
			
			if (choice == 2)
			{
				printf("%s","Enter numbers for array and 0 for end\n");
				
				for(i=0;i<100;i++)
				{
					scanf("%d",&choice2);
					if(choice2 == 0) break;
					myArray[i] = choice2;
					max = i ;
				}
				
				printf("Numbers are entered.. \n");
				printf("Now sorting.. ");
			    
				for (i=0;i<=max;i++)
				{
			       for (j=0;j<max; j++)
				   {
			           if (myArray[j] > myArray[j+1])
					   {
			           		temp = myArray[j];
			           		myArray[j]= myArray[j+1];
			           		myArray[j+1]=temp;
			           }
				    }
				    
				}
				
				printf("finished..\n ");
			    
				for(i=0;i<=max;i++)
				{
			    	printf("%d  ",myArray[i]);
			    }
			    
			    printf("are the numbers.\n");
				    
				c=getchar();
				c=getchar();
			}
			
			if (choice == 3)
			{
				printf("%s","PLEASE  ENTER FIRST NUMBER\n");
				scanf("%d",&number1);
				printf("%s","PLEASE  ENTER SECOND NUMBER\n");
				scanf("%d",&number2);
				sub = number1 - number2;
				printf("The result is: ");
				printf("%d\n",sub);
				c=getchar();
				c=getchar();
			}
			
			if (choice == 4)
			{
				printf("%s","PLEASE  ENTER DIVIDEND NUMBER\n");
				scanf("%d",&number1);
				printf("%s","PLEASE  ENTER DIVISOR NUMBER\n");
				scanf("%d",&number2);
				div = (float)number1 / (float)number2;
				printf("The result is: ");
				printf("%f\n",div);
				c=getchar();
				c=getchar();
			}
			
			if (choice == 5)
			{
				printf("%s","PLEASE  ENTER THE NUMBER\n");
				scanf("%d",&number1);
				
				//With this control we take the absolute value of the number1 variable in order to prevent errors which can be caused by logarithmic operations with negative numbers.
				if (number1 < 0)
				{
					printf("%s","THE ENTERED NUMBERS ABSOLUTE VALUE HAS TAKEN\n");
					number1 *= -1;
				}

				else if (number1 == 0)
				{
					len = 0;
				}
								
				//Kind of a len_temp = log10(number1);
				num_temp = (float)number1;
				
				for (len_temp = -1; num_temp >= 1; len_temp++)
				{
					num_temp /= 10;
				}
				
				//Here we do what the floor() function in <math.h> library, does. We count the digits (n - 1).				
				for (i = 0; (float)i <= len_temp; i++)
				{
					len = i;
				}
								
				printf("The result is: ");
				printf("%d",number1);
				printf(" = ");
				
				while (len >= 0)
				{
					number2 = number1 - (number1 % Power(10,len));
					printf("%d",number2 / Power(10,len));
					
					if(len > 0)
					{
						printf("x");
						printf("%d", Power(10,len));
						printf(" + ");
					}
					number1 -= number2;
					len--;
				}
				
				c=getchar();
				c=getchar();
			}
			
			if (choice == 6)
			{
				printf("%s","PLEASE  ENTER BASE NUMBER\n");
				scanf("%d",&number1);
				printf("%s","PLEASE  ENTER EXPONENT NUMBER\n");
				scanf("%d",&number2);
				res = Power(number1, number2);
				printf("The result is: ");
				printf("%d\n",res);				
				c=getchar();
				c=getchar();
			}
			
			if (choice == 0)
			{
				wanttoexit = TRUE;
				printf("exiting...");
			}
		}
	}
