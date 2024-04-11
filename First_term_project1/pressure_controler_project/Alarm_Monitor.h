/*
 * Alarm_Monitor.h
 *
 *  Created on: Mar 17, 2024
 *      Author: 3m.B
 */

#ifndef ALARM_MONITOR_H_
#define ALARM_MONITOR_H_
#include "status.h"
enum{
	alarmoff,
	alarmon,
	alarmwaiting
}Alarm_Monitor_status_id;
extern void (*Alarm_Monitor_State)();
void Off();
void On();
void Wait();


#endif /* ALARM_MONITOR_H_ */
