/*
 * LED.h
 *
 *  Created on: Feb 17, 2024
 *      Author: Osman
 */

#ifndef HAL_LED_H_
#define HAL_LED_H_

/* ============================================================================ */
/*                                  INCLUDEDS                           	    */
/* ============================================================================ */
#include "HAL/LED/LED_config.h"


/* ============================================================================ */
/*                                  MACROS                                     	*/
/* ============================================================================ */

#define LED_STATE_OFF    0x00000000
#define LED_STATE_ON     0x00000001

#define LED_CONNECTION_FORWARD      0x00000000
#define LED_CONNECTION_REVERSE      0x00000001


/* ============================================================================ */
/*                                  TYPES                                  	    */
/* ============================================================================ */
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
    LED_INVALID_STATE,
    LED_INVALID_ID,
}LED_ErrorStatus_t;


/* ============================================================================ */
/*                                  APIS PROTOTYPES                           	*/
/* ============================================================================ */


/**
 * @brief Initializes all the leds configured in configure files
 * 
 * @return LED_ErrorStatus_t LED module error status
 * 
 * @note LEDs Must be configured in LED_config.h and LED_config.c files before using this function
 */
LED_ErrorStatus_t LED_Init(void);


/**
 * @brief Sets the State of the Specified LED (ON or OFF)
 * 
 * @param Copy_Led ID of the LED as defined in LED_config.h
 * @param Copy_State The State to set the LED to
 * @return LED_ErrorStatus_t LED module error status
 * 
 * @note LEDs must be initialized first by calling LED_Init() function
 */
LED_ErrorStatus_t LED_SetState(LED_ID_t Copy_LedID, u8 Copy_State);

#endif /* HAL_LED_H_ */
