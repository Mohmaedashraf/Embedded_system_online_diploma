/*
 * Alarm_Actuator.h
 *
 *  Created on: Mar 17, 2024
 *      Author: 3m.B
 */

#ifndef ALARM_ACTUATOR_H_
#define ALARM_ACTUATOR_H_
#include "status.h"
enum{
	off,
	on,
	Awaiting
}Alarm_Actuator_status_id;
extern void (*Alarm_Actuator_State)();
void Alarm_init();
void AlarmOff();
void AlarmOn();
void Waiting();



#endif /* ALARM_ACTUATOR_H_ */
