/*
 * MainAl.c
 *
 *  Created on: Mar 17, 2024
 *      Author: 3m.B
 */
#include "MainAl.h"
int P_val=0;
int threshold =20;
void (*High_pressure)();

void Set_pressure_Val(int Pval){
	P_val=Pval;
}
void hiegh_pressure_detect(){
	High_Pressure_State_id=pressure_detection;
	if(P_val > threshold){
			High_Pressure_Detection();
		}
	High_pressure = hiegh_pressure_detect;
}


