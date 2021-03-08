################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../driver/CONFIG.c \
../driver/GPIO.c \
../driver/Inicializacion.c \
../driver/PWM_Salidas.c \
../driver/Teclado.c \
../driver/adc.c \
../driver/extint.c \
../driver/handler.c 

OBJS += \
./driver/CONFIG.o \
./driver/GPIO.o \
./driver/Inicializacion.o \
./driver/PWM_Salidas.o \
./driver/Teclado.o \
./driver/adc.o \
./driver/extint.o \
./driver/handler.o 

C_DEPS += \
./driver/CONFIG.d \
./driver/GPIO.d \
./driver/Inicializacion.d \
./driver/PWM_Salidas.d \
./driver/Teclado.d \
./driver/adc.d \
./driver/extint.d \
./driver/handler.d 


# Each subdirectory must supply rules for building sources it contributes
driver/%.o: ../driver/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"C:\Users\cat21\Desktop\GitHub\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m3 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


