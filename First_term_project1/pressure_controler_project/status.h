/*
 * status.h
 *
 *  Created on: Mar 16, 2024
 *      Author: 3m.B
 */

#ifndef STATUS_H_
#define STATUS_H_
#include <stdio.h>
#include <stdlib.h>
#include "driver.h"
#define HIGH_PRESSURE ((int)1)
#define NORMAL_PRESSURE ((int)0)
void Set_pressure_Val(int Pval);
void Hiegh_pressure_detect();
void start_alam();
void stop_alarm();

#endif /* STATUS_H_ */
