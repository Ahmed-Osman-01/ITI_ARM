/*
 * led_switch_test.c
 *
 *  Created on: Feb 17, 2024
 *      Author: Osman
 */



#if 0

#include "LIB/STD_TYPES.h"
#include "MCAL/RCC/RCC.h"
#include "HAL/LED/LED.h"
#include "HAL/SWITCH/SWITCH.h"

int main(void)
{
	u8 state = SWITCH_STATE_RELEASED;

	RCC_EnableClk(RCC_CLK_HSE);

	RCC_SetSystemClk(RCC_SYSCLK_HSE);

	RCC_EnablePeripheral(RCC_GPIOA);
	RCC_EnablePeripheral(RCC_GPIOB);
	RCC_EnablePeripheral(RCC_GPIOC);

	LED_Init();
	SWITCH_Init();

	while(1)
	{
		SWITCH_GetSwitchState(SWITCH_ONE, &state);

		if(state == SWITCH_STATE_PRESSED)
		{
			LED_SetState(LED_ONE, LED_STATE_ON);
			LED_SetState(LED_TWO, LED_STATE_ON);
		}
		else
		{
			LED_SetState(LED_ONE, LED_STATE_OFF);
			LED_SetState(LED_TWO, LED_STATE_OFF);
		}

	}
	return 0;
}
#endif
