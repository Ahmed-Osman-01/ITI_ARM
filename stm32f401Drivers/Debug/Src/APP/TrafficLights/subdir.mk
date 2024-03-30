################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/APP/TrafficLights/blinkingLed.c \
../Src/APP/TrafficLights/main.c \
../Src/APP/TrafficLights/traffic.c 

OBJS += \
./Src/APP/TrafficLights/blinkingLed.o \
./Src/APP/TrafficLights/main.o \
./Src/APP/TrafficLights/traffic.o 

C_DEPS += \
./Src/APP/TrafficLights/blinkingLed.d \
./Src/APP/TrafficLights/main.d \
./Src/APP/TrafficLights/traffic.d 


# Each subdirectory must supply rules for building sources it contributes
Src/APP/TrafficLights/%.o Src/APP/TrafficLights/%.su Src/APP/TrafficLights/%.cyclo: ../Src/APP/TrafficLights/%.c Src/APP/TrafficLights/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F401CCUx -DSTM32 -DSTM32F4 -c -I../Inc -I"D:/ITI/Eng_Tourkey/stmCubeWorkSpace/ITI_ARM/stm32f401Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-APP-2f-TrafficLights

clean-Src-2f-APP-2f-TrafficLights:
	-$(RM) ./Src/APP/TrafficLights/blinkingLed.cyclo ./Src/APP/TrafficLights/blinkingLed.d ./Src/APP/TrafficLights/blinkingLed.o ./Src/APP/TrafficLights/blinkingLed.su ./Src/APP/TrafficLights/main.cyclo ./Src/APP/TrafficLights/main.d ./Src/APP/TrafficLights/main.o ./Src/APP/TrafficLights/main.su ./Src/APP/TrafficLights/traffic.cyclo ./Src/APP/TrafficLights/traffic.d ./Src/APP/TrafficLights/traffic.o ./Src/APP/TrafficLights/traffic.su

.PHONY: clean-Src-2f-APP-2f-TrafficLights

