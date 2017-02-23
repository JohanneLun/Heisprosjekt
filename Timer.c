//Timer will count to tre seconds
#include <time.h>


double get_wall_time(){
    struct timeval time;
    gettimeofday(&time, NULL);
    return (double)time.tv_sec + (double)time.tv_usec * .000001;
}

int check_time(double ){
	double current_time = get_wall_time();
	double 3_sec_later = current_time +3;
	if (3_sec_later == current_time){
		return 1;
	}
	else {
		return 0;
	}
}

