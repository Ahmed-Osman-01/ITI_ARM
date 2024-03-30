################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/HAL/LCD/LCD.c \
../Src/HAL/LCD/LCD_config.c 

OBJS += \
./Src/HAL/LCD/LCD.o \
./Src/HAL/LCD/LCD_config.o 

C_DEPS += \
./Src/HAL/LCD/LCD.d \
./Src/HAL/LCD/LCD_config.d 


# Each subdirectory must supply rules for building sources it contributes
Src/HAL/LCD/%.o Src/HAL/LCD/%.su Src/HAL/LCD/%.cyclo: ../Src/HAL/LCD/%.c Src/HAL/LCD/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F401CCUx -DSTM32 -DSTM32F4 -c -I../Inc -I"D:/ITI/Eng_Tourkey/stmCubeWorkSpace/ITI_ARM/stm32f401Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-HAL-2f-LCD

clean-Src-2f-HAL-2f-LCD:
	-$(RM) ./Src/HAL/LCD/LCD.cyclo ./Src/HAL/LCD/LCD.d ./Src/HAL/LCD/LCD.o ./Src/HAL/LCD/LCD.su ./Src/HAL/LCD/LCD_config.cyclo ./Src/HAL/LCD/LCD_config.d ./Src/HAL/LCD/LCD_config.o ./Src/HAL/LCD/LCD_config.su

.PHONY: clean-Src-2f-HAL-2f-LCD

