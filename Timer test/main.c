

#include "Timer.h"

int main() {
	// fra her
	struct timer_struct timer;
	int returnvalue = 0;
	int timer_started = 0;  //settes til 1 når timeren startes og, setter til 0 
							//når timeren har telt 3 sekunder

	start_timer(&timer);

	do{
		continue;
	} while(check_time(timer) != 1);

	if (check_time(timer) == 1) {
		returnvalue = 1;
	}

	printf("%d\n", returnvalue);
	return returnvalue;	
	// til hit i hovedmain ish funksjon

	return 0;
}