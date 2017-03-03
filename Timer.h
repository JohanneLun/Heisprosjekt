#ifndef TimerHFile
#define TimerHFile


#include <stdio.h>
#include <sys/time.h>

struct timer_struct{
	double initial_time;
};

// utlevert funksjon som henter ant sekunder siden 1.jan 1970
double get_wall_time();

//starter timeren, setter initial_time lik get_wall_time()
void start_timer(struct timer_struct* timer);

//Returnerer 1 hvis det har gått 3 sekunder, og 0 ellers
int check_time(struct timer_struct timer);




#endif