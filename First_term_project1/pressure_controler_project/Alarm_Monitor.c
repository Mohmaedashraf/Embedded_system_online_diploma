/*
 * Alarm_Monitor.c
 *
 *  Created on: Mar 17, 2024
 *      Author: 3m.B
 */
#include "Alarm_Monitor.h"
void (*Alarm_Monitor_State)(void);
void High_Pressure_Detection(void){
	Alarm_Monitor_State = On;
}
void Off(){
	Alarm_Monitor_status_id=alarmoff;
	stop_alarm();
	Alarm_Monitor_State=Off;

}

void On(){
	Alarm_Monitor_status_id=alarmon;
	start_alam();
	Delay(60000);
	Alarm_Monitor_State=Wait;
}
void Wait(){
	Alarm_Monitor_status_id=alarmwaiting;
	Alarm_Monitor_State=Off;
}



