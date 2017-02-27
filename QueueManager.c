#include <stdio.h>

typedef struct {
	int motor_direction;
	struct queue_element *next;
} queue_element;

//static int head_of_Q = NULL;


//må ha en variabel hvor man lagrer en peker til adressen til det første elementet i køen
// lagres før funksjonene. Static global?

//skal denne være static??
void add_order_in_Q(queue_element *previous_Q_element, queue_element *new_Q_element){
	//warning: assignment from incompatible pointer type
	new_Q_element->next = previous_Q_element->next;
	previous_Q_element->next = new_Q_element;
}

queue_element* get_next_in_Q(queue_element* current){
	//int *temp = malloc(sizeof *temp);
	// warning: initialization makes integer from pointer without a cast
	queue_element* temp = current->next;
	return temp;
}

void compare_Q_and_floor(){
 //   ????????  
}

void delete_Q(){
	// setter head_of_Q til NULL; 
	// må man gjøre noe annet for å slette de andre elementene, 
	// eller bare forsvinner de i intet?
}

void delete_executed_order() {
	//setter den 'globale' head_of_Q til neste element
	// fjerner den forrige? bare fjerner pekeren?
}

//funksjon for å iterere over listen??
