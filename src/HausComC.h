/*
 * HausComC.h
 *
 *  Created on: 13.07.2014
 *      Author: sascha
 */

#ifndef HAUSCOMC_H_
#define HAUSCOMC_H_

#include <stdio.h> /* Standard input/output definitions */
#include <string.h> /* String function definitions */
#include <unistd.h> /* UNIX standard function definitions */
#include <fcntl.h> /* File control definitions */
#include <errno.h> /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <stdint.h>
#include <stdlib.h>

#define CMSPAR   010000000000	//hack for MARK/SPACE

#define CONF_FILE "/usr/local/etc/HausCom/HausCom.conf"
#define BAUDRATE B4800
#define OUTPUT_FILE		"/usr/local/var/HausComI"

//for the Raspberry
#define RASPBERRY


#endif /* HAUSCOMC_H_ */
