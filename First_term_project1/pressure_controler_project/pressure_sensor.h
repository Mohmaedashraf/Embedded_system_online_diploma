/*
 * pressure_sensor.h
 *
 *  Created on: Mar 16, 2024
 *      Author: 3m.B
 */

#ifndef PRESSURE_SENSOR_H_
#define PRESSURE_SENSOR_H_
#include "status.h"
enum{
	Reading,
	PWaiting
}sensor_status_id;
void Sensor_init();
void reading();
void waiting();
extern void (*PSensor_states) ();


#endif /* PRESSURE_SENSOR_H_ */
