/*
 * LIN_HW.c
 * 
 * A spearate Layer to Initialize the hardware used by the LIN protocol, in this case it's the UART
 * 
 */


/* ============================================================================ */
/*                                  INCLUDEDS                           	    */
/* ============================================================================ */

#include "LIB/STD_TYPES.h"
#include "MCAL/GPIO/GPIO.h"

#include "MCAL/UART/UART.h"

#include "COMM/LIN/LIN_HW_config.h"
#include "COMM/LIN/LIN_HW.h"

#include "COMM/LIN/LIN_config.h"

/* ============================================================================ */
/*                                   MACROS                             	    */
/* ============================================================================ */


/* ------------------------------------- */
/*                  MASKS                */
/* ------------------------------------- */

/* ------------------------------------- */
/*                  VALIDATIONS          */
/* ------------------------------------- */

/* ------------------------------------- */
/*                  REGISTERS            */
/* ------------------------------------- */



/* ============================================================================ */
/*                                  VALIDATION MACROS                          	*/
/* ============================================================================ */


/* ============================================================================ */
/*                                  	TYPES                           	    */
/* ============================================================================ */


/* ============================================================================ */
/*                                  	EXTERNS                           	    */
/* ============================================================================ */

/* ============================================================================ */
/*                                  GLOBAL VARIABLES                    	    */
/* ============================================================================ */

/* ============================================================================ */
/*                                  IMPLEMENTATION                           	*/
/* ============================================================================ */


#if LIN_HW_USED_UART == UART1

void LIN_HW_Init(void)
{

    GPIO_Pin_t uartTX;
    GPIO_Pin_t uartRX;

    uartTX.Mode = GPIO_MODE_AF_PP;
    uartTX.AF = GPIO_AF_USART1_2;
    uartTX.Pin = GPIO_PIN_9;
    uartTX.Port = GPIO_PORT_A;
    uartTX.Speed = GPIO_SPEED_HIGH;

    uartRX.Mode = GPIO_MODE_AF_PP;
    uartRX.AF = GPIO_AF_USART1_2;
    uartRX.Pin = GPIO_PIN_10;
    uartRX.Port = GPIO_PORT_A;
    uartRX.Speed = GPIO_SPEED_HIGH;

    GPIO_Init(&uartTX);
    GPIO_Init(&uartRX);


    UART_Config_t uart1Config;
    uart1Config.BaudRate = LIN_SPEED;
    uart1Config.Mode = UART_MODE_TX_RX;
    uart1Config.Parity = UART_PARITY_DISABLE;
    uart1Config.Sampling = UART_SAMPLING_16;
    uart1Config.WordLength = UART_WORDLENGTH_8;

    UART_SetConfig(UART2, &uart1Config);
}



#elif LIN_HW_USED_UART == UART2

void LIN_HW_Init(void)
{

    GPIO_Pin_t uartTX;
    GPIO_Pin_t uartRX;

    uartTX.Mode = GPIO_MODE_AF_PP;
    uartTX.AF = GPIO_AF_USART1_2;
    uartTX.Pin = GPIO_PIN_2;
    uartTX.Port = GPIO_PORT_A;
    uartTX.Speed = GPIO_SPEED_HIGH;

    uartRX.Mode = GPIO_MODE_AF_PP;
    uartRX.AF = GPIO_AF_USART1_2;
    uartRX.Pin = GPIO_PIN_3;
    uartRX.Port = GPIO_PORT_A;
    uartRX.Speed = GPIO_SPEED_HIGH;

    GPIO_Init(&uartTX);
    GPIO_Init(&uartRX);


    UART_Config_t uart1Config;
    uart1Config.BaudRate = LIN_SPEED;
    uart1Config.Mode = UART_MODE_TX_RX;
    uart1Config.Parity = UART_PARITY_DISABLE;
    uart1Config.Sampling = UART_SAMPLING_16;
    uart1Config.WordLength = UART_WORDLENGTH_8;

    UART_SetConfig(UART2, &uart1Config);
}


#elif LIN_HW_USED_UART == UART6


void LIN_HW_Init(void)
{

    GPIO_Pin_t uartTX;
    GPIO_Pin_t uartRX;

    uartTX.Mode = GPIO_MODE_AF_PP;
    uartTX.AF = GPIO_AF_USART6;
    uartTX.Pin = GPIO_PIN_11;
    uartTX.Port = GPIO_PORT_A;
    uartTX.Speed = GPIO_SPEED_HIGH;

    uartRX.Mode = GPIO_MODE_AF_PP;
    uartRX.AF = GPIO_AF_USART6;
    uartRX.Pin = GPIO_PIN_12;
    uartRX.Port = GPIO_PORT_A;
    uartRX.Speed = GPIO_SPEED_HIGH;

    GPIO_Init(&uartTX);
    GPIO_Init(&uartRX);


    UART_Config_t uart1Config;
    uart1Config.BaudRate = LIN_SPEED;
    uart1Config.Mode = UART_MODE_TX_RX;
    uart1Config.Parity = UART_PARITY_DISABLE;
    uart1Config.Sampling = UART_SAMPLING_16;
    uart1Config.WordLength = UART_WORDLENGTH_8;

    UART_SetConfig(UART2, &uart1Config);
}


#endif