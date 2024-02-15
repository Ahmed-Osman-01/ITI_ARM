#include "LIB/STD_TYPES.h"
#include "MCAL/RCC/RCC.h"
#include "MCAL/GPIO/GPIO.h"
int main()
{

	GPIO_Pin_t led;
	led.Mode = GPIO_MODE_OP_PP;
	led.Port = GPIO_PORT_C;
	led.Pin = GPIO_PIN_13;
	led.Speed = GPIO_SPEED_MED;


    RCC_EnableClk(RCC_CLK_HSE);
    RCC_SetSystemClk(RCC_SYSCLK_HSE);


    RCC_EnablePeripheral(RCC_GPIOA);
    RCC_EnablePeripheral(RCC_GPIOB);
    RCC_EnablePeripheral(RCC_GPIOC);


    GPIO_Init(&led);


    while(1)
    {
    	GPIO_SetPinState(GPIO_PORT_C, GPIO_PIN_13, GPIO_STATE_HIGH);
    	GPIO_SetPinState(GPIO_PORT_C, GPIO_PIN_13, GPIO_STATE_LOW);
    }
    return 0;
}


