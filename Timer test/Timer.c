
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
		//printf("det har gått 3 sek\n");
		return 1;
	}
	else {
		//printf("start\n");
		//printf("%f\n", timer.three_sec_later);
		//printf("%f\n", get_wall_time()- timer.three_sec_later); //egentlig bare denne som skal stå der, de andre er for testing
		return 0;
	}
}


int start_timer(){
	struct timer_struct timer;
	set_start_time(&timer);
	int returnvalue = 0;

	// et lite problem med denne er at så lenge døra er åpen, vil man ikke kunne gjøre noe annet
	// må finne en måte å kjøre check_time uten while løkken....
	do{
		continue;
	} while(check_time(timer) != 1);

	if (check_time(timer) == 1) {
		returnvalue = 1;
	}

	printf("%d\n", returnvalue);
	return returnvalue;	
}