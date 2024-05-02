################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/COMM/LIN_SLAVE/LIN_Slave.c \
../Src/COMM/LIN_SLAVE/LIN_SlaveAppData.c \
../Src/COMM/LIN_SLAVE/LIN_Slave_config.c 

OBJS += \
./Src/COMM/LIN_SLAVE/LIN_Slave.o \
./Src/COMM/LIN_SLAVE/LIN_SlaveAppData.o \
./Src/COMM/LIN_SLAVE/LIN_Slave_config.o 

C_DEPS += \
./Src/COMM/LIN_SLAVE/LIN_Slave.d \
./Src/COMM/LIN_SLAVE/LIN_SlaveAppData.d \
./Src/COMM/LIN_SLAVE/LIN_Slave_config.d 


# Each subdirectory must supply rules for building sources it contributes
Src/COMM/LIN_SLAVE/%.o Src/COMM/LIN_SLAVE/%.su Src/COMM/LIN_SLAVE/%.cyclo: ../Src/COMM/LIN_SLAVE/%.c Src/COMM/LIN_SLAVE/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F401CCUx -DSTM32 -DSTM32F4 -c -I../Inc -I"D:/ITI/Eng_Tourkey/stmCubeWorkSpace/ITI_ARM/stm32f401Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-COMM-2f-LIN_SLAVE

clean-Src-2f-COMM-2f-LIN_SLAVE:
	-$(RM) ./Src/COMM/LIN_SLAVE/LIN_Slave.cyclo ./Src/COMM/LIN_SLAVE/LIN_Slave.d ./Src/COMM/LIN_SLAVE/LIN_Slave.o ./Src/COMM/LIN_SLAVE/LIN_Slave.su ./Src/COMM/LIN_SLAVE/LIN_SlaveAppData.cyclo ./Src/COMM/LIN_SLAVE/LIN_SlaveAppData.d ./Src/COMM/LIN_SLAVE/LIN_SlaveAppData.o ./Src/COMM/LIN_SLAVE/LIN_SlaveAppData.su ./Src/COMM/LIN_SLAVE/LIN_Slave_config.cyclo ./Src/COMM/LIN_SLAVE/LIN_Slave_config.d ./Src/COMM/LIN_SLAVE/LIN_Slave_config.o ./Src/COMM/LIN_SLAVE/LIN_Slave_config.su

.PHONY: clean-Src-2f-COMM-2f-LIN_SLAVE

