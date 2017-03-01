#include <stdio.h>

#include "Initialize.h"
#include "elev.h"


void elev_initialize() {

    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
    }

	if (elev_get_floor_sensor_signal() == -1) {
		elev_set_motor_direction(DIRN_DOWN);
		while (elev_get_floor_sensor_signal() == -1) {}
	}
	elev_set_motor_direction(DIRN_STOP);
}