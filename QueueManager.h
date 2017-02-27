

//a queue element with the value and a pointer to the next queue element
typedef struct {
	int motor_direction;
	struct queue_element *next;
} queue_element;



//functions

//depending on the order, the function will add a 1,0 or -1 to the queue.
void add_order_in_Q();

// retrieves the next queue element/the next direction of the motor
int* get_next_in_Q();

void compare_Q_and_floor();

//deletes the entire queue and sets the first queue element to a null-pointer
void delete_Q();

