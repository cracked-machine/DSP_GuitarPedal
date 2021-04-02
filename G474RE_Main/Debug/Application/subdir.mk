################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/redirect_write.c 

CPP_SRCS += \
../Application/appmain.cpp 

C_DEPS += \
./Application/redirect_write.d 

OBJS += \
./Application/appmain.o \
./Application/redirect_write.o 

CPP_DEPS += \
./Application/appmain.d 


# Each subdirectory must supply rules for building sources it contributes
Application/appmain.o: ../Application/appmain.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32G474xx -DDEBUG -c -I../Core/Inc -I"/home/chris/DSP_GuitarPedal/G474_CppUTest/Inc" -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I"/home/chris/DSP_GuitarPedal/G474RE_Main/CppUTests" -I"/home/chris/DSP_GuitarPedal/G474RE_Main/Application" -I"/home/chris/DSP_GuitarPedal/G474_RTT/RTT" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Application/appmain.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/redirect_write.o: ../Application/redirect_write.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32G474xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I"/home/chris/DSP_GuitarPedal/G474RE_Main/CppUTests" -I"/home/chris/DSP_GuitarPedal/G474RE_Main/Application" -I"/home/chris/DSP_GuitarPedal/G474_RTT/RTT" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Application/redirect_write.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

