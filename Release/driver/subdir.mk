################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../driver/CONFIG.c \
../driver/DR_Systick.c \
../driver/GPIO.c \
../driver/Inic.c \
../driver/Oscilador.c \
../driver/PWM_Salidas.c \
../driver/adc.c \
../driver/extint.c 

OBJS += \
./driver/CONFIG.o \
./driver/DR_Systick.o \
./driver/GPIO.o \
./driver/Inic.o \
./driver/Oscilador.o \
./driver/PWM_Salidas.o \
./driver/adc.o \
./driver/extint.o 

C_DEPS += \
./driver/CONFIG.d \
./driver/DR_Systick.d \
./driver/GPIO.d \
./driver/Inic.d \
./driver/Oscilador.d \
./driver/PWM_Salidas.d \
./driver/adc.d \
./driver/extint.d 


# Each subdirectory must supply rules for building sources it contributes
driver/%.o: ../driver/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DNDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"C:\Users\fedes\Desktop\servomotorpendrive3-LPC-1769-main\inc" -Os -fno-common -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m3 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


