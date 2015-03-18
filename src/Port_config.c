#include "HausComC.h"

int open_port(void)
{
	char Port[100];

	if (getPort(Port))
	{
		int fd; /* File descriptor for the port */
		fd = open(Port, O_RDWR | O_NOCTTY | O_NDELAY);
		printf("open Port %s\n", Port);
		if (fd == -1)
		{
			/*
			 * Could not open the port.
			 */
			char Error[50] = "open_port: Unable to open Port \n";
			strcat(Error, Port);
			perror(Error);
		}
		else
			fcntl(fd, F_SETFL, 0);
		return (fd);
	}
	else
		return -1;
}

void general_conf(int fd)
{
	struct termios options;
	tcgetattr(fd, &options);
	/*
	 * Set the baud rates to 19200...
	 */
	cfsetispeed(&options, BAUDRATE);
	cfsetospeed(&options, BAUDRATE);

	//
	// Input flags - Turn off input processing
	// convert break to null byte, no CR to NL translation,
	// no NL to CR translation, don't mark parity errors or breaks
	// no input parity check, don't strip high bit off,
	// no XON/XOFF software flow control
	//
	options.c_iflag &= ~(IGNBRK | BRKINT | ICRNL | INLCR | PARMRK | INPCK
			| ISTRIP | IXON);

	// Output flags - Turn off output processing
	// no CR to NL translation, no NL to CR-NL translation,
	// no NL to CR translation, no column 0 CR suppression,
	// no Ctrl-D suppression, no fill characters, no case mapping,
	// no local output processing
	//
	// config.c_oflag &= ~(OCRNL | ONLCR | ONLRET |
	//                     ONOCR | ONOEOT| OFILL | OLCUC | OPOST);
	options.c_oflag = 0;
	//
	// No line processing:
	// echo off, echo newline off, canonical mode off,
	// extended input processing off, signal chars off
	//
	options.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN | ISIG);
	//
	// Turn off character processing
	//todo clear current char size mask, no parity checking,
	// no output processing, force 8 bit input
	//
	options.c_cflag &= ~(CSIZE | PARENB);
	options.c_cflag |= CS8;

	//options.c_cflag &= ~CSIZE; /* Mask the character size bits */
	//options.c_cflag |= CS8; /* Select 8 data bits */

	//2 Stop bits
	options.c_cflag |= CSTOPB;

	//parity error not ignore
	//mark parity errors with \377
	options.c_iflag &= ~IGNPAR;
	options.c_iflag |= PARMRK;
	//debug: options.c_iflag |= IGNPAR;
	//options.c_iflag &= ~PARMRK; // mark error with \0

	//enable input parity check
	/*options.c_iflag |= (INPCK);

	 options.c_cflag |= (PARENB );
	 options.c_cflag &= ~(PARODD );
	 options.c_cflag &= ~CMSPAR  ;*/

	tcsetattr(fd, TCSANOW, &options);

	//system("stty -a");
}

void setMARK(int fd)
{
	struct termios options;
	tcgetattr(fd, &options);

	options.c_cflag |= PARENB | CMSPAR;
	options.c_cflag &= ~PARODD;

	tcsetattr(fd, TCSANOW, &options);
}

void setSPACE(int fd)
{
	struct termios options;
	tcgetattr(fd, &options);

	options.c_cflag |= PARENB | PARODD | CMSPAR;

	tcsetattr(fd, TCSANOW, &options);
}

uint8_t getI(uint8_t Byte)
{
	uint8_t counter = 0;
	for (uint8_t i = 0; i < 8; i++)
	{
		if (Byte & 0x01)
			counter++;
		Byte >>= 1;
	}
	return counter;
}

void setAddress_filter(int fd, uint8_t MyAddress)
{
	struct termios options;
	tcgetattr(fd, &options);

	if ((getI(MyAddress) % 2))
	//there are even Is
	{
		//the 8. Bit is one, so we has to use ODD
		options.c_cflag |= (PARENB);
		options.c_cflag &= ~PARODD;
	}
	//there are odd Is
	else
	{
		//the 8. Bit is one, so we has to use EVEN
		options.c_cflag |= (PARENB | PARODD);
	}

	//enable input parity check
	options.c_iflag |= (INPCK);
	options.c_cflag &= ~CMSPAR;

	//mark parity error
	options.c_iflag &= ~IGNPAR;
	//todo
	options.c_iflag |= PARMRK;

	tcsetattr(fd, TCSANOW, &options);
}

void delAddress_filter(int fd)
{
	struct termios options;
	tcgetattr(fd, &options);


	//don't mark parity error
	options.c_iflag |= IGNPAR;
	options.c_iflag &= ~PARMRK;
	

	//disable input parity check
	options.c_iflag &= ~(INPCK);
	options.c_cflag &= ~(CMSPAR | PARENB | PARODD);
	options.c_cflag |= PARENB;

	tcsetattr(fd, TCSANOW, &options);
}
