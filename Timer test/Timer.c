//Timer will count to tre seconds
#include <sys/time.h>
#include "Timer.h"


double get_wall_time(){
    struct timeval time;
    gettimeofday(&time, NULL);
    return (double)time.tv_sec + (double)time.tv_usec * .000001;
}

int check_time(){
	double current_time = get_wall_time();
	double 3_sec_later = current_time +3;
	if (3_sec_later == current_time){
		printf("det har gått 3 sek\n");
		return 1;
	}
	else {
		printf("%f\n", 3_sec_later-current_time);
		return 0;
	}
}

