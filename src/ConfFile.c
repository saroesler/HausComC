/*
 * ConfFile.c
 *
 *  Created on: 14.07.2014
 *      Author: sascha
 */
#include "HausComC.h"

char* getPort(char* Port)
{
	FILE *datei;
	char text[100 + 1];
	datei = fopen(CONF_FILE, "r");

	if (datei != NULL)
	{
		//read file
		printf("read Port by file\n");
		fscanf(datei, "%100c", text);
		/* String muss mit Nullbyte abgeschlossen sein */
		text[100] = '\0';

		//search for Port
		char *temp = strstr(text, "PORT=");
		if (temp)
		{
			int i = 0;
			char *ptr;

			//select word after Port
			ptr = strtok(temp, "=");
			ptr = strtok(NULL, "=");

			strcpy(Port, ptr);

			//look for ";" and delete it
			while (Port[i] != ';')
			{
				i++;
			}
			Port[i] = '\0';
		}
		else
		{
			fclose(datei);
			perror("Can not find \"PORT\"- Argument in file");
			return NULL;
		}
	}
	else
	{
		perror("Can not find config- file \"HausCom.conf\"");
		return NULL;
	}
	return Port;
}

char* getMyAddress(char* Address)
{
	FILE *datei;
	char text[100 + 1];
	datei = fopen(CONF_FILE, "r");

	printf("read Address in file\n");

	if (datei != NULL)
	{
		//read file
		fscanf(datei, "%100c", text);
		/* String muss mit Nullbyte abgeschlossen sein */
		text[100] = '\0';

		//search for Port
		char *temp = strstr(text, "ADDRESS=");
		if (temp)
		{
			printf("read Address\n");
			char *ptr;

			//select word after Port
			ptr = strtok(temp, "=");
			ptr = strtok(NULL, "=");
			strncpy(Address, ptr, 3);

			fclose(datei);
		}
		else
		{
			fclose(datei);
			perror("Can not find \"ADDRESS\"- Argument in file");
			return NULL;
		}
	}
	else
	{
		perror("Can not find config- file \"HausCom.conf\"");
		return NULL;
	}
	return Address;
}
