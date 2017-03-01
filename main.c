#include "elev.h"
#include <stdio.h>

#include "Timer.h"
#include "StateMachine.h"
#include "QueueManager.h"
#include "Initialize.h"


int main() {
    elev_initialize();
    elev_set_motor_direction(DIRN_STOP);
    
    struct timer_struct timer; //variabel til timeren

    for (int c = 1 ; c <= 32767 ; c++ )
        for (int d = 1 ; d <= 32767 ; d++ ){}

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
            elev_set_door_open_lamp(0);
        }
        
        //må endres for å slippe å kjøre hele veien opp og ned hver gang
        //Change direction when we reach top/bottom floor
        if (elev_get_floor_sensor_signal() == N_FLOORS - 1) { 
            elev_set_motor_direction(DIRN_DOWN);
            set_motor_direction(DIRN_DOWN);
            set_last_moving_motor_direction(DIRN_DOWN);
            printf("%d\n", get_last_moving_motor_direction());
        }
        if (elev_get_floor_sensor_signal() == 0) {
            elev_set_motor_direction(DIRN_UP);
            set_motor_direction(DIRN_UP);
            set_last_moving_motor_direction(DIRN_UP);
            printf("%d\n", get_last_moving_motor_direction());
        }

        if (get_motor_direction() == -1) {
            printf("kjører nedover\n");
            if (get_order_in_Q_down(elev_get_floor_sensor_signal()) == 1 || get_order_in_Q_command(elev_get_floor_sensor_signal()) == 1) {
                elev_set_motor_direction(DIRN_STOP);
                set_motor_direction(DIRN_STOP);

                printf("inni if-løkken ved matchende etasje og order i kø\n");

                elev_set_door_open_lamp(1);
                elev_set_button_lamp(BUTTON_CALL_DOWN, elev_get_floor_sensor_signal(), 0);
                elev_set_button_lamp(BUTTON_COMMAND, elev_get_floor_sensor_signal(), 0);

                delete_executed_order(elev_get_floor_sensor_signal());

                //starter timer og sjekker knapper 
                start_timer(&timer);
                do{
                    check_button_pressed();
                    printf("sjekker timer ned\n");
                    set_current_floor();    
                    if (get_current_floor() != -1) {
                        elev_set_floor_indicator(get_current_floor());
                    }
                    continue;
                } while(check_time(timer) != 1);

                elev_set_door_open_lamp(0);
                elev_set_motor_direction(get_last_moving_motor_direction());
                set_motor_direction(get_last_moving_motor_direction());
            }
        }

        if (get_motor_direction() == 1) {
            printf("kjører oppover\n");
            if (get_order_in_Q_up( elev_get_floor_sensor_signal()) == 1 || get_order_in_Q_command(elev_get_floor_sensor_signal()) == 1) {
                elev_set_motor_direction(DIRN_STOP);
                set_motor_direction(DIRN_STOP);

                printf("inni if-løkken ved matchende etasje og order i kø\n");

                elev_set_door_open_lamp(1);
                elev_set_button_lamp(BUTTON_CALL_UP, elev_get_floor_sensor_signal(), 0);
                elev_set_button_lamp(BUTTON_COMMAND, elev_get_floor_sensor_signal(), 0);

                delete_executed_order(elev_get_floor_sensor_signal());

                //starter timer og sjekker knapper 
                start_timer(&timer);
                do{
                    check_button_pressed();
                    printf("sjekker timer opp\n");
                    set_current_floor();    
                    if (get_current_floor() != -1) {
                        elev_set_floor_indicator(get_current_floor());
                    }
                    continue;
                } while(check_time(timer) != 1);    
                elev_set_door_open_lamp(0);
                elev_set_motor_direction(get_last_moving_motor_direction());
                set_motor_direction(get_last_moving_motor_direction());
            }
        }

        // manger implementasjon som bestemmer hvilken vei heisen skal begynne å kjøre etter å ha stoppet
        if (get_motor_direction() == 0) {
            printf("kjører ingen vei\n");

            if (get_order_in_Q_up(elev_get_floor_sensor_signal()) == 1){
                printf("ligger en ordre i opp køen i denne etasjen\n");
                elev_set_door_open_lamp(1);
                for (int c = 1 ; c <= 32767 ; c++ )
                    for (int d = 1 ; d <= 32767 ; d++ ){}
                elev_set_door_open_lamp(0);
                elev_set_motor_direction(get_last_moving_motor_direction());
            }
            if (get_order_in_Q_command(elev_get_floor_sensor_signal()) == 1){
                printf("ligger en ordre i command køen i denne etasjen\n");
                elev_set_door_open_lamp(1);
                for (int c = 1 ; c <= 32767 ; c++ )
                    for (int d = 1 ; d <= 32767 ; d++ ){}
                elev_set_door_open_lamp(0);
                elev_set_motor_direction(get_last_moving_motor_direction());
            }
            if (get_order_in_Q_down(elev_get_floor_sensor_signal()) == 1){
                printf("ligger en ordre i ned køen i denne etasjen\n");
                elev_set_door_open_lamp(1);
                for (int c = 1 ; c <= 32767 ; c++ )
                    for (int d = 1 ; d <= 32767 ; d++ ){}
                elev_set_door_open_lamp(0);
                elev_set_motor_direction(get_last_moving_motor_direction());
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


