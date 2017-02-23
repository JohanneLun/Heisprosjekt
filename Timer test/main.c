#include <stdio.h>
#include <sys/time.h>

//henter sekunder siden jan 1970 eln. og returnerer det
double get_wall_time(){
    struct timeval time;
    gettimeofday(&time, NULL);
    return (double)time.tv_sec + (double)time.tv_usec * .000001;
}

//skal sjekke tiden
int check_time(){
	double current_time = get_wall_time(); //lagrer 1970 tiden som current_time
	double three_sec_later = current_time +3; //legger til 3 sek

	if (three_sec_later == get_wall_time()){
		printf("det har gått 3 sek\n");
		return 1;
	}
	else {
		printf("start\n");
		printf("%f\n", three_sec_later - get_wall_time()); //egentlig bare denne som skal stå der, de andre er for testing
		printf("%f\n", get_wall_time());
		printf("%f\n", three_sec_later);
		return 0;
	}
}



int main(){
	while(check_time() != 1){
		check_time();
	}

	return 1;
}