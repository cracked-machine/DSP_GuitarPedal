################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/Device/ST/STM32G4xx/Source/Templates/system_stm32g4xx.c 

OBJS += \
./Drivers/CMSIS/Device/ST/STM32G4xx/Source/Templates/system_stm32g4xx.o 

C_DEPS += \
./Drivers/CMSIS/Device/ST/STM32G4xx/Source/Templates/system_stm32g4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/Device/ST/STM32G4xx/Source/Templates/system_stm32g4xx.o: ../Drivers/CMSIS/Device/ST/STM32G4xx/Source/Templates/system_stm32g4xx.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32G474xx -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I../Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I"/home/chris/DSP_GuitarPedal/G474_RTT/RTT" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/CMSIS/Device/ST/STM32G4xx/Source/Templates/system_stm32g4xx.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

