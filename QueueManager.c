#include <stdio>

typedef struct {
	int motor_direction;
	struct queue_element *next;
} queue_element;


//skal denne være static??
void add_order_in_Q(queue_element* previous_Q_element){
	//previous_Q_element
	if (previous_Q_element->next == NULL) {
		previous_Q_element->next = adresse_til_det_nye_structet;
		det_nye_structet.next = NULL;
	}
	else(){
		det_nye_structet.next = previous_Q_element.next;
		// noe spesielt man må gjøre ved eventuell dereferering??
		previous_Q_element->next = adresse_til_det_nye_structet;
	}
}


void get_next_in_Q(){

}

void compare_Q_and_floor(){

}

void delete_Q(){
	
}
