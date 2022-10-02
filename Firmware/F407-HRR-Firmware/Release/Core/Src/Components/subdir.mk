################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Src/Components/Dynamixel.cpp \
../Core/Src/Components/PWMServo.cpp \
../Core/Src/Components/Robot.cpp \
../Core/Src/Components/SerialDebug.cpp \
../Core/Src/Components/Start.cpp 

OBJS += \
./Core/Src/Components/Dynamixel.o \
./Core/Src/Components/PWMServo.o \
./Core/Src/Components/Robot.o \
./Core/Src/Components/SerialDebug.o \
./Core/Src/Components/Start.o 

CPP_DEPS += \
./Core/Src/Components/Dynamixel.d \
./Core/Src/Components/PWMServo.d \
./Core/Src/Components/Robot.d \
./Core/Src/Components/SerialDebug.d \
./Core/Src/Components/Start.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Components/%.o Core/Src/Components/%.su: ../Core/Src/Components/%.cpp Core/Src/Components/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Components

clean-Core-2f-Src-2f-Components:
	-$(RM) ./Core/Src/Components/Dynamixel.d ./Core/Src/Components/Dynamixel.o ./Core/Src/Components/Dynamixel.su ./Core/Src/Components/PWMServo.d ./Core/Src/Components/PWMServo.o ./Core/Src/Components/PWMServo.su ./Core/Src/Components/Robot.d ./Core/Src/Components/Robot.o ./Core/Src/Components/Robot.su ./Core/Src/Components/SerialDebug.d ./Core/Src/Components/SerialDebug.o ./Core/Src/Components/SerialDebug.su ./Core/Src/Components/Start.d ./Core/Src/Components/Start.o ./Core/Src/Components/Start.su

.PHONY: clean-Core-2f-Src-2f-Components

