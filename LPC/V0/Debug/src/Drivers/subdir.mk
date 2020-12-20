################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Drivers/DR_GPIO.c \
../src/Drivers/DR_PLL.c \
../src/Drivers/DR_Pinsel.c \
../src/Drivers/DR_Systick.c 

OBJS += \
./src/Drivers/DR_GPIO.o \
./src/Drivers/DR_PLL.o \
./src/Drivers/DR_Pinsel.o \
./src/Drivers/DR_Systick.o 

C_DEPS += \
./src/Drivers/DR_GPIO.d \
./src/Drivers/DR_PLL.d \
./src/Drivers/DR_Pinsel.d \
./src/Drivers/DR_Systick.d 


# Each subdirectory must supply rules for building sources it contributes
src/Drivers/%.o: ../src/Drivers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"/home/damian/Desktop/Info2/TPI/LPC/V0/inc" -I"/home/damian/Desktop/Info2/TPI/LPC/V0/inc/Drivers" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m3 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


