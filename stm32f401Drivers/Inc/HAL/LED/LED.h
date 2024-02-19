/*
 * LED.h
 *
 *  Created on: Feb 17, 2024
 *      Author: Osman
 */

#ifndef HAL_LED_H_
#define HAL_LED_H_

#include "HAL/LED/LED_config.h"

#define LED_STATE_OFF    0x00000000
#define LED_STATE_ON     0x00000001

#define LED_CONNECTION_FORWARD      0x00000000
#define LED_CONNECTION_REVERSE      0x00000001

typedef struct
{
    void * Port;
    u32 Pin;
    u8 Connection;
    u8 InitState;

}LED_Config_t;

typedef enum
{
    LED_OK,
    LED_NOK,
}LED_ErrorStatus_t;


LED_ErrorStatus_t LED_Init(void);

LED_ErrorStatus_t LED_SetState(u8 Copy_Led, u8 Copy_State);

#endif /* HAL_LED_H_ */
