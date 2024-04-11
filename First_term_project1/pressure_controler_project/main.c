
#include "driver.h"
#include "pressure_sensor.h"
#include "Alarm_Actuator.h"
#include "MainAl.h"
#include "Alarm_Monitor.h"
void init(){
	Sensor_init();
	Alarm_init();
	PSensor_states=reading;
	High_pressure = hiegh_pressure_detect;
	Alarm_Monitor_State=AlarmOff;
	Alarm_Actuator_State=Waiting;

}
int main (){
	init();
	GPIO_INITIALIZATION();
	while (1)
	{
		PSensor_states();
		High_pressure();
		Alarm_Monitor_State();
		Alarm_Actuator_State();
	}

}
