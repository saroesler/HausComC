################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ConfFile.c \
../HausComC.c \
../Port_config.c \
../Raspberry_GPIO.c \
../Receive.c \
../Transmit.c 

OBJS += \
./ConfFile.o \
./HausComC.o \
./Port_config.o \
./Raspberry_GPIO.o \
./Receive.o \
./Transmit.o 

C_DEPS += \
./ConfFile.d \
./HausComC.d \
./Port_config.d \
./Raspberry_GPIO.d \
./Receive.d \
./Transmit.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


