#include "elev.h"
#include <stdio.h>

#include "Timer.h"
#include "StateMachine.h"
#include "QueueManager.h"
#include "Initialize.h"


int main() {
    elev_initialize();
    elev_set_motor_direction(DIRN_STOP);

    for (int c = 1 ; c <= 32767 ; c++ )
    for (int d = 1 ; d <= 32767 ; d++ ){}

    while (1) {
        set_current_floor();
        if (get_current_floor() != -1) {
            elev_set_floor_indicator(get_current_floor());
        }

        check_button_pressed();

        if (elev_get_stop_signal() == 1){
            stop_button_activated_ignore_orders(); 
            elev_set_door_open_lamp(0);
        }

        //Change direction when we reach top/bottom floor
        if (elev_get_floor_sensor_signal() == N_FLOORS - 1) { 
            elev_set_motor_direction(DIRN_DOWN);
        }
        if (elev_get_floor_sensor_signal() == 0) {
            elev_set_motor_direction(DIRN_UP);
        }

        if (get_motor_direction() == -1) {
            if (get_order_in_Q_down( elev_get_floor_sensor_signal() ) == 1 || get_order_in_Q_command(elev_get_floor_sensor_signal()) == 1) {
                elev_set_motor_direction(DIRN_STOP);
                elev_set_door_open_lamp(1);
                delete_executed_order(elev_get_floor_sensor_signal());
                for (int c = 1 ; c <= 32767 ; c++ ){
                for (int d = 1 ; d <= 32767 ; d++ ){}
                }
                //åpne døra
                //teller ned 3 sek.
                //lukke døra/skru av lys
            }
        }
        if (get_motor_direction() == 1) {
            if (get_order_in_Q_up( elev_get_floor_sensor_signal() ) == 1 || get_order_in_Q_command(elev_get_floor_sensor_signal()) == 1) {
                elev_set_motor_direction(DIRN_STOP);
                elev_set_door_open_lamp(1);
                delete_executed_order(elev_get_floor_sensor_signal());

                for (int c = 1 ; c <= 32767 ; c++ ){
                for (int d = 1 ; d <= 32767 ; d++ ){}
                }
                //åpne døra
                //teller ned 3 sek.
                //lukke døra/skru av lys
            }
        }
        if (get_motor_direction() == 0) {
            
            if (get_order_in_Q_up(elev_get_floor_sensor_signal()) == 1 ){

            }
            if (get_order_in_Q_command(elev_get_floor_sensor_signal()) == 1 )
                || get_order_in_Q_down(elev_get_floor_sensor_signal()) == 1) {
                for (int c = 1 ; c <= 32767 ; c++ ){
                for (int d = 1 ; d <= 32767 ; d++ ){}
                }
                //åpne døra
            }
        }

    }
    return 0;
}



/* Pseudokode for inni while-løkken i main
if else(noe i opp-køen) {
    kjør til den etasjen noen har bestilt heisen til
} 
if else(noe i ned-køen) {
    kjør til den etasjen noen har bestilt heisen til
}
if else(noe i command-køen) {
    kjør til den etasjen noen har bestilt heisen til
}
else (tom kø) {
    sett motor til 0/STOP
}

*/

/*
        if (get_order_in_Q_up(2) == 1){

            set_order_in_Q_up(2,0);
            elev_set_button_lamp(BUTTON_CALL_UP,2, 0);
        }
*/

/*
        // Stop elevator and exit program if the stop button is pressed
        if (elev_get_stop_signal()) {
            elev_set_motor_direction(DIRN_STOP);
            break;
        } 
*/


