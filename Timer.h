#ifndef TimerHFile
#define TimerHFile

#include <stdio.h>
#include <sys/time.h>


static double timeStamp;

// utlevert funksjon som henter ant sekunder siden 1.jan 1970
double get_wall_time();

//starter timeren, setter initial_time lik get_wall_time()
void start_timer();

//Returnerer 1 hvis det har gått 3 sekunder, og 0 ellers
int check_time();




#endif