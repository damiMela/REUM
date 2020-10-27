################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/DR/DR_ADC.c \
../src/DR/DR_GPIO.c \
../src/DR/DR_PLL.c \
../src/DR/DR_PWM.c \
../src/DR/DR_Pinsel.c \
../src/DR/DR_Systick.c 

OBJS += \
./src/DR/DR_ADC.o \
./src/DR/DR_GPIO.o \
./src/DR/DR_PLL.o \
./src/DR/DR_PWM.o \
./src/DR/DR_Pinsel.o \
./src/DR/DR_Systick.o 

C_DEPS += \
./src/DR/DR_ADC.d \
./src/DR/DR_GPIO.d \
./src/DR/DR_PLL.d \
./src/DR/DR_PWM.d \
./src/DR/DR_Pinsel.d \
./src/DR/DR_Systick.d 


# Each subdirectory must supply rules for building sources it contributes
src/DR/%.o: ../src/DR/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"/home/damian/Desktop/Info2/TPI/LPC/V0/inc" -I"/home/damian/Desktop/Info2/TPI/LPC/V0/inc/PR" -I"/home/damian/Desktop/Info2/TPI/LPC/V0/inc/DR" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m3 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


