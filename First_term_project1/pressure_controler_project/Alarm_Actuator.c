/*
 * Alarm_Actuator.c
 *
 *  Created on: Mar 17, 2024
 *      Author: 3m.B
 */
#include "Alarm_Actuator.h"
 void (*Alarm_Actuator_State)();

void Alarm_init(){
	GPIO_INITIALIZATION();
}
void AlarmOff(){
	Alarm_Actuator_status_id=off;
	Set_Alarm_actuator(1);
	Alarm_Actuator_State=Waiting;
}
void AlarmOn(){
	Alarm_Actuator_status_id=on;
	Set_Alarm_actuator(0);
	Alarm_Actuator_State=Waiting;
}
void Waiting(){
	Alarm_Actuator_status_id=Awaiting;
	Alarm_Actuator_State=Waiting;
}
void start_alam(){
	Alarm_Actuator_State=AlarmOn;
	Alarm_Actuator_State();

}
void stop_alarm(){
	Alarm_Actuator_State=AlarmOff;
	Alarm_Actuator_State();
}





