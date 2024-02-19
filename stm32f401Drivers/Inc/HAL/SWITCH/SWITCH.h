/*
 * SWITCH.h
 *
 *  Created on: Feb 18, 2024
 *      Author: Osman
 */

#ifndef HAL_SWITCH_SWITCH_H_
#define HAL_SWITCH_SWITCH_H_

#include "HAL/SWITCH/SWITCH_config.h"



#define SWITCH_STATE_RELEASED       0x00000000
#define SWITCH_STATE_PRESSED        0x00000001
#define SWITCH_STATE_HOLD           0x00000002

#define SWITCH_CONNECTION_FLOATING  0x00000000
#define SWITCH_CONNECTION_PULLUP    0x00000008
#define SWITCH_CONNECTION_PULLDOWN  0x00000010


typedef struct
{
    void * Port;
    u32 Pin;
    u8 Connection;
}SWITCH_Config_t;

typedef enum
{
    SWITCH_OK,
    SWITCH_NOK,
}SWITCH_ErrorStatus_t;




SWITCH_ErrorStatus_t SWITCH_Init(void);


u8 SWITCH_GetSwitchState(u8 Copy_Switch);

#endif /* HAL_SWITCH_SWITCH_H_ */
