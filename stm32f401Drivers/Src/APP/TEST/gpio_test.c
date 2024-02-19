//#include "LIB/STD_TYPES.h"
//#include "MCAL/RCC/RCC.h"
//#include "MCAL/GPIO/GPIO.h"
//int main()
//{
//
//	u8 state = GPIO_STATE_LOW;
//
//
//	GPIO_Pin_t led;
//	led.Mode = GPIO_MODE_OP_OD;
//	led.Port = GPIO_PORT_C;
//	led.Pin = GPIO_PIN_13;
//	led.Speed = GPIO_SPEED_MED;
//	led.AF = GPIO_AF_EVENTOUT;
//
//	GPIO_Pin_t sw;
//	sw.Mode = GPIO_MODE_IN_PU;
//	sw.Port = GPIO_PORT_A;
//	sw.Pin = GPIO_PIN_0;
//	sw.Speed = GPIO_SPEED_MED;
//	sw.AF = GPIO_AF_TIM1_2;
//
//
//    RCC_EnableClk(RCC_CLK_HSE);
//    RCC_SetSystemClk(RCC_SYSCLK_HSE);
//
//
//    RCC_EnablePeripheral(RCC_GPIOA);
//    RCC_EnablePeripheral(RCC_GPIOB);
//    RCC_EnablePeripheral(RCC_GPIOC);
//
//
//    GPIO_Init(&led);
//    GPIO_Init(&sw);
//
//
//
//    while(1)
//    {
//
//    	state = GPIO_GetPin(GPIO_PORT_A, GPIO_PIN_0);
//    	if(state == GPIO_STATE_HIGH)
//    	{
//    		GPIO_SetPinState(GPIO_PORT_C, GPIO_PIN_13, GPIO_STATE_HIGH);
//    	}
//    	else
//    	{
//    		GPIO_SetPinState(GPIO_PORT_C, GPIO_PIN_13, GPIO_STATE_LOW);
//    	}
//
//    }
//    return 0;
//}
//
//
