#include <stdio.h>

#include "Initialize.h"
#include "elev.h"
#include "QueueManager.h"
#include "Timer.h"



void elev_initialize() {
    struct timer_struct timer; //variabel til timeren

    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
    }

	if (elev_get_floor_sensor_signal() == -1) {
		elev_set_motor_direction(DIRN_DOWN);
		set_last_moving_motor_direction(DIRN_DOWN);

		printf("motor sensor signal = -1\n");
		while (elev_get_floor_sensor_signal() == -1) {}
	}
	elev_set_motor_direction(DIRN_STOP);
	set_motor_direction(DIRN_STOP);
	set_last_moving_motor_direction(DIRN_DOWN);
	printf("setter motor direction til NED\n");

    start_timer(&timer); //huske å fjerne alt som hører til denne timeren
    while (check_time(timer) != 1){}

}