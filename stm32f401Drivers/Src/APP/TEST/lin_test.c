/*
 * lin_test.c
 *
 *  Created on: Apr 2, 2024
 *      Author: Osman
 */


#include "LIB/STD_TYPES.h"
#include "MCAL/RCC/RCC.h"
#include "MCAL/UART/UART.h"
#include "MCAL/NVIC/NVIC.h"
#include "MCAL/GPIO/GPIO.h"
#include "SERVICE/SCHED/SCHED.h"

#include "HAL/LCD/LCD.h"
#include "HAL/LED/LED.h"

#include "APP/TrafficLights/blinkingLed.h"


u8 buffer[7] = {0};

void fun(void)
{

}

void lbd(void)
{
	static u8 state = GPIO_STATE_HIGH;


	GPIO_SetPinState(GPIO_PORT_B, GPIO_PIN_1, state);
	state = !state;
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



	GPIO_Pin_t ledPin;

	ledPin.Mode = GPIO_MODE_OP_PP;
	ledPin.AF = GPIO_AF_SYSTEM;
	ledPin.Pin = GPIO_PIN_1;
	ledPin.Port = GPIO_PORT_B;
	ledPin.Speed = GPIO_SPEED_HIGH;
	GPIO_Init(&ledPin);


    GPIO_Pin_t uart2TX;
    GPIO_Pin_t uart2RX;

    uart2TX.Mode = GPIO_MODE_AF_PP;
    uart2TX.AF = GPIO_AF_USART1_2;
    uart2TX.Pin = GPIO_PIN_2;
    uart2TX.Port = GPIO_PORT_A;
    uart2TX.Speed = GPIO_SPEED_HIGH;

    uart2RX.Mode = GPIO_MODE_AF_PP;
    uart2RX.AF = GPIO_AF_USART1_2;
    uart2RX.Pin = GPIO_PIN_3;
    uart2RX.Port = GPIO_PORT_A;
    uart2RX.Speed = GPIO_SPEED_HIGH;

    GPIO_Init(&uart2TX);
    GPIO_Init(&uart2RX);

    UART_Config_t uart1Config;
    uart1Config.BaudRate = 9600;
    uart1Config.Mode = UART_MODE_TX_RX;
    uart1Config.Parity = UART_PARITY_DISABLE;
    uart1Config.Sampling = UART_SAMPLING_16;
    uart1Config.WordLength = UART_WORDLENGTH_8;

    UART_SetConfig(UART2, &uart1Config);

    LCD_Init();
    LED_Init();

    UART_LIN_Config_t linConfig;
    linConfig.State = UART_LIN_ENABLED;
    linConfig.BreakDetectLength = UART_LIN_BREAK_DETECTION_11;
    linConfig.BreakDetectInterrupt = UART_LIN_BREAK_INTERRUPT_ENABLED;

    UART_ConfigLIN(UART2, &linConfig);


    UART_SetLBDCallback(UART2, lbd);

//    UART_TXLINBreak(UART2);

    blinkingLed_Init();

    SCHED_Init();
    SCHED_Start();

    return 0;
}


void lcdApp(void)
{
//	UART_TXByte(UART2, 'A');

//	UART_TXBufferAsyncZC(UART2, "Ahmed\n\r", 7, fun);

	UART_TXLINBreak(UART2);

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
