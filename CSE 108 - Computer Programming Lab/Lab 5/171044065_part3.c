#include <stdio.h>

typedef enum 
{ Mon, Tue, Wed, Thu, Fri, Sat, Sun }
days;

typedef enum 
{ Jan, Feb, Mar, Apr, May, June, July, Aug, Sep, Oct, Nov, Dec }
months;

typedef enum 
{ _2019, _2020, _2021, _2022, _2023 }
years;

void calc_date(int n, days *dm, int *d, months *m, years *y)
{
	*dm = n % 7;
	*d = n;
	
	while(*d >= 30)
	{
		*d -= 30;
		*m += 1;
	}
	while(*m >= 12)
	{
		*m -= 12;
		*y += 1;
	}
}

int main()
{
	days dm = Mon;
	int d = 0;
	months m = Jan;
	years y = _2019;
	
	calc_date(30, &dm, &d, &m, &y);
	
	switch(dm)
	{
		case Mon:
			printf("Monday ");
			break;
		case Tue:
			printf("Tuesday ");
			break;
		case Wed:
			printf("Wednesday ");
			break;
		case Thu:
			printf("Thursday ");
			break;
		case Fri:
			printf("Friday ");
			break;
		case Sat:
			printf("Saturday ");
			break;
		case Sun:
			printf("Sunday ");
			break;
	}
	
	printf("dm = %d ", d + 1);
	
	switch(m)
	{
		case Jan:
			printf("m = January ");
			break;
		case Feb:
			printf("m = February ");
			break;
		case Mar:
			printf("m = March ");
			break;
		case Apr:
			printf("m = April ");
			break;
		case May:
			printf("m = May ");
			break;
		case June:
			printf("m = June ");
			break;
		case July:
			printf("m = July ");
			break;
		case Aug:
			printf("m = August ");
			break;
		case Sep:
			printf("m = September ");
			break;
		case Oct:
			printf("m = October ");
			break;
		case Nov:
			printf("m = November ");
			break;
		case Dec:
			printf("m = December ");
			break;
	}
	
	switch(y)
	{
		case _2019:
			printf("y = 2019\n");
			break;
		case _2020:
			printf("y = 2020\n");
			break;
		case _2021:
			printf("y = 2021\n");
			break;
		case _2022:
			printf("y = 2022\n");
			break;
		case _2023:
			printf("y = 2023\n");
			break;
	}
}
