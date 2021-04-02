################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../RTT/SEGGER_RTT.c \
../RTT/SEGGER_RTT_printf.c 

S_UPPER_SRCS += \
../RTT/SEGGER_RTT_ASM_ARMv7M.S 

OBJS += \
./RTT/SEGGER_RTT.o \
./RTT/SEGGER_RTT_ASM_ARMv7M.o \
./RTT/SEGGER_RTT_printf.o 

S_UPPER_DEPS += \
./RTT/SEGGER_RTT_ASM_ARMv7M.d 

C_DEPS += \
./RTT/SEGGER_RTT.d \
./RTT/SEGGER_RTT_printf.d 


# Each subdirectory must supply rules for building sources it contributes
RTT/SEGGER_RTT.o: ../RTT/SEGGER_RTT.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32G474xx -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I../Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I"/home/chris/DSP_GuitarPedal/G474_RTT/RTT" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"RTT/SEGGER_RTT.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
RTT/SEGGER_RTT_ASM_ARMv7M.o: ../RTT/SEGGER_RTT_ASM_ARMv7M.S
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -c -I"/home/chris/DSP_GuitarPedal/G474_RTT/RTT" -x assembler-with-cpp -MMD -MP -MF"RTT/SEGGER_RTT_ASM_ARMv7M.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"
RTT/SEGGER_RTT_printf.o: ../RTT/SEGGER_RTT_printf.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32G474xx -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I../Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I"/home/chris/DSP_GuitarPedal/G474_RTT/RTT" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"RTT/SEGGER_RTT_printf.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

