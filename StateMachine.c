#include <stdio.h>
#include "StateMachine.h"
#include "QueueManager.h"
#include "elev.h"

static int current_floor;

//kjøres ved sjekk av elev_get_stop_signal som returnerer 1
void stop_button_activated_ignore_orders() {
	elev_set_stop_lamp(1);
	elev_set_motor_direction(DIRN_STOP);
	//delete_Q();	//ikke inkludert i denne c-filen ennå
	if (elev_get_floor_sensor_signal()== -1) {
		while (elev_get_stop_signal() != 0) {
			continue;
		}
	}
	else {
		elev_set_door_open_lamp(1);
		while (elev_get_stop_signal() != 0) {
			continue;
		}
	} 
	elev_set_stop_lamp(0); 
}
// kjører en if(i etg.){tell ned 3 sek} etter stop_button_activated_ignore orders
// hvor funksjonen tar inn et struct &timer og setter dør lampen av.

void set_current_floor(void) {
	current_floor = elev_get_floor_sensor_signal();
}
int get_current_floor() {
	return current_floor;
}

//sjekker om en knapp er trykket og legger til i kø og setter på lys, hvis en er trykket
void check_button_pressed_up() {
	if (elev_get_button_signal(BUTTON_CALL_UP, GROUND_FLOOR) == 1) {
		set_order_in_Q_up(GROUND_FLOOR, 1);
		elev_set_button_lamp(BUTTON_CALL_UP, GROUND_FLOOR, 1);
	}
	if (elev_get_button_signal(BUTTON_CALL_UP, FIRST) == 1) {
		set_order_in_Q_up(FIRST, 1);
		elev_set_button_lamp(BUTTON_CALL_UP, FIRST, 1);
	}
	if (elev_get_button_signal(BUTTON_CALL_UP, SECOND) == 1) {
		set_order_in_Q_up(SECOND, 1);
		elev_set_button_lamp(BUTTON_CALL_UP, SECOND, 1);
	}
}

void check_button_pressed_down(){
	if (elev_get_button_signal(BUTTON_CALL_DOWN, FIRST)) {
		set_order_in_Q_down(FIRST, 1);
		elev_set_button_lamp(BUTTON_CALL_DOWN, FIRST, 1);
	} 
	if (elev_get_button_signal(BUTTON_CALL_DOWN, SECOND)) {
		set_order_in_Q_down(SECOND, 1);
		elev_set_button_lamp(BUTTON_CALL_DOWN, SECOND, 1);
	} 
	if (elev_get_button_signal(BUTTON_CALL_DOWN, TOP_FLOOR)) {
		set_order_in_Q_down(TOP_FLOOR, 1);
		elev_set_button_lamp(BUTTON_CALL_DOWN, TOP_FLOOR, 1);
	} 
}
void check_button_pressed_command(){
	if (elev_get_button_signal(BUTTON_COMMAND, GROUND_FLOOR) {
		set_order_in_Q_command(GROUND_FLOOR, 1);
		elev_set_button_lamp(BUTTON_COMMAND, GROUND_FLOOR, 1);
	}
	if (elev_get_button_signal(BUTTON_COMMAND, FIRST) {
		set_order_in_Q_command(FIRST, 1);
		elev_set_button_lamp(BUTTON_COMMAND, FIRST, 1);
	}
	if (elev_get_button_signal(BUTTON_COMMAND, SECOND) {
		set_order_in_Q_command(SECOND, 1);
		elev_set_button_lamp(BUTTON_COMMAND, SECOND, 1);
	}
	if (elev_get_button_signal(BUTTON_COMMAND, TOP_FLOOR) {
		set_order_in_Q_command(TOP_FLOOR, 1);
		elev_set_button_lamp(BUTTON_COMMAND, TOP_FLOOR, 1);
	}
}
void check_button_pressed() {
	check_button_pressed_command();
	check_button_pressed_down();
	check_button_pressed_up();
}

