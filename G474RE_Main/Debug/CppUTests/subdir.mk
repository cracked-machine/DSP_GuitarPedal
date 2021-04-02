################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CppUTests/cpputests_buffer_allignment.cpp \
../CppUTests/cpputests_dsp_buffer.cpp \
../CppUTests/cpputests_main.cpp 

OBJS += \
./CppUTests/cpputests_buffer_allignment.o \
./CppUTests/cpputests_dsp_buffer.o \
./CppUTests/cpputests_main.o 

CPP_DEPS += \
./CppUTests/cpputests_buffer_allignment.d \
./CppUTests/cpputests_dsp_buffer.d \
./CppUTests/cpputests_main.d 


# Each subdirectory must supply rules for building sources it contributes
CppUTests/cpputests_buffer_allignment.o: ../CppUTests/cpputests_buffer_allignment.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32G474xx -DDEBUG -c -I../Core/Inc -I"/home/chris/DSP_GuitarPedal/G474_CppUTest/Inc" -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I"/home/chris/DSP_GuitarPedal/G474RE_Main/CppUTests" -I"/home/chris/DSP_GuitarPedal/G474RE_Main/Application" -I"/home/chris/DSP_GuitarPedal/G474_RTT/RTT" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"CppUTests/cpputests_buffer_allignment.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
CppUTests/cpputests_dsp_buffer.o: ../CppUTests/cpputests_dsp_buffer.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32G474xx -DDEBUG -c -I../Core/Inc -I"/home/chris/DSP_GuitarPedal/G474_CppUTest/Inc" -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I"/home/chris/DSP_GuitarPedal/G474RE_Main/CppUTests" -I"/home/chris/DSP_GuitarPedal/G474RE_Main/Application" -I"/home/chris/DSP_GuitarPedal/G474_RTT/RTT" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"CppUTests/cpputests_dsp_buffer.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
CppUTests/cpputests_main.o: ../CppUTests/cpputests_main.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32G474xx -DDEBUG -c -I../Core/Inc -I"/home/chris/DSP_GuitarPedal/G474_CppUTest/Inc" -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I"/home/chris/DSP_GuitarPedal/G474RE_Main/CppUTests" -I"/home/chris/DSP_GuitarPedal/G474RE_Main/Application" -I"/home/chris/DSP_GuitarPedal/G474_RTT/RTT" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"CppUTests/cpputests_main.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

