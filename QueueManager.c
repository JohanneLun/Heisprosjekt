#include <stdio.h>
#include "QueueManager.h"
#include "elev.h"

static int motor_direction;
static int last_moving_motor_direction; //will only be 1 or -1

static int queue_up[4] = {0}; // plass for 4. etasje finnes egentlig ikke
static int queue_down[4] = {0};  // plass for 1. etasje finnes egentlig ikke
static int queue_command[4] = {0}; 

// returns the value of motor_direction
int get_motor_direction() {
	return motor_direction;
}
// sets the motor_direction equal to the parameter
void set_motor_direction(int direction) {
	motor_direction = direction;
}

// returns the value of last_moving_motor_direction
int get_last_moving_motor_direction() {
	return last_moving_motor_direction;
}
// sets the last_moving_motor_direction equal to the parameter
void set_last_moving_motor_direction(int direction) {
	last_moving_motor_direction = direction;
}

//Function for array Queue_up
// bool_value is the value in the array, representing if the 
// elevator has an order there or not
void set_order_in_Q_up(int floor, int bool_value){
	queue_up[floor] = bool_value;
}
void set_order_in_Q_down(int floor, int bool_value){
	queue_down[floor] = bool_value;
}
void set_order_in_Q_command(int floor, int bool_value){
	queue_command[floor] = bool_value;
}


// returns the value at the floor place in the array
int get_order_in_Q_up(int floor){
	return queue_up[floor];
}
int get_order_in_Q_down(int floor){
	return queue_down[floor];
}
int get_order_in_Q_command(int floor){
	return queue_command[floor];
}

// set all floor orders/the bool value to 0
void delete_Q(){
	for(int x = 0; x < 4; x++) {
		queue_command[x] = 0;
		queue_up[x] = 0;
		queue_down[x] = 0;
	}

    int i;
    // Zero all floor button lamps
    for (i = 0; i < N_FLOORS; ++i) { // burde henne ha hver implimentert i++ 
        if (i != 0)
            elev_set_button_lamp(BUTTON_CALL_DOWN, i, 0);

        if (i != N_FLOORS - 1)
            elev_set_button_lamp(BUTTON_CALL_UP, i, 0);

        elev_set_button_lamp(BUTTON_COMMAND, i, 0);
    }
}
  
void delete_executed_order(int floor){
	set_order_in_Q_command(floor, 0);
	elev_set_button_lamp(BUTTON_COMMAND, floor, 0);

	set_order_in_Q_down(floor, 0);
	elev_set_button_lamp(BUTTON_CALL_DOWN, floor, 0);

	set_order_in_Q_up(floor, 0);
	elev_set_button_lamp(BUTTON_CALL_UP, floor, 0);
}

int if_order_in_floors_under(int floor) {
    if (get_order_in_Q_down(floor) || get_order_in_Q_command(floor) || get_order_in_Q_up(floor) ) {return 1;}
    else {return 0;}
}

int if_order_in_floors_over(int floor) {
    if (get_order_in_Q_up(floor) || get_order_in_Q_command(floor) || get_order_in_Q_down(floor)) {return 1;}
    else {return 0;}
}

int if_order_in_Q(int floor) {
    if (get_order_in_Q_up(floor) || get_order_in_Q_command(floor) || get_order_in_Q_down(floor)) {return 1;}
    else {return 0;}
}

