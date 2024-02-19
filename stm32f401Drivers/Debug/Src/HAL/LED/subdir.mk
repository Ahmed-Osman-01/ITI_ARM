################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/HAL/LED/LED.c \
../Src/HAL/LED/LED_config.c 

OBJS += \
./Src/HAL/LED/LED.o \
./Src/HAL/LED/LED_config.o 

C_DEPS += \
./Src/HAL/LED/LED.d \
./Src/HAL/LED/LED_config.d 


# Each subdirectory must supply rules for building sources it contributes
Src/HAL/LED/%.o Src/HAL/LED/%.su Src/HAL/LED/%.cyclo: ../Src/HAL/LED/%.c Src/HAL/LED/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F401CCUx -DSTM32 -DSTM32F4 -c -I../Inc -I"D:/ITI/Eng_Tourkey/stmCubeWorkSpace/ITI_ARM/stm32f401Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-HAL-2f-LED

clean-Src-2f-HAL-2f-LED:
	-$(RM) ./Src/HAL/LED/LED.cyclo ./Src/HAL/LED/LED.d ./Src/HAL/LED/LED.o ./Src/HAL/LED/LED.su ./Src/HAL/LED/LED_config.cyclo ./Src/HAL/LED/LED_config.d ./Src/HAL/LED/LED_config.o ./Src/HAL/LED/LED_config.su

.PHONY: clean-Src-2f-HAL-2f-LED

