
#ifndef QueueManager
#define QueueManager


int get_motor_direction();
void set_motor_direction(int direction);
int get_last_moving_motor_direction();
void set_last_moving_motor_direction(int direction);
void set_order_in_Q_up(int floor, int bool_value);
void set_order_in_Q_down(int floor, int bool_value);
void set_order_in_Q_command(int floor, int bool_value);
int get_order_in_Q_up(int floor);
int get_order_in_Q_down(int floor);
int get_order_in_Q_command(int floor);
void delete_Q();
void delete_executed_order(int floor);
int if_order_in_floors_under(int floor);
int if_order_in_floors_over(int floor);
int if_order_in_Q(int floor); 


#endif