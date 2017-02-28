#include <stdio.h>
#include <sys/time.h>

struct timer_struct{
	double initial_time;
};

double get_wall_time();
void start_timer(struct timer_struct* timer);
int check_time(struct timer_struct timer);
