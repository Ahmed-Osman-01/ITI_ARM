

#if 0

#include "LIB/STD_TYPES.h"
#include "MCAL/RCC/RCC.h"

int main()
{
    RCC_EnableClk(RCC_CLK_HSE);
//    RCC_SetSystemClk(RCC_SYSCLK_HSE);
    RCC_SetPllSource(RCC_SYSCLK_HSI);
    RCC_SetPllClk(10, 200, RCC_PLL_P_6, 7);
    RCC_EnableClk(RCC_CLK_PLL);

    RCC_EnablePeripheral(RCC_GPIOA);
//    RCC_EnablePeripheral(RCC_GPIOA);
    RCC_EnablePeripheral(RCC_SPI2);

//    RCC_SetSystemClk(RCC_SYSCLK_HSI);

    RCC_SetAHBPrescale(RCC_AHB_PRESCALE_2);
//    RCC_SetAHBPrescale(RCC_AHB_PRESCALE_1);
    RCC_SetSystemClk(RCC_SYSCLK_PLL);
    RCC_EnablePeripheral(RCC_GPIOC);
    RCC_EnablePeripheral(RCC_USART1);
    RCC_DisablePeripheral(RCC_USART1);
    RCC_DisablePeripheral(RCC_GPIOA);
    RCC_DisablePeripheral(RCC_SPI2);
//    RCC_SetAPB2Prescale(RCC_APB_PRESCALE_4);
//    RCC_SetAPB2Prescale(RCC_APB_PRESCALE_1);
//    RCC_SetAPB1Prescale(RCC_APB_PRESCALE_8);
//    RCC_SetAPB1Prescale(RCC_APB_PRESCALE_1);

//    RCC_DisableClk(RCC_CLK_HSE);
//    RCC_DisableClk(RCC_CLK_PLL);


    while(1)
    {

    }
    return 0;
}


#endif
