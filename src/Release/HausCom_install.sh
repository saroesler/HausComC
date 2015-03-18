#!/bin/bash

echo "This script install HausCom, a program help with the UART connection"
echo "compiling HausCom"

make clean
make

#copy the program into the right dir
echo "copying the program to the execution dir"
echo "Please insert your root keypass:"
sudo cp "HausComC" /usr/local/bin/HausCom
sudo chmod 777 /usr/local/bin/HausCom
echo "creating a link to the general bin- directory. This is necessary using HausCom via a startup program."
sudo ln -s /usr/local/bin/HausCom /usr/bin/HausCom

#create the conf file
echo "creating the config file in \"/usr/local/etc/HausCom/HausCom.conf\""
echo "Please edit it by the root. The standart configuration is:"
echo "UART Port:  PORT=/dev/ttyAMA0;"
echo "The HausCom Address:  ADDRESS=0;"
cd /usr/local/etc
sudo mkdir HausCom
sudo touch HausCom/HausCom.conf
sudo chmod 666 HausCom/HausCom.conf
sudo echo "PORT=/dev/ttyAMA0;"  >> /usr/local/etc/HausCom/HausCom.conf
sudo echo "ADDRESS=0;"  >> /usr/local/etc/HausCom/HausCom.conf
sudo chmod 644 HausCom/HausCom.conf

#create file for the output
echo "create a file in \"usr/local/var/HausComI\" to get the received message"
cd /usr/local
sudo mkdir var
sudo touch /usr/local/var/HausComI
sudo chmod 666 /usr/local/var/HausComI

#create file for the output
echo "installation complete. Thanks for using HausCom!"
