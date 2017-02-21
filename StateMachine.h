//State machin h fil 
//Include que amnager and HW panal 
struct  Struct_Current_Floor 
{
	int Current_Floor
}

enum Floor{
	GROUND_FLOOR =0
	FIRST =1
	SECOND =2
	TOP_FLOOR =3
	NOT_ON_FLOOR =-1 // The elevator is between to floors  
}

//Fra( Floor_Signal =elev_ get_flor_sensor_signal)
//poller alle følerene og seter etasje etter hva de returnerer
void set_current_floor(void);
	//Stuct_Current_floor.Current_Floor = elev_ get_flor_sensor_signal; 

void button_pressed()
elev_get_button_signal(BUTTON_CALL_UP, GROUND_FLOOR); 
elev_get_button_signal(BUTTON_CALL_UP, FIRST); 
elev_get_button_signal(BUTTON_CALL_UP, SECOND); 
elev_get_button_signal(BUTTON_CALL_UP, TOP_FLOOR); 

elev_get_button_signal(BUTTON_CALL_DOWN, GROUND_FLOOR); 
elev_get_button_signal(BUTTON_CALL_DOWN, FIRST); 
elev_get_button_signal(BUTTON_CALL_DOWN, SECOND); 
elev_get_button_signal(BUTTON_CALL_DOWN, TOP_FLOOR); 

