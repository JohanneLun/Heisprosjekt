#include <stdio.h>
#include "StateMachine.h"

//checks the floor sensors to tell which floor the elevator is on
int check_floor_sensors(){

	return //tall;
}

//kjøres ved sjekk av elev_get_stop_signal som returnerer 1
void stop_button_activated_ignore_orders() {
	elev_set_stop_lamp(1); //setter lampen

	if (check_floor_sensors() != -1) {
		elev_set_motor_direction(DIRN_STOP);
		//delete_Q();	//ikke inkludert i denne c-filen ennå
		while (elev_get_stop_signal() != 0) {
			//ingorer alle bestillinger
			//gjør den det pga while løkken, eller må man implementere noe for det også?
			continue;
		}
	}
	else {
		elev_set_door_open_lamp(1);
		//delete_Q();
		while (elev_get_stop_signal() != 0) {
			//ingorer alle bestillinger
			//gjør den det pga while løkken, eller må man implementere noe for det også?
			continue;
		}
		
	}
}



//Fra( Floor_Signal =elev_ get_flor_sensor_signal)
//poller alle følerene og seter etasje etter hva de returnerer
void set_current_floor(void);
	//Stuct_Current_floor.Current_Floor = elev_ get_flor_sensor_signal; 

void button_pressed()
elev_get_button_signal(BUTTON_CALL_UP, GROUND_FLOOR); 
elev_get_button_signal(BUTTON_CALL_UP, FIRST); 
elev_get_button_signal(BUTTON_CALL_UP, SECOND); 
elev_get_button_signal(BUTTON_CALL_UP, TOP_FLOOR); 

elev_get_button_signal(BUTTON_CALL_DOWN, GROUND_FLOOR); 
elev_get_button_signal(BUTTON_CALL_DOWN, FIRST); 
elev_get_button_signal(BUTTON_CALL_DOWN, SECOND); 
elev_get_button_signal(BUTTON_CALL_DOWN, TOP_FLOOR); 





Funksjoner fra elev.h :
 - int elev_init(void);
 - typedef enum tag_elev_motor_direction { 
    	DIRN_DOWN = -1,
    	DIRN_STOP = 0,
    	DIRN_UP = 1
	} elev_motor_direction_t;
 - void elev_set_motor_direction(elev_motor_direction_t dirn);
 - void elev_set_door_open_lamp(int value);
 - int elev_get_stop_signal(void);
 - void elev_set_stop_lamp(int value);
 - int elev_get_floor_sensor_signal(void);
 - void elev_set_floor_indicator(int floor);
 - typedef enum tag_elev_lamp_type { 
	    BUTTON_CALL_UP = 0,
	    BUTTON_CALL_DOWN = 1,
    	BUTTON_COMMAND = 2
	} elev_button_type_t;
 - int elev_get_button_signal(elev_button_type_t button, int floor);
 - void elev_set_button_lamp(elev_button_type_t button, int floor, int value);
