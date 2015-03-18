# HausComC

This is a program written in c to manage a uart communication with one master an a lot of slaves. You can use this software for "KolbeHomeSystem", you can find here: https://github.com/cmfcmf/KolbeHomeSystem
The protocol is published here:https://github.com/cmfcmf/KolbeHomeSystem/blob/master/Kolbe_Protokoll.odt

To install the software you can use the install- script https://github.com/sarom5/HausComC/blob/master/src/Release/HausCom_install.sh
After installation you start the prgram by insert "HausCom" on your command.

This script creates everything you need. It compiles the software on the computer, you want to use.
If you want to use a RS485 Bus, sending and reseiving by the same wires, you can set the GPIO- Pin here: https://github.com/sarom5/HausComC/blob/master/src/Raspberry_GPIO.c
If you use a Raspberry Pi, you can use this software, without changing the "HausComC.h". If you want to use an computer without GPIO pins, you have to delete the Raspberry- define here (you commentate the line by a "//"): https://github.com/sarom5/HausComC/blob/master/src/HausComC.h#L27

If you want to get every sign, your computer reseive, you can insert a "-d" as argument. It will not test the address or any stop signs.

Good Luck!

If you want to simulate a program, you find a debug- Version as an other Repository.
