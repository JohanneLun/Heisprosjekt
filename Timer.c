
#include "Timer.h"

double get_wall_time(){
    struct timeval time;
    gettimeofday(&time, NULL);
    return (double)time.tv_sec + (double)time.tv_usec * .000001;
}

void start_timer(struct timer_struct* timer){
	timer->initial_time = get_wall_time();
}

int check_time(struct timer_struct timer){

	if (get_wall_time()- timer.initial_time >= 3){
		// printf("det har gått 3 sek\n");
		return 1;
	}
	else {
		//printf("start\n");
		//printf("%f\n", timer.initial_time);
		//printf("%f\n", get_wall_time()- timer.initial_time); //egentlig bare denne som skal stå der, de andre er for testing
		return 0;
	}
}