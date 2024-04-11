/*
 * MainAl.h
 *
 *  Created on: Mar 17, 2024
 *      Author: 3m.B
 */

#ifndef MAINAL_H_
#define MAINAL_H_
#include "status.h"
enum{
	pressure_detection
}High_Pressure_State_id;
extern void (*High_pressure)();
void hiegh_pressure_detect();


#endif /* MAINAL_H_ */
