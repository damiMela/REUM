################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/DR/DR_ADC.c \
../src/DR/DR_Botones.c \
../src/DR/DR_ExtInt.c \
../src/DR/DR_GPIO.c \
../src/DR/DR_I2C.c \
../src/DR/DR_LCD.c \
../src/DR/DR_PLL.c \
../src/DR/DR_PWM.c \
../src/DR/DR_Pinsel.c \
../src/DR/DR_Serial.c \
../src/DR/DR_Systick.c \
../src/DR/DR_Timer0.c 

OBJS += \
./src/DR/DR_ADC.o \
./src/DR/DR_Botones.o \
./src/DR/DR_ExtInt.o \
./src/DR/DR_GPIO.o \
./src/DR/DR_I2C.o \
./src/DR/DR_LCD.o \
./src/DR/DR_PLL.o \
./src/DR/DR_PWM.o \
./src/DR/DR_Pinsel.o \
./src/DR/DR_Serial.o \
./src/DR/DR_Systick.o \
./src/DR/DR_Timer0.o 

C_DEPS += \
./src/DR/DR_ADC.d \
./src/DR/DR_Botones.d \
./src/DR/DR_ExtInt.d \
./src/DR/DR_GPIO.d \
./src/DR/DR_I2C.d \
./src/DR/DR_LCD.d \
./src/DR/DR_PLL.d \
./src/DR/DR_PWM.d \
./src/DR/DR_Pinsel.d \
./src/DR/DR_Serial.d \
./src/DR/DR_Systick.d \
./src/DR/DR_Timer0.d 


# Each subdirectory must supply rules for building sources it contributes
src/DR/%.o: ../src/DR/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"/home/damian/git/TPI/LPC/V0/inc" -I"/home/damian/git/TPI/LPC/V0/inc/PR" -I"/home/damian/git/TPI/LPC/V0/inc/DR" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m3 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


