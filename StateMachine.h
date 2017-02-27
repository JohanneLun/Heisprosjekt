

// eller ha denne structen som en global static variabel eller bare en funksjon som
// sjekker etasjefølerene hver gang man trenger å finn ut hvilken etg man er i
struct  Struct_Current_Floor {
	int Current_Floor
}

enum Floor{
	GROUND_FLOOR =0
	FIRST =1
	SECOND =2
	TOP_FLOOR =3
	NOT_ON_FLOOR =-1 // The elevator is between to floors  
}

struct Button_Pressed{
	int floor;
	enum Floor floor;
};


//Fra( Floor_Signal =elev_ get_flor_sensor_signal)
//poller alle følerene og seter etasje etter hva de returnerer
void set_current_floor(void);
	//Stuct_Current_floor.Current_Floor = elev_ get_flor_sensor_signal; 

int button_pressed();
