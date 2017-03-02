#include "elev.h"
#include <stdio.h>

#include "Timer.h"
#include "StateMachine.h"
#include "QueueManager.h"
#include "Initialize.h"


int main() {
    elev_initialize();
    
    struct timer_struct timer; //variabel til timeren

    while (1) {
        // setter etasjeindikator
        set_current_floor();
        if (get_current_floor() != -1) {
            elev_set_floor_indicator(get_current_floor());
        }

        //sjekker om noen knapper har blitt trykket
        check_button_pressed();

        // nok implemetasjon av stoppknapp-funksjonalitet  i main 
        if (elev_get_stop_signal() == 1){
            stop_button_activated_ignore_orders(); 
            
            elev_set_motor_direction(DIRN_DOWN); //står her bare for testing
            set_motor_direction(DIRN_DOWN); //står her bare for testing
            set_last_moving_motor_direction(DIRN_DOWN); //står her bare for testing

            elev_set_door_open_lamp(0);
        }
        
        //må endres for å slippe å kjøre hele veien opp og ned hver gang
        //Change direction when we reach top/bottom floor
        if (elev_get_floor_sensor_signal() == N_FLOORS - 1) { 
            elev_set_motor_direction(DIRN_DOWN);
            set_motor_direction(DIRN_DOWN);
            set_last_moving_motor_direction(DIRN_DOWN);
        }
        if (elev_get_floor_sensor_signal() == 0) {
            elev_set_motor_direction(DIRN_UP);
            set_motor_direction(DIRN_UP);
            set_last_moving_motor_direction(DIRN_UP);
        }

        if (get_motor_direction() == -1) {
            if (get_order_in_Q_down(elev_get_floor_sensor_signal()) == 1 || get_order_in_Q_command(elev_get_floor_sensor_signal()) == 1) {
                elev_set_motor_direction(DIRN_STOP);
                set_motor_direction(DIRN_STOP);

                elev_set_door_open_lamp(1);
                elev_set_button_lamp(BUTTON_CALL_DOWN, elev_get_floor_sensor_signal(), 0);
                elev_set_button_lamp(BUTTON_COMMAND, elev_get_floor_sensor_signal(), 0);

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
                elev_set_motor_direction(get_last_moving_motor_direction());
                set_motor_direction(get_last_moving_motor_direction());
            }
            // huske å snu motor_direction?
        }

        if (get_motor_direction() == 1) {

            if (get_order_in_Q_up( elev_get_floor_sensor_signal()) == 1 || get_order_in_Q_command(elev_get_floor_sensor_signal()) == 1) {
                elev_set_motor_direction(DIRN_STOP);
                set_motor_direction(DIRN_STOP);

                elev_set_door_open_lamp(1);
                elev_set_button_lamp(BUTTON_CALL_UP, elev_get_floor_sensor_signal(), 0);
                elev_set_button_lamp(BUTTON_COMMAND, elev_get_floor_sensor_signal(), 0);

                delete_executed_order(elev_get_floor_sensor_signal());

                //starter timer og sjekker knapper 
                start_timer(&timer);
                while (check_time(timer) != 1) {
                    check_button_pressed();
                    //printf("sjekker timer opp\n");
                    set_current_floor();    
                    if (get_current_floor() != -1) {
                        elev_set_floor_indicator(get_current_floor());
                    }
                } 

                elev_set_door_open_lamp(0);
                elev_set_motor_direction(get_last_moving_motor_direction());
                set_motor_direction(get_last_moving_motor_direction());
            }
            //huske å snu motordirection?
        }

        // manger implementasjon som bestemmer hvilken vei heisen skal begynne å kjøre etter å ha stoppet
        if (get_motor_direction() == 0) {

            if (get_order_in_Q_up(elev_get_floor_sensor_signal()) == 1){
                elev_set_door_open_lamp(1);

                //starter timer og sjekker knapper 
                start_timer(&timer);
                while (check_time(timer) != 1) {
                    check_button_pressed();
                    set_current_floor();    
                    if (get_current_floor() != -1) {
                        elev_set_floor_indicator(get_current_floor());
                    }
                }  

                elev_set_door_open_lamp(0);
                elev_set_motor_direction(get_last_moving_motor_direction());
            }

            if (get_order_in_Q_command(elev_get_floor_sensor_signal()) == 1){
                elev_set_door_open_lamp(1);

                //starter timer og sjekker knapper 
                start_timer(&timer);
                while (check_time(timer) != 1) {
                    check_button_pressed();
                    set_current_floor();

                    if (get_current_floor() != -1) {
                        elev_set_floor_indicator(get_current_floor());
                    }
                }

                elev_set_door_open_lamp(0);
                elev_set_motor_direction(get_last_moving_motor_direction());
            }

            if (get_order_in_Q_down(elev_get_floor_sensor_signal()) == 1){
                elev_set_door_open_lamp(1);
 
                //starter timer og sjekker knapper 
                start_timer(&timer);
                while (check_time(timer) != 1) {
                    check_button_pressed();
                    set_current_floor();    
                    if (get_current_floor() != -1) {
                        elev_set_floor_indicator(get_current_floor());
                    }
                } 

                elev_set_door_open_lamp(0);
                elev_set_motor_direction(get_last_moving_motor_direction());
            }
            else { //skal ikke gjøre noe dersom de nikke har noe i en kø
            	//printf("nothing to do, nothing to see\n");
            }
        }
    }
    return 0;
}


/*

if (etasje =! 3) {
	sjekker_opp_og_command_kø(int etasje) {
		for (int i = etasje+1; i < 4; i++) {
			if (get_order_inQ_up(i) || get_order_in_Q_command(i)) {
				return 1;
			}
		}
		return 0;
	}
}

if etasje != 0 {
	sjekker_ned_og_command_kø(int etasje) {
		for (int i = etasje-1; i >= 0; i--) {
			if (get_order_inQ_up(i) || get_order_in_Q_command(i)) {
				return 1;
			}
		}
		return 0;
	}
}
*/