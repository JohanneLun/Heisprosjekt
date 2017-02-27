
#include "Timer.h"

//henter sekunder siden jan 1970 eln. og returnerer det
double get_wall_time(){
    struct timeval time;
    gettimeofday(&time, NULL);
    return (double)time.tv_sec + (double)time.tv_usec * .000001;
}

void set_start_time(struct timer_struct* timer){
	timer->three_sec_later = get_wall_time();
}

//skal sjekke tiden
int check_time(struct timer_struct timer){

	if (get_wall_time()- timer.three_sec_later >= 3){
		printf("det har gått 3 sek\n");
		return 1;
	}
	else {
		printf("start\n");
		printf("%f\n", timer.three_sec_later);
		printf("%f\n", get_wall_time()- timer.three_sec_later); //egentlig bare denne som skal stå der, de andre er for testing
		return 0;
	}
}

