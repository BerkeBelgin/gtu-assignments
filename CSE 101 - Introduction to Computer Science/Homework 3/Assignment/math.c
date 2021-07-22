	/* THIS PROGRAM SORTS ARRAY DEMONSTRATION PURPOSES */
	/* GTU RULEZ */
	
	
	// !!! Since There were no warnings about are we allowed to use existing 
	// functions in <math.h> or not, I used pow(), abs() and log10() functions.
	// If it is a problem, I can replace them with my own algorithms. !!!
	
	
	#include <stdio.h>
	#include <math.h>
	#define TRUE 1
	#define FALSE 0
	
	int number1, number2, sum, sub, len;
	float div, res, len_temp;
	char wanttoexit = FALSE;
	char c;
	int choice;
	int i,j;
	int myArray[100];
	int max;
	int pivot;
	int temp;
	
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
					scanf("%d",&choice);
					if(choice == 0) break;
					myArray[i] = choice;
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
				
				//With abs() function we take the absolute value of the number1 variable in order to prevent errors which can be caused by logarithmic operations with negative numbers.
				len_temp = log10(abs(number1));
				
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
					//pow() function allows us to have the number 10^1, 10^2, 10^3...
					number2 = number1 - (number1 % (int)pow(10,len));
					printf("%d",number2 / (int)pow(10,len));
					
					if(len > 0)
					{
						printf("x");
						printf("%d", (int)pow(10,len));
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
				res = pow((float)number1, (float)number2);								
				
				if (number2 < 0)
				{
					printf("The result is: ");
					printf("%f\n",res);
				}
				else
				{
					printf("The result is: ");
					printf("%d\n",(int)res);
				}				
				
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
