################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/APP/TEST/gpio_test.c \
../Src/APP/TEST/led_switch_test.c \
../Src/APP/TEST/rcc_test.c 

OBJS += \
./Src/APP/TEST/gpio_test.o \
./Src/APP/TEST/led_switch_test.o \
./Src/APP/TEST/rcc_test.o 

C_DEPS += \
./Src/APP/TEST/gpio_test.d \
./Src/APP/TEST/led_switch_test.d \
./Src/APP/TEST/rcc_test.d 


# Each subdirectory must supply rules for building sources it contributes
Src/APP/TEST/%.o Src/APP/TEST/%.su Src/APP/TEST/%.cyclo: ../Src/APP/TEST/%.c Src/APP/TEST/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F401CCUx -DSTM32 -DSTM32F4 -c -I../Inc -I"D:/ITI/Eng_Tourkey/stmCubeWorkSpace/ITI_ARM/stm32f401Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-APP-2f-TEST

clean-Src-2f-APP-2f-TEST:
	-$(RM) ./Src/APP/TEST/gpio_test.cyclo ./Src/APP/TEST/gpio_test.d ./Src/APP/TEST/gpio_test.o ./Src/APP/TEST/gpio_test.su ./Src/APP/TEST/led_switch_test.cyclo ./Src/APP/TEST/led_switch_test.d ./Src/APP/TEST/led_switch_test.o ./Src/APP/TEST/led_switch_test.su ./Src/APP/TEST/rcc_test.cyclo ./Src/APP/TEST/rcc_test.d ./Src/APP/TEST/rcc_test.o ./Src/APP/TEST/rcc_test.su

.PHONY: clean-Src-2f-APP-2f-TEST

