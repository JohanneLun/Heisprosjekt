#include <stdio.h>
#include <sys/time.h>

struct timer_struct{
	double three_sec_later;
};

double get_wall_time();
void set_start_time(struct timer_struct* timer);
int check_time(struct timer_struct timer);
