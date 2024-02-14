################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../APP/TEST/rcc_test.c 

OBJS += \
./APP/TEST/rcc_test.o 

C_DEPS += \
./APP/TEST/rcc_test.d 


# Each subdirectory must supply rules for building sources it contributes
APP/TEST/%.o APP/TEST/%.su APP/TEST/%.cyclo: ../APP/TEST/%.c APP/TEST/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F401CCUx -DSTM32 -DSTM32F4 -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-APP-2f-TEST

clean-APP-2f-TEST:
	-$(RM) ./APP/TEST/rcc_test.cyclo ./APP/TEST/rcc_test.d ./APP/TEST/rcc_test.o ./APP/TEST/rcc_test.su

.PHONY: clean-APP-2f-TEST

