/*
 * lin_test.c
 *
 *  Created on: Apr 2, 2024
 *      Author: Osman
 */



#if 0

#include "LIB/STD_TYPES.h"
#include "MCAL/RCC/RCC.h"
#include "MCAL/UART/UART.h"
#include "MCAL/NVIC/NVIC.h"
#include "MCAL/GPIO/GPIO.h"
#include "SERVICE/SCHED/SCHED.h"

#include "COMM/LIN_SLAVE/LIN_SlaveAppData.h"
#include "COMM/LIN_MASTER/LIN_MasterAppData.h"

#include "COMM/LIN_MASTER/LIN_Master.h"
#include "COMM/LIN_SLAVE/LIN_SLave.h"

#include "HAL/LCD/LCD.h"
#include "HAL/LED/LED.h"

#include "APP/TrafficLights/blinkingLed.h"


u8 buffer[7] = {0};

void fun(void)
{

}



void rxCB(void)
{
	LCD_WriteBufferAsync(buffer, 7);
}


int main(void)
{

    RCC_EnableClk(RCC_CLK_HSE);
    RCC_SetSystemClk(RCC_SYSCLK_HSE);

    RCC_EnablePeripheral(RCC_GPIOA);
    RCC_EnablePeripheral(RCC_GPIOB);
    RCC_EnablePeripheral(RCC_USART1);
    RCC_EnablePeripheral(RCC_USART2);
    RCC_EnablePeripheral(RCC_USART6);

    NVIC_EnableInterrupt(NVIC_USART2);
    NVIC_EnableInterrupt(NVIC_USART1);



	GPIO_Pin_t ledPin;

	ledPin.Mode = GPIO_MODE_OP_PP;
	ledPin.AF = GPIO_AF_SYSTEM;
	ledPin.Pin = GPIO_PIN_1;
	ledPin.Port = GPIO_PORT_B;
	ledPin.Speed = GPIO_SPEED_HIGH;
	GPIO_Init(&ledPin);


	LIN_MasterInit();
	LIN_SlaveInit();

//    LCD_Init();
    LED_Init();


    blinkingLed_Init();

//    UART_SendBreak(UART1);
//    UART_SendBreak(UART2);


       u16 masterGetData;
       u16 masterSendData = 0x0807;
       MasterGetControls(&masterGetData);
       MasterSendControls(masterSendData);


       u16 slaveGetData;
       u16 slaveSendData =0x0201;
       SlaveGetControls(&slaveGetData);
       SlaveSendControls(slaveSendData);

    SCHED_Init();
    SCHED_Start();

    return 0;
}


void lcdApp(void)
{
//	UART_TXByte(UART2, 'A');

//	UART_TXBufferAsyncZC(UART2, "Ahmed\n\r", 7, fun);

//	UART_SendBreak(UART2);


//    u16 masterGetData;
//    u16 masterSendData = 0x0807;
//    MasterGetControls(&masterGetData);
//    MasterSendControls(masterSendData);
//
//
//    u16 slaveGetData;
//    u16 slaveSendData =0x0201;
//    SlaveGetControls(&slaveGetData);
//    SlaveSendControls(slaveSendData);


}

void uartApp(void)
{
//	u8 input = 0;


//	UART_RXByte(UART2, &input);
//
//	if(input == '0')
//	{
//		LED_SetState(LED_ONE, LED_STATE_OFF);
//		LCD_ClearScreenAsync();
//
//	}
//	else if(input == '1')
//	{
//		LED_SetState(LED_ONE, LED_STATE_ON);
//		UART_RXBufferAsyncZC(UART2, buffer, 7, rxCB);
//	}
}


#endif
