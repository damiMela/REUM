################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/PR/PR_Botones.c \
../src/PR/PR_Motores.c \
../src/PR/PR_Relays.c \
../src/PR/PR_Serial.c \
../src/PR/PR_Timers.c 

OBJS += \
./src/PR/PR_Botones.o \
./src/PR/PR_Motores.o \
./src/PR/PR_Relays.o \
./src/PR/PR_Serial.o \
./src/PR/PR_Timers.o 

C_DEPS += \
./src/PR/PR_Botones.d \
./src/PR/PR_Motores.d \
./src/PR/PR_Relays.d \
./src/PR/PR_Serial.d \
./src/PR/PR_Timers.d 


# Each subdirectory must supply rules for building sources it contributes
src/PR/%.o: ../src/PR/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"D:\Damian\Archivos\UTN\info II\REUM\LPC\V0\inc" -I"D:\Damian\Archivos\UTN\info II\REUM\LPC\V0\inc\PR" -I"D:\Damian\Archivos\UTN\info II\REUM\LPC\V0\inc\DR" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m3 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


