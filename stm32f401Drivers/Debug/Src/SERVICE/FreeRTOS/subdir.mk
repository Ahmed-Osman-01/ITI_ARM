################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/SERVICE/FreeRTOS/croutine.c \
../Src/SERVICE/FreeRTOS/event_groups.c \
../Src/SERVICE/FreeRTOS/heap_1.c \
../Src/SERVICE/FreeRTOS/list.c \
../Src/SERVICE/FreeRTOS/port.c \
../Src/SERVICE/FreeRTOS/queue.c \
../Src/SERVICE/FreeRTOS/stream_buffer.c \
../Src/SERVICE/FreeRTOS/tasks.c \
../Src/SERVICE/FreeRTOS/timers.c 

OBJS += \
./Src/SERVICE/FreeRTOS/croutine.o \
./Src/SERVICE/FreeRTOS/event_groups.o \
./Src/SERVICE/FreeRTOS/heap_1.o \
./Src/SERVICE/FreeRTOS/list.o \
./Src/SERVICE/FreeRTOS/port.o \
./Src/SERVICE/FreeRTOS/queue.o \
./Src/SERVICE/FreeRTOS/stream_buffer.o \
./Src/SERVICE/FreeRTOS/tasks.o \
./Src/SERVICE/FreeRTOS/timers.o 

C_DEPS += \
./Src/SERVICE/FreeRTOS/croutine.d \
./Src/SERVICE/FreeRTOS/event_groups.d \
./Src/SERVICE/FreeRTOS/heap_1.d \
./Src/SERVICE/FreeRTOS/list.d \
./Src/SERVICE/FreeRTOS/port.d \
./Src/SERVICE/FreeRTOS/queue.d \
./Src/SERVICE/FreeRTOS/stream_buffer.d \
./Src/SERVICE/FreeRTOS/tasks.d \
./Src/SERVICE/FreeRTOS/timers.d 


# Each subdirectory must supply rules for building sources it contributes
Src/SERVICE/FreeRTOS/%.o Src/SERVICE/FreeRTOS/%.su Src/SERVICE/FreeRTOS/%.cyclo: ../Src/SERVICE/FreeRTOS/%.c Src/SERVICE/FreeRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F401CCUx -DSTM32 -DSTM32F4 -c -I../Inc -I"D:/ITI/Eng_Tourkey/stmCubeWorkSpace/ITI_ARM/stm32f401Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-SERVICE-2f-FreeRTOS

clean-Src-2f-SERVICE-2f-FreeRTOS:
	-$(RM) ./Src/SERVICE/FreeRTOS/croutine.cyclo ./Src/SERVICE/FreeRTOS/croutine.d ./Src/SERVICE/FreeRTOS/croutine.o ./Src/SERVICE/FreeRTOS/croutine.su ./Src/SERVICE/FreeRTOS/event_groups.cyclo ./Src/SERVICE/FreeRTOS/event_groups.d ./Src/SERVICE/FreeRTOS/event_groups.o ./Src/SERVICE/FreeRTOS/event_groups.su ./Src/SERVICE/FreeRTOS/heap_1.cyclo ./Src/SERVICE/FreeRTOS/heap_1.d ./Src/SERVICE/FreeRTOS/heap_1.o ./Src/SERVICE/FreeRTOS/heap_1.su ./Src/SERVICE/FreeRTOS/list.cyclo ./Src/SERVICE/FreeRTOS/list.d ./Src/SERVICE/FreeRTOS/list.o ./Src/SERVICE/FreeRTOS/list.su ./Src/SERVICE/FreeRTOS/port.cyclo ./Src/SERVICE/FreeRTOS/port.d ./Src/SERVICE/FreeRTOS/port.o ./Src/SERVICE/FreeRTOS/port.su ./Src/SERVICE/FreeRTOS/queue.cyclo ./Src/SERVICE/FreeRTOS/queue.d ./Src/SERVICE/FreeRTOS/queue.o ./Src/SERVICE/FreeRTOS/queue.su ./Src/SERVICE/FreeRTOS/stream_buffer.cyclo ./Src/SERVICE/FreeRTOS/stream_buffer.d ./Src/SERVICE/FreeRTOS/stream_buffer.o ./Src/SERVICE/FreeRTOS/stream_buffer.su ./Src/SERVICE/FreeRTOS/tasks.cyclo ./Src/SERVICE/FreeRTOS/tasks.d ./Src/SERVICE/FreeRTOS/tasks.o ./Src/SERVICE/FreeRTOS/tasks.su ./Src/SERVICE/FreeRTOS/timers.cyclo ./Src/SERVICE/FreeRTOS/timers.d ./Src/SERVICE/FreeRTOS/timers.o ./Src/SERVICE/FreeRTOS/timers.su

.PHONY: clean-Src-2f-SERVICE-2f-FreeRTOS

