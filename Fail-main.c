#include "elev.h"
#include <stdio.h>

#include "Timer.h"
#include "StateMachine.h"
#include "QueueManager.h"
#include "Initialize.h"


int main() {

    elev_initialize();
    struct timer_struct timer; //variabel til timeren
    int no_orders_under;
    int no_orders_over;

    while (1) {
        // setter etasjeindikator
        set_current_floor();
        elev_set_floor_indicator(get_current_floor());

        //sjekker om noen knapper har blitt trykket
        check_button_pressed();

        // nok implemetasjon av stoppknapp-funksjonalitet  i main 
        //Ny funksjon; stop_button_handeling?
        /* state = elev_get_stop _signal
            case = 1
            { kjør stop_ button handeling}
        */ 
        //handeling stop button 
        if (elev_get_stop_signal() == 1){
            stop_button_activated_ignore_orders(); 
          
            elev_set_motor_direction(DIRN_DOWN); //står her bare for testing
            set_motor_direction(DIRN_DOWN); //står her bare for testing
            set_last_moving_motor_direction(DIRN_DOWN); //står her bare for testing

            elev_set_door_open_lamp(0);
        }
        
        //må endres for å slippe å kjøre hele veien opp og ned hver gang
        //Change direction when we reach top/bottom floor
        //Kjører ikke utenfor definert område
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

        //kjører nedover 
        if (get_motor_direction() == -1) {
            printf("motor direction = -1\n");
            //Skjekker om det er noen ordre den må ta hensyn og stoppe ved 
            if (get_order_in_Q_down(get_current_floor()) == 1 || get_order_in_Q_command(get_current_floor()) == 1 ) {
                elev_set_motor_direction(DIRN_STOP);
                set_motor_direction(DIRN_STOP);
                printf("setter motor direction til 0\n");

                //åpner døren 
                elev_set_door_open_lamp(1);
                //sletter orderen fra kø
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
                //lukker døren 
                elev_set_door_open_lamp(0);
            }
        }

        if (get_motor_direction() == 1) {
            printf("motor direction = 1\n");

            if (get_order_in_Q_up( get_current_floor()) == 1 || get_order_in_Q_command(get_current_floor()) == 1) {
                elev_set_motor_direction(DIRN_STOP);
                set_motor_direction(DIRN_STOP);
                printf("setter motor direction til 0\n");

                elev_set_door_open_lamp(1);

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
            }
        }

        // manger implementasjon som bestemmer hvilken vei heisen skal begynne å kjøre etter å ha stoppet
        if (get_motor_direction() == 0) {
            printf("motor direction = 0\n");
            set_current_floor();

            //hvis vi var på veg nedover 
            if (get_last_moving_motor_direction() == DIRN_DOWN) {
                // sjekker om det ligger noe i køen for knappene under den etasjen den er i
                for (int i = get_current_floor(); i > -1; i--) {
                    printf("sjekker kø under\n");
                    if (if_order_in_floors_under(i) == 1) {
                        elev_set_motor_direction(DIRN_DOWN);
                        //set_last_moving_motor_direction(DIRN_DOWN);
                        elev_set_motor_direction(DIRN_DOWN);
                        no_orders_under = 0; //variabel for å kunne kjøre neste ifsetning
                        break;
                    }
                    else {no_orders_under = 1;}
                }
                if (no_orders_under == 1) { //dersom det ikke er noe i køen under etajsen vi er i, sjekk dem over
                    printf("sjekker kø over etter under\n");
                    for (int i = get_current_floor(); i < 4; i++) {
                        if (if_order_in_floors_over(i) == 1) {
                            elev_set_motor_direction(DIRN_UP);
                            set_last_moving_motor_direction(DIRN_UP);
                            elev_set_motor_direction(DIRN_UP);
                            printf("setter motor dir OPP\n");
                            break;
                        }
                    }
                }
            }

            if (get_last_moving_motor_direction() == DIRN_UP) {
                //sjekker om det liger noe i køen for knappene over den etajsen heisen er i
                printf("sjekker kø over\n");
                for (int i = get_current_floor(); i < 4; i++) {
                    if (if_order_in_floors_over(i) == 1) {
                        elev_set_motor_direction(DIRN_UP);
                        //set_last_moving_motor_direction(DIRN_UP);
                        elev_set_motor_direction(DIRN_UP);
                        no_orders_over = 0; //variabel for å kunne kjøre neste if-setning
                        break;
                    }
                    else {no_orders_over = 1;}
                }
                if (no_orders_over == 1) { //dersom det ikke er noe i køen over etajsen vi er i, sjekk dem under
                    printf("sjekker kø under etter over\n");
                    for (int i = get_current_floor(); i > -1; i--) {
                        if (if_order_in_floors_under(i) == 1) {
                            elev_set_motor_direction(DIRN_DOWN);
                            set_last_moving_motor_direction(DIRN_DOWN);
                            elev_set_motor_direction(DIRN_DOWN);
                            break;
                        }
                    }
                }
            }

            else {
                // stop motoren, køen er tom
                elev_set_motor_direction(DIRN_STOP);
                elev_set_motor_direction(DIRN_STOP);
            } 
        }
    }
    return 0;
}

/*
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
            }
*/
