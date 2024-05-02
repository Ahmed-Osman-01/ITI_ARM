################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/COMM/LIN_MASTER/LIN_Master.c \
../Src/COMM/LIN_MASTER/LIN_MasterAppData.c \
../Src/COMM/LIN_MASTER/LIN_config.c 

OBJS += \
./Src/COMM/LIN_MASTER/LIN_Master.o \
./Src/COMM/LIN_MASTER/LIN_MasterAppData.o \
./Src/COMM/LIN_MASTER/LIN_config.o 

C_DEPS += \
./Src/COMM/LIN_MASTER/LIN_Master.d \
./Src/COMM/LIN_MASTER/LIN_MasterAppData.d \
./Src/COMM/LIN_MASTER/LIN_config.d 


# Each subdirectory must supply rules for building sources it contributes
Src/COMM/LIN_MASTER/%.o Src/COMM/LIN_MASTER/%.su Src/COMM/LIN_MASTER/%.cyclo: ../Src/COMM/LIN_MASTER/%.c Src/COMM/LIN_MASTER/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F401CCUx -DSTM32 -DSTM32F4 -c -I../Inc -I"D:/ITI/Eng_Tourkey/stmCubeWorkSpace/ITI_ARM/stm32f401Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-COMM-2f-LIN_MASTER

clean-Src-2f-COMM-2f-LIN_MASTER:
	-$(RM) ./Src/COMM/LIN_MASTER/LIN_Master.cyclo ./Src/COMM/LIN_MASTER/LIN_Master.d ./Src/COMM/LIN_MASTER/LIN_Master.o ./Src/COMM/LIN_MASTER/LIN_Master.su ./Src/COMM/LIN_MASTER/LIN_MasterAppData.cyclo ./Src/COMM/LIN_MASTER/LIN_MasterAppData.d ./Src/COMM/LIN_MASTER/LIN_MasterAppData.o ./Src/COMM/LIN_MASTER/LIN_MasterAppData.su ./Src/COMM/LIN_MASTER/LIN_config.cyclo ./Src/COMM/LIN_MASTER/LIN_config.d ./Src/COMM/LIN_MASTER/LIN_config.o ./Src/COMM/LIN_MASTER/LIN_config.su

.PHONY: clean-Src-2f-COMM-2f-LIN_MASTER

