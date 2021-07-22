#include <stdio.h>

//********** Calculator Section **********

//the function that calls operation functions below
int doit(int (*foo)(int, int), int x, int y)
{
	return foo(x, y);
}

//Basic operation functions:
int add(int x,int y)
{
	return x + y;
}

int sub(int x,int y)
{
	return x - y;
}

int multi(int x,int y)
{
	return x * y;
}

int div(int x,int y)
{
	return x / y;
}

int mod(int x,int y)
{
	return x % y;
}

int pwr(int x,int y)
{
	int res = 1;
	
	for(int i = 0; i < y; i++)
	{
		res *= x;
	}
	
	return res;
}

//main calculator function which we call from menu
void calculator()
{
	//two char variables to decide which operation to execute between "+ ", "- ", "* ", "/ ", "% ", "**"
	char a;
	char b;

	//listens an enter or space key to decide either program uses previous number or take another one from user 
	char c;

	//two input numbers and a number that stores the number from previous operation
	int num1;
	int num2;
	int num3 = 0;
	
	//main calculator loop that continues until user enters escape key
	printf("Press \"Esc + Enter\" to Exit\n\n");
	do
	{
		a = '\0';
		b = '\0';
		c = '\0';

		num1 = 0;
		num2 = 0;	
		
		scanf("\n%c", &a);
		if((int) a == 27){break;}
		scanf("%c", &b);
		scanf("%d", &num1);
		scanf("%c", &c);
		if(c != '\n')
		{
			scanf("%d", &num2);
		}
		else
		{		
			num2 = num1;
			num1 = num3;
		}
		
		if(a == '+')
		{
			num3 = doit(add, num1, num2);
		}
		else if(a == '-')
		{
			num3 = doit(sub, num1, num2);
		}
		else if(a == '*' && b != '*')
		{
			num3 = doit(multi, num1, num2);
		}
		else if(a == '/')
		{
			num3 = doit(div, num1, num2);
		}
		else if(a == '%')
		{
			num3 = doit(mod, num1, num2);
		}
		else if(a == '*' && b == '*')
		{
			num3 = doit(pwr, num1, num2);
		}
		
		printf("%d\n", num3);
	}
	while((int) a != 27);
}

//********** Weighted Average Calculation Section **********

//function that takes 10 integers for lab and homework grades
int take_grades(int ary[])
{
	for(int i = 0; i < 10; i++)
	{
		printf("Grade %d: ", i+1);
		scanf("%d",&ary[i]);
	}
	printf("\n");
}

//function that takes two exam grades
int take_exam_grades(int ary[])
{
	for(int i = 0; i < 2; i++)
	{
		printf("Grade %d: ", i+1);
		scanf("%d",&ary[i]);
	}
	printf("\n");
}

//function that calculates the average of homeworks
double calculate_homework(int ary[])
{
	int total = 0;
	
	for(int i = 0;i < 10; i++)
	{
		total += ary[i];
	}
	
	return (double)total / 10.0;
}

//function that calculates the average of lab grades
double calculate_lab(int ary[])
{
	int total = 0;
	
	for(int i = 0;i < 10; i++)
	{
		total += ary[i];
	}
	
	return (double)total / 10.0;
}

//here we calculate the weighted average
double calculate_all(int hw, int exams[], int lab)
{
	return (hw * 0.1 + lab * 0.2 + exams[0] * 0.3 + exams[1] * 0.4);
}

//********** Diamond Printing Section **********

//the main function that prints the hole diamond according to the size user enters
void diamond_print(int x)
{
	int y = x;
	
	//upper half part
	for(int i = 0; i < x; i++)
	{
		for(int i = 0; i < y-1; i++)
		{
			printf(" ");
		}
		printf("/");
		for(int i = 0; i < (x - y) * 2; i++)
		{
			printf("*");
		}
		printf("\\");

		printf("\n");
		y--;
	}

	y++;

	//lower half part
	for(int i = 0; i < x; i++)
	{
		for(int i = 0; i < y-1; i++)
		{
			printf(" ");
		}
		printf("\\");
		for(int i = 0; i < (x - y) * 2; i++)
		{
			printf("*");
		}
		printf("/");

		printf("\n");
		y++;
	}
}


//********** Main Menu Section **********
void menu()
{
	int choice;
	
	int homeworks[10];
	int labs[10];
	int exams[2];
	
	int scale;// for diamond_print()
	
	do
	{
		printf("\n*****Menu*****\n");
		printf("1. Calculator\n");
		printf("2. Weighted Average Calculation\n");
		printf("3. Diamond Printing\n");
		printf("4. Exit\n\n");
		
		scanf("%d", &choice);
		
		while(choice < 1 || choice > 4)
		{
			printf("Invalid choice!\n\n");
			scanf("%d", &choice);
		}
		printf("\n");
		
		switch (choice)
		{
			case 1:
				calculator();
				break;
				
			case 2:
				printf("Enter your homework grades:\n");
				take_grades(homeworks);
				printf("Enter your lab grades:\n");
				take_grades(labs);
				printf("Enter your exam grades:\n");
				take_exam_grades(exams);
				printf("Your weighted average is: %g\n", calculate_all(calculate_homework(homeworks),exams,calculate_lab(labs)));
				break;
				
			case 3:
				scanf("%d",&scale);
				diamond_print(scale);
				break;
		}
	}
	while(choice != 4);
}

//in int main() we only need to call menu() function
int main()
{
	menu();
}
