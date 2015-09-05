#include "HausComC.h"
#include "ConfFile.h"
#include "PortConfig.h"
#include "Raspberry_GPIO.h"

int trasmit(uint8_t datac, char *data)
{
#ifdef RASPBERRY
	set_GPIO_transmit();
	printf("Block RS485- BUS\n");
#endif

	int fd = open_port();
	if (fd > -1)
	{
		general_conf(fd);

		//calculating xor
		uint8_t Xor = xor(data);
		printf("XOR-Generated: Wert = %d\n", Xor);

		/*uint8_t *XorData;
		XorData = data + datac + 1;
		*XorData = Xor;
		
		//put 255 before XOR
		XorData --;
		*XorData = 255;*/

		printf("\n\nTransmitting data\n");
		printf("_________________\n");

		//only Databytes (first one is the Address)
		//+1 for the Xor //+1 for End of Data
		/*int Data_len = datac - 1 + 2;
		uint8_t Address[1] = { *data };
		uint8_t Stop[1] = { 255 };
		data++;
		printf("Databytes : %i  \n", Data_len);
		uint8_t transmit[Data_len];
		*/
		
#ifdef RASPBERRY
		set_GPIO_transmit();
		printf("Set RS485- BUS to Transmission\n");
#endif
/*
		for (int i = 1; i < Data_len + 1; i++)
		{
			transmit[i - 1] = *data;

			data++;
		}
		//setSPACE(fd);
		//setMARK(fd, Address[0]);
		int n = write(fd, Address, 1);
		if (n < 0)
		{
			perror("write() of Address failed!\n");
			return -1;
		}
		else
		{
			printf("write address %i\n", Address[0]);
		}
*/
		//setMARK();
		printf("write data: %d", datac);
		while(*data){
			//setSPACE(fd, transmit[i]);
			//uint8_t tmp[1] = { transmit[i] };
			uint8_t n = write(fd, data, 1);
			if (n < 0)
			{
				perror("write() of Data failed!\n");
				return -1;
			}
			else
			{
				
				//for (uint8_t i = 0; i < Data_len; i++)
				printf(" \"%c\",", *data);
			}
			data ++;
		}
		printf(" \n");

		//setMARK(fd);//
		//setSPACE(fd);

		char end[2] = {Xor, '\0' };
		uint8_t n = write(fd, end, 2);
		if (n < 0)
		{
			perror("write() of Xor and End failed!\n");
			return -1;
		}
		else
			printf("write Xor: %u and End \n", Xor);


		close(fd);

		printf("\n\nTransmission complete! \nThanks for using HausCom3-ASCII.\n");
		printf("If you need help, please insert \"-h\" as argument.\n\n\n");
		

		return 0;
	}
	else
		return -1;
}
