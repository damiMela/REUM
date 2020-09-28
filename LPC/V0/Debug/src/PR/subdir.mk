################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/PR/PR_Timers.c 

OBJS += \
./src/PR/PR_Timers.o 

C_DEPS += \
./src/PR/PR_Timers.d 


# Each subdirectory must supply rules for building sources it contributes
src/PR/%.o: ../src/PR/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"/home/damian/Desktop/Info2/TPI/LPC/V0/inc" -I"/home/damian/Desktop/Info2/TPI/LPC/V0/inc/PR" -I"/home/damian/Desktop/Info2/TPI/LPC/V0/inc/DR" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m3 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


