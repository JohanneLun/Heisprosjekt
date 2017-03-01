#include "elev.h"
#include <stdio.h>

#include "Timer.h"
#include "StateMachine.h"
#include "QueueManager.h"
#include "Initialize.h"


int main() {

    elev_initialize();


    /*
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }
    printf("Press STOP button to stop elevator and exit program.\n");
*/
    elev_set_motor_direction(DIRN_UP);


    while (1) {
        // Change direction when we reach top/bottom floor
    
        if (elev_get_floor_sensor_signal() == N_FLOORS - 1) {
            elev_set_motor_direction(DIRN_DOWN);
        } else if (elev_get_floor_sensor_signal() == 0) {
            elev_set_motor_direction(DIRN_UP);
        }
        

        /*
        // Stop elevator and exit program if the stop button is pressed
        if (elev_get_stop_signal()) {
            elev_set_motor_direction(DIRN_STOP);
            break;
        } */

        check_button_pressed();
        if (elev_get_stop_signal() == 1){
            stop_button_activated_ignore_orders(); 
            elev_set_motor_direction(DIRN_DOWN);
            elev_set_door_open_lamp(0);
        }
    }
    return 0;
}