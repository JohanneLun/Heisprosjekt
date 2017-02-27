
#include "Timer.h"



int main(){
	struct timer_struct timer;
	set_start_time(&timer);

	do{
		check_time(timer);
	} while(check_time(timer) != 1);

	return 1;
}