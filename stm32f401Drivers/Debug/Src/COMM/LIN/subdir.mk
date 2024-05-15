################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/COMM/LIN/LIN_HW.c \
../Src/COMM/LIN/LIN_Master.c \
../Src/COMM/LIN/LIN_Slave.c 

OBJS += \
./Src/COMM/LIN/LIN_HW.o \
./Src/COMM/LIN/LIN_Master.o \
./Src/COMM/LIN/LIN_Slave.o 

C_DEPS += \
./Src/COMM/LIN/LIN_HW.d \
./Src/COMM/LIN/LIN_Master.d \
./Src/COMM/LIN/LIN_Slave.d 


# Each subdirectory must supply rules for building sources it contributes
Src/COMM/LIN/%.o Src/COMM/LIN/%.su Src/COMM/LIN/%.cyclo: ../Src/COMM/LIN/%.c Src/COMM/LIN/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F401CCUx -DSTM32 -DSTM32F4 -c -I../Inc -I"D:/ITI/Eng_Tourkey/stmCubeWorkSpace/ITI_ARM/stm32f401Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-COMM-2f-LIN

clean-Src-2f-COMM-2f-LIN:
	-$(RM) ./Src/COMM/LIN/LIN_HW.cyclo ./Src/COMM/LIN/LIN_HW.d ./Src/COMM/LIN/LIN_HW.o ./Src/COMM/LIN/LIN_HW.su ./Src/COMM/LIN/LIN_Master.cyclo ./Src/COMM/LIN/LIN_Master.d ./Src/COMM/LIN/LIN_Master.o ./Src/COMM/LIN/LIN_Master.su ./Src/COMM/LIN/LIN_Slave.cyclo ./Src/COMM/LIN/LIN_Slave.d ./Src/COMM/LIN/LIN_Slave.o ./Src/COMM/LIN/LIN_Slave.su

.PHONY: clean-Src-2f-COMM-2f-LIN

