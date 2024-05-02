


#if 1


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



    blinkingLed_Init();
    LED_Init();
    LCD_Init();




    SCHED_Init();
    SCHED_Start();

    return 0;
}


void lcdApp(void)
{

	LCD_SendCommandAsync(DISPLAY_ON_CURSOR_ON_BLINKING_ON);

//	LCD_WriteStringAsync("Ahmed");
//	LCD_WriteStringAsync("Ahmed");
//	LCD_WriteStringAsync("Ahmed");
//	LCD_WriteStringAsync("Ahmed");
	LCD_WriteStringAsync("Ahmed");

	LCD_SetCursorPosAsync(1, 0);
//	LCD_WriteStringAsync("AhmedDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD");
	LCD_WriteStringAsync("Ahmed");

//	LCD_WriteStringAsync("Osman");
	LCD_SetCursorPosAsync(0, 0);

//	LCD_SendCommandAsync(DISPLAY_ON_CURSOR_OFF_BLINKING_OFF);
//	LCD_SendCommandAsync(DISPLAY_ON_CURSOR_ON_BLINKING_OFF);


}

void uartApp(void)
{

}

#endif
