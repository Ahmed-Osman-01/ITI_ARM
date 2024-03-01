/*
 * LED.c
 *
 *  Created on: Feb 17, 2024
 *      Author: Osman
 */

/* ============================================================================ */
/*                                  INCLUDEDS                           	    */
/* ============================================================================ */

#include "LIB/STD_TYPES.h"
#include "HAL/LED/LED.h"
#include "MCAL/GPIO/GPIO.h "

/* ============================================================================ */
/*                                  VALIDATION MACROS                          	*/
/* ============================================================================ */

#define IS_LED_STATE(STATE)     ((STATE == LED_STATE_ON) || (STATE == LED_STATE_OFF))

/* ============================================================================ */
/*                                  	EXTERNS                               	*/
/* ============================================================================ */

extern const LED_Config_t Leds[_LED_NUM];



/* ============================================================================ */
/*                                  IMPLEMENTATION                           	*/
/* ============================================================================ */

LED_ErrorStatus_t LED_Init(void)
{
    LED_ErrorStatus_t Ret_ErrorStatus = LED_OK;
    GPIO_Pin_t Local_Led;
    u8 Local_iter;
    Local_Led.Mode = GPIO_MODE_OP_PP;
    Local_Led.Speed = GPIO_SPEED_HIGH;
    Local_Led.AF = GPIO_AF_SYSTEM;

    for(Local_iter = 0; Local_iter < _LED_NUM; Local_iter++)
    {
        if(!IS_LED_STATE(Leds[Local_iter].InitState))
        {
            Ret_ErrorStatus = LED_INVALID_STATE;
        }
        else
        {
            Local_Led.Port = Leds[Local_iter].Port;
            Local_Led.Pin = Leds[Local_iter].Pin;
            Ret_ErrorStatus = GPIO_Init(&Local_Led);
            GPIO_SetPinState(Leds[Local_iter].Port, Leds[Local_iter].Pin, Leds[Local_iter].InitState ^ Leds[Local_iter].Connection);
        }

        if(Ret_ErrorStatus != LED_OK)
        {
            break;
        }
    }

    return Ret_ErrorStatus;
}


LED_ErrorStatus_t LED_SetState(LED_ID_t Copy_LedID, u8 Copy_State)
{
    LED_ErrorStatus_t Ret_ErrorStatus = LED_OK;

    if(Copy_LedID >= _LED_NUM)
    {
        Ret_ErrorStatus = LED_INVALID_ID;
    }
    else if(!IS_LED_STATE(Copy_State))
    {
        Ret_ErrorStatus = LED_INVALID_STATE;
    }
    else
    {
        /* do nothing */
    }

    if(Ret_ErrorStatus == LED_OK)
    {
        Ret_ErrorStatus = GPIO_SetPinState(Leds[Copy_LedID].Port, Leds[Copy_LedID].Pin, Copy_State ^ Leds[Copy_LedID].Connection);
    }

    return Ret_ErrorStatus;
}
