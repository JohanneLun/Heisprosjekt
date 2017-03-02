
#ifndef StateMachine
#define StateMachine

enum Floor{
	GROUND_FLOOR = 0,
	FIRST = 1,
	SECOND = 2,
	TOP_FLOOR = 3,
	NOT_ON_FLOOR = -1//The elevator is between two floors  
};

void stop_button_activated_ignore_orders();
void set_current_floor(void);
int get_current_floor();
void check_button_pressed_up();
void check_button_pressed_down();
void check_button_pressed_command();
void check_button_pressed();


#endif