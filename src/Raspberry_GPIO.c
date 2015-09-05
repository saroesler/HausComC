/*
 * Raspberry_GPIO.c
 *
 *  Created on: 15.07.2014
 *      Author: sascha
 */
/*
 * Pin 17 if Raspberry of Herr Kolbe
 * Pin 4  if other Raspberry
 */

#include "HausComC.h"
#include "ConfFile.h"


#ifdef RASPBERRY
void config_GPIO()
{
	char pin[3];
	if(getPin(pin))
		return;
	//activate pin
	char cmd[50];
	sprintf(cmd, "echo \"%s\" > /sys/class/gpio/export", pin);
	system(cmd);
	sprintf(cmd, " echo \"out\" > /sys/class/gpio/gpio%s/direction", pin);
	system(cmd);
}

void set_GPIO_transmit()
{
	char pin[3];
	if(getPin(pin))
		return;
	config_GPIO();
	char cmd[50];
	sprintf(cmd, "  echo \"1\" > /sys/class/gpio/gpio%s/value", pin);
	system(cmd);
}

void set_GPIO_receive()
{
	char pin[3];
	if(getPin(pin))
		return;
	config_GPIO();
	char cmd[50];
	sprintf(cmd, "echo \"0\" > /sys/class/gpio/gpio%s/value", pin);
	system(cmd);
}
#endif
