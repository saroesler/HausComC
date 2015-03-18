/*
 * Raspberry_GPIO.c
 *
 *  Created on: 15.07.2014
 *      Author: sascha
 */
#include "HausComC.h"
#ifdef RASPBERRY
void config_GPIO()
{
	//activate pin
	char cmd[50];
	sprintf(cmd, "echo \"4\" > /sys/class/gpio/export");
	system(cmd);
	sprintf(cmd, " echo \"out\" > /sys/class/gpio/gpio4/direction");
	system(cmd);
}

void set_GPIO_transmit()
{
	config_GPIO();
	char cmd[50];
	sprintf(cmd, "  echo \"1\" > /sys/class/gpio/gpio4/value");
	system(cmd);
}

void set_GPIO_receive()
{
	config_GPIO();
	char cmd[50];
	sprintf(cmd, "echo \"0\" > /sys/class/gpio/gpio4/value");
	system(cmd);
}
#endif
