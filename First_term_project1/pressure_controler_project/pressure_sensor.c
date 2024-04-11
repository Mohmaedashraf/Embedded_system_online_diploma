/*
 * pressure_sensor.c
 *
 *  Created on: Mar 16, 2024
 *      Author: 3m.B
 */
#include "pressure_sensor.h"
void (*PSensor_states) ();
int Pval=0;
void Sensor_init(){
	GPIO_INITIALIZATION();
}
void reading(){
	sensor_status_id= Reading;
	Pval=getPressureVal();
	Set_pressure_Val(Pval);
	Delay(6000);
		// state transition
	PSensor_states=waiting;
}
void waiting(){
	sensor_status_id=PWaiting;
	PSensor_states=reading;
}


