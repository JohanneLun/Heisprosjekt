

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
		timer_started = 0;
	}

	printf("%d\n", returnvalue);
	return returnvalue;	
	// til hit i hovedmain ish funksjon

	return 0;
}

void funk_som_haandterer_at_heisen_skal_stoppe(struct timer_struct *timer) {

	elev_set_motor_direction(DIRN_STOP);
    set_motor_direction(DIRN_STOP);

    elev_set_door_open_lamp(1);
    delete_executed_order(elev_get_floor_sensor_signal());

    //starter timer og sjekker knapper 
    start_timer(&timer);
    while (check_time(timer) != 1){
        check_button_pressed();
        set_current_floor();   

        if (get_current_floor() != -1) {
            elev_set_floor_indicator(get_current_floor());
        }
    }

    elev_set_door_open_lamp(0);
}