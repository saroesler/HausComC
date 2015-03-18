/*
 * HausComC.c
 *
 *  Created on: 13.07.2014
 *      Author: sascha
 */
#include "HausComC.h"

int main(int argc, char *argv[])
{
	int Backmessage = -1;

	if (argc == 1) /* argc should be 2 for correct execution */
	{
		/* We print argv[0] assuming it is the program name */
		printf("Please insert Arguments!\nInsert -h for help!\n");
	}
	else
	{
		char Mode[2];
		Mode[0] = argv[1][0];
		Mode[1] = argv[1][1];

		int Message_len = argc - 2;

		uint8_t Data[Message_len +2 ];//+1 for XOR  +1 for End of Data
		uint8_t *Datapt = &Data[0];

		for (int i = 2; i < argc; i++)
		{
			Data[i-2] = atoi(argv[i]);
		}

		switch (Mode[0])
		/* Check for option character. */
		{
			case '-':
				switch (Mode[1])
				{
					case 'o':
						printf("Transmit message!\n");
						if (Message_len)
						{
							Backmessage = trasmit(Message_len, Datapt);
						}
						else
							printf("There is no Message to transmit!\n");
						break;
					case 'i':
						printf("Receive message!\n");
						Backmessage = receive();
						break;
					case 'd':
						printf("Receive message DEBUG!\n");
						Backmessage = receiveall();
						break;
					case 'h':
						printf("\n\n\nHausCom ---  Help!!!\n\n");
						printf("You can transmit an send data via the HausCom protocol, based on the MPC- Mode by Atmel. There are two directions you can choose:\n\n");
						printf("  -i: Input!   Here you can get data out of the UART. The data is printed in the file \"/dev/HausComI\" Please wait with reading this file until HausComC is closed by itself. Please notice that HausCom compare the XOR- checksum by itself and doesn't print it into the file!");
						printf("The Last sign is 255.");
						printf("\n\n  -o: Output!  Here you can write something in the UART. You have to write the message after \"-o\" in the commandline. Please don't write 255 at the end of the message, HausCom does it for you. Please notice that HausCom generates the XOR- checksum by itself, too!");
						printf("\n\nFor the configuration please use the file HausCom.conf. Insert \"PORT=[YOUR_PORT_NAME]\" for configure the UART- Port. For the Address please insert \"ADDRESS=[YOUR_ADDRESS]\".\n");
						printf("\n\n\n");
						break;
					default:
						printf(	"Please choose a direction!\nInsert -h for help! \n \n");
						break;
				}
				break;

			default:
				printf("Please choose a direction!\n");
				break;
		}

	}

	return Backmessage;
}
