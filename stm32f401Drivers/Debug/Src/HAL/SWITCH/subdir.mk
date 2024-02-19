################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/HAL/SWITCH/SWITCH.c \
../Src/HAL/SWITCH/SWITCH_config.c 

OBJS += \
./Src/HAL/SWITCH/SWITCH.o \
./Src/HAL/SWITCH/SWITCH_config.o 

C_DEPS += \
./Src/HAL/SWITCH/SWITCH.d \
./Src/HAL/SWITCH/SWITCH_config.d 


# Each subdirectory must supply rules for building sources it contributes
Src/HAL/SWITCH/%.o Src/HAL/SWITCH/%.su Src/HAL/SWITCH/%.cyclo: ../Src/HAL/SWITCH/%.c Src/HAL/SWITCH/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F401CCUx -DSTM32 -DSTM32F4 -c -I../Inc -I"D:/ITI/Eng_Tourkey/stmCubeWorkSpace/ITI_ARM/stm32f401Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-HAL-2f-SWITCH

clean-Src-2f-HAL-2f-SWITCH:
	-$(RM) ./Src/HAL/SWITCH/SWITCH.cyclo ./Src/HAL/SWITCH/SWITCH.d ./Src/HAL/SWITCH/SWITCH.o ./Src/HAL/SWITCH/SWITCH.su ./Src/HAL/SWITCH/SWITCH_config.cyclo ./Src/HAL/SWITCH/SWITCH_config.d ./Src/HAL/SWITCH/SWITCH_config.o ./Src/HAL/SWITCH/SWITCH_config.su

.PHONY: clean-Src-2f-HAL-2f-SWITCH

