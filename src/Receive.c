/*
 * Receive.c
 *
 *  Created on: 13.07.2014
 *      Author: sascha
 */

//fcntl(fd, F_SETFL, 0);
#include "HausComC.h"
#include "ConfFile.h"
#include "PortConfig.h"
#include "Raspberry_GPIO.h"

//Build XOR for receiver
uint8_t xor(char *Message)
{
	uint8_t temp = 0;
	printf("\n\nCheck XOR\n");
	printf("_________\n");
	while(*Message)
	{
		uint8_t new = *Message;
		printf("Check %u\n", new);
		temp = temp ^ new;
		Message++;
		printf("   calculate %u", temp);
	}

	return temp;
}

int receive()
{
	FILE *datei;
	datei = fopen(OUTPUT_FILE, "w+");
	if (datei == NULL)
	{
		perror("Can not open buffer file!");
		return -1;
	}

	int fd = open_port();

	if (fd > -1)
	{
		general_conf(fd);

		//read address
		char MyAddress = getMyAddress();

		//setAddress_filter(fd, MyAddress_i);
		uint8_t Buffer[10];
		printf("wait for address\n");
		
		//to ignore a 255 at the beginning
		//read(fd, Buffer, 1);
		
		#ifdef RASPBERRY
			set_GPIO_receive();
		#endif
		if (read(fd, Buffer, 1))
		{
			char ReceivedAddress = Buffer[0];

			printf("compare address %c, %c\n", ReceivedAddress, MyAddress);
			if (ReceivedAddress == MyAddress)
			{
				printf("myAddress detected!!\n");
				//getting Data
				char Data[10];
				uint8_t Data_i = 0;
				printf("\n\nReceive Data\n");
				printf("_______________\n");
				do{
					if (read(fd, Buffer, 1)){
						Data[Data_i++] = Buffer[0];
						printf("Received Data %c,\n", Buffer[0]);
					}else{
						printf("Error by reading message\n");
						close(fd);
						return -1;
					}
				} while(Buffer[0]);
				/*while (1)
				{
					delAddress_filter(fd);
					read(fd, Buffer, 1);
					Data[Data_i] = Buffer[0];
					printf("Received Data %u,\n", Data[Data_i]);
					if (Data[Data_i] == 255)
						break;
					Data_i++;
				}
				//get XOR- Checksum
				read(fd, Buffer, 1);
				Data[Data_i] = Buffer[0];
				printf("XOR Checksum  %u,\n", Data[Data_i]);
				Data_i++;
				
				//get End
				read(fd, Buffer, 1);
				Data[Data_i] = Buffer[0];
				printf("Received Data %u,\n", Data[Data_i]);
				
				Data[Data_i] = MyAddress_i;
				Data_i++;
				uint8_t *Datapt = &Data[0];*/
				Data_i --;
				Data[Data_i++] = MyAddress;
				Data[Data_i++] = '\0';
				if (xor(Data))
				{
					printf("There is an error in the XOR- Code!\n");
					fprintf(datei, "__XOR_ERROR__");
				}
				else
				{
					printf("\n\nData is OK!\n");

					printf("\n\nWriting Data into file\n");
					printf("_______________________\n");
					for (int i = 0; i < (Data_i - 2); i++)
					{
						printf("Writing data: %c\n", Data[i]);
						fprintf(datei, " %c;", Data[i]);
					}
				}

			}
			else
			{
				printf("ReceivedAddress: %c\n", ReceivedAddress);
				printf("Not my address. There is nothing to do!\n");
			}
			close(fd);

			printf("\n\nReceiving complete! \nThanks for using HausCom3-ASCII.\n");
			printf("If you need help, please insert \"-h\" as argument.\n\n\n");
		}
		else
			printf("Error by reading message\n");
		close(fd);

	}
	else
	{
		fprintf(datei, "Error");
		fclose(datei);
		close(fd);
		return -1;
	}
	fclose(datei);
	return 0;
}


int receiveall()
{
	FILE *datei;
	datei = fopen(OUTPUT_FILE, "w+");
	if (datei == NULL)
	{
		perror("Can not open buffer file!");
		return -1;
	}

	int fd = open_port();

	if (fd > -1)
	{
		general_conf(fd);

		//read address
		char MyAddress = getMyAddress();

		//setAddress_filter(fd, MyAddress_i);
		uint8_t Buffer[10];
		printf("wait for address\n");

		//to ignore a 255 at the beginning
		//read(fd, Buffer, 1);

		#ifdef RASPBERRY
			set_GPIO_receive();
		#endif
		if (read(fd, Buffer, 1))
		{
			char ReceivedAddress = Buffer[0];

			printf("compare address %c, %c\n", ReceivedAddress, MyAddress);
			if (ReceivedAddress == MyAddress)
			{
				printf("myAddress detected!!\n");
				//getting Data
				printf("\n\nReceive Data\n");
				printf("_______________\n");
				do{
					if (read(fd, Buffer, 1)){
						printf("Received Data %c,\n", Buffer[0]);
					}else{
						printf("Error by reading message\n");
						close(fd);
						return -1;
					}
				} while(1);
			}
			else
			{
				printf("ReceivedAddress: %u\n", ReceivedAddress);
				printf("Not my address. There is nothing to do!\n");
			}
			close(fd);

			printf("\n\nReceiving complete! \nThanks for using HausCom3-ASCII.\n");
			printf("If you need help, please insert \"-h\" as argument.\n\n\n");
		}
		else
			printf("Error by reading message\n");
		close(fd);

	}
	else
	{
		fprintf(datei, "Error");
		fclose(datei);
		close(fd);
		return -1;
	}
	fclose(datei);
	return 0;
}
