#include <stdio.h>
#include "QueueManager.h"

static int motor_direction;
static int last_moving_motor_direction; //will only be 1 or -1

static int queue_up[3] = {0};
static int queue_down[3] = {0}; 
static int queue_command[4] = {0}; 

// returns the value of motor_direction
int get_motor_direction() {
	return motor_direction;
}
// sets the motor_direction equal to the parameter
void set_motor_direction(int direction) {
	motor_direction = direction;
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
	for (int i = 0; i < 3; i++) {
		queue_up[i] = 0;
		queue_down[i] = 0;
	}
	for(int i = 0; i < 4; i++) {
		queue_command[i] = 0;
	}
}
  
//if (get_current_floor() != -1 && motor_direction == 0)
void delete_executed_order(int floor){
	set_order_in_Q_command(floor, 0);
	//non-existing down-button at top floor
	if(floor == 0){}
	else {
		set_order_in_Q_down(floor-1, 0);
	}
	//non-existing up-button at top floor
	if(floor == 3){}
	else {
		set_order_in_Q_up(floor, 0);
	}
}