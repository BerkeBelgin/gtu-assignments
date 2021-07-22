#include <stdio.h>

struct TIME 
{
	int hr;
	int mn;
	int sn;
};

void difference_time(struct TIME start, struct TIME stop, struct TIME *diff)
{
	(*diff).hr = start.hr - stop.hr;
	diff->mn = start.mn - stop.mn;
	(*diff).sn = start.sn - stop.sn;
	
	
}

int main()
{
	struct TIME start;
	struct TIME stop;
	struct TIME diff;
	
	printf("Start time (h m s): ");
	scanf("%d %d %d", &start.hr, &start.mn, &start.sn);
	printf("Stop time (h m s): ");
	scanf("%d %d %d", &stop.hr, &stop.mn, &stop.sn);
	
	difference_time(start, stop, &diff);
		
	printf("Time elapsed: %d:%d:%d - %d:%d:%d = %d:%d:%d\n", start.hr, start.mn, start.sn, stop.hr, stop.mn, stop.sn, diff.hr, diff.mn, diff.sn);
}
