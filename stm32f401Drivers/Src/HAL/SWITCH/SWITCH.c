/*
* SWITCH.c
*
*  Created on: Feb 18, 2024
*      Author: Osman
*/

/* ============================================================================ */
/*                                  INCLUDEDS                           	    */
/* ============================================================================ */

#include "LIB/STD_TYPES.h"
#include "HAL/SWITCH/SWITCH.h"
#include "MCAL/GPIO/GPIO.h"


/* ============================================================================ */
/*                                  MASKS MACROS                           	    */
/* ============================================================================ */
#define SWITCH_PULLUP_OFFSET    0x00000003


/* ============================================================================ */
/*                                  VALIDATION MACROS                          	*/
/* ============================================================================ */

#define IS_SWITCH_CONNECTION(CONNECTION)    ((CONNECTION == SWITCH_CONNECTION_FLOATING) ||\
                                             (CONNECTION == SWITCH_CONNECTION_PULLUP)   ||\
                                             (CONNECTION == SWITCH_CONNECTION_PULLDOWN))

/* ============================================================================ */
/*                                  	EXTERNS                           	    */
/* ============================================================================ */

extern const SWITCH_Config_t Switches[_SWITCH_NUM];




/* ============================================================================ */
/*                                  IMPLEMENTATION                           	*/
/* ============================================================================ */

SWITCH_ErrorStatus_t SWITCH_Init(void)
{
   SWITCH_ErrorStatus_t Ret_ErrorStatus = SWITCH_OK;

   GPIO_Pin_t Local_Switch;
   u8 Local_Iter;
   Local_Switch.Speed = GPIO_SPEED_HIGH;
   Local_Switch.AF = GPIO_AF_SYSTEM;

   for(Local_Iter = 0; Local_Iter < _SWITCH_NUM; Local_Iter++)
   {

        if(!IS_SWITCH_CONNECTION(Switches[Local_Iter].Connection))
        {
            Ret_ErrorStatus = SWITCH_INVALID_CONNECTION;
        }
        else
        {
            Local_Switch.Port = Switches[Local_Iter].Port;
            Local_Switch.Pin = Switches[Local_Iter].Pin;
            Local_Switch.Mode = Switches[Local_Iter].Connection;
            Ret_ErrorStatus = GPIO_Init(&Local_Switch);
        }

        if(Ret_ErrorStatus != SWITCH_OK)
        {
            break;
        }

   }

   return Ret_ErrorStatus;
}


SWITCH_ErrorStatus_t SWITCH_GetSwitchState(SWITCH_ID_t Copy_SwitchID, u8 *Add_SwitchState)
{
    SWITCH_ErrorStatus_t Ret_ErrorStatus = SWITCH_OK;
    u8 Local_PinState;
    if(Copy_SwitchID >= _SWITCH_NUM)
    {
        Ret_ErrorStatus = SWITCH_INVALID_SWITCH_ID;
    }
    else if(Add_SwitchState == NULL)
    {
        Ret_ErrorStatus = SWITCH_NULLPTR;
    }
    else
    {
        /* do nothing */
    }

    if(Ret_ErrorStatus == SWITCH_OK)
    {
       Ret_ErrorStatus = GPIO_GetPin(Switches[Copy_SwitchID].Port, Switches[Copy_SwitchID].Pin, &Local_PinState);

        /* This line to return Either Pressed Or Released Regardless of the Connection
            If The connection is PullUp then inverse the returned state from GPIO to match the
            actuall state (Pressed or Released) */
        *Add_SwitchState =  Local_PinState ^ ( (Switches[Copy_SwitchID].Connection & SWITCH_CONNECTION_PULLUP) >> SWITCH_PULLUP_OFFSET);
    }

    return Ret_ErrorStatus;
}


//u8 SWITCH_GetSwitchState(u8 Copy_SwitchID)
//{
//    static u8 Ret_State = SWITCH_STATE_RELEASED;
//    u8 Local_Input = GPIO_GetPin(Switches[Copy_SwitchID].Port, Switches[Copy_SwitchID].Pin);
//
//    /* This line to return Either Pressed Or Released Regardless of the Connection
//        If The connection is PullUp then inverse the returned state from GPIO to match the
//        actuall state (Pressed or Released) */
//    Local_Input ^= ( (Switches[Copy_SwitchID].Connection & SWITCH_CONNECTION_PULLUP) >> SWITCH_PULLUP_OFFSET);
//
//
//    if(Ret_State == SWITCH_STATE_RELEASED && Local_Input == SWITCH_STATE_PRESSED)
//    {
//        Ret_State = SWITCH_STATE_PRESSED;
//    }
//    else if(Ret_State == SWITCH_STATE_PRESSED && Local_Input == SWITCH_STATE_PRESSED)
//    {
//        Ret_State = SWITCH_STATE_HOLD;
//    }
//    else if(Local_Input == SWITCH_STATE_RELEASED)
//    {
//        Ret_State = SWITCH_STATE_RELEASED;
//    }
//    else
//    {
//        /* do nothing */
//    }
//
//    return Ret_State;
//}
