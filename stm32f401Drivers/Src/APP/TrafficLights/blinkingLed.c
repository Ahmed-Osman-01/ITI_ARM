/*
 * blinkingLed.c
 *
 *  Created on: Mar 12, 2024
 *      Author: Osman
 */

/* ============================================================================ */
/*                                  INCLUDEDS                           	    */
/* ============================================================================ */
#include "LIB/STD_TYPES.h"
#include "MCAL/RCC/RCC.h"
#include "HAL/LED/LED.h"


/* ============================================================================ */
/*                                  GLOBAL VARIABLES                    	    */
/* ============================================================================ */
static u8 state = LED_STATE_OFF;


/* ============================================================================ */
/*                                  IMPLEMENTATION                           	*/
/* ============================================================================ */


void blinkingLed_Init(void)
{
    RCC_EnablePeripheral(RCC_GPIOC);
    LED_Init();
}

void blinkingLed_Update(void)
{
    LED_SetState(BLINKING_LED, state);
    state = !state;
}