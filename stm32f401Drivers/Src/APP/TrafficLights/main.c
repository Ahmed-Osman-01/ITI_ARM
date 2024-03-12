/*
 * main.c
 *
 *  Created on: Mar 12, 2024
 *      Author: Osman
 */



#include "LIB/STD_TYPES.h"
#include "MCAL/RCC/RCC.h"
#include "OS/SCHED/SCHED.h"

#include "APP/TrafficLights/blinkingLed.h"
#include "APP/TrafficLights/traffic.h"


int main(void)
{

    RCC_EnableClk(RCC_CLK_HSE);
    RCC_SetSystemClk(RCC_SYSCLK_HSE);

    RCC_EnablePeripheral(RCC_GPIOA);

    traffic_Init();
    blinkingLed_Init();

    SCHED_Init();
    SCHED_Start();

    return 0;
}