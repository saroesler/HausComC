/*
 * Raspberry_GPIO.h
 *
 *  Created on: 02.09.2015
 *      Author: sascha
 */

#ifndef RASPBERRY_GPIO_H_
#define RASPBERRY_GPIO_H_

#ifdef RASPBERRY

extern void config_GPIO();
extern void set_GPIO_transmit();
extern void set_GPIO_receive();

#endif


#endif /* RASPBERRY_GPIO_H_ */
