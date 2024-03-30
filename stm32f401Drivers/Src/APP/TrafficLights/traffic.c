/*
 * traffic.c
 *
 *  Created on: Mar 12, 2024
 *      Author: Osman
 */


#if 0


/* ============================================================================ */
/*                                  INCLUDEDS                           	    */
/* ============================================================================ */

#include "LIB/STD_TYPES.h"
#include "MCAL/RCC/RCC.h"
#include "HAL/LED/LED.h"

/* ============================================================================ */
/*                                   MACROS                             	    */
/* ============================================================================ */

#define TRAFFIC_PERIODICITY_SEC     2

#define RED_LIGHT_ON_TIME           4
#define YELLOW_LIGHT_ON_TIME        2
#define GREEN_LIGHT_ON_TIME         4


/* ============================================================================ */
/*                                  	TYPES                           	    */
/* ============================================================================ */

typedef enum {RED, YELLOW, GREEN}traffic_states_t;


/* ============================================================================ */
/*                                  GLOBAL VARIABLES                    	    */
/* ============================================================================ */
static traffic_states_t state = RED;
static u8 passedSeconds;


/* ============================================================================ */
/*                                  IMPLEMENTATION                           	*/
/* ============================================================================ */

void traffic_Init(void)
{
    RCC_EnablePeripheral(RCC_GPIOA);
    LED_Init();
}


void traffic_Update(void)
{
    passedSeconds += TRAFFIC_PERIODICITY_SEC;
    static traffic_states_t prevState = RED;

    switch (state)
    {
    case RED:
        LED_SetState(RED_LED, LED_STATE_ON);
        LED_SetState(YELLOW_LED, LED_STATE_OFF);
        LED_SetState(GREEN_LED, LED_STATE_OFF);

        if(passedSeconds == RED_LIGHT_ON_TIME)
        {
            passedSeconds = 0;
            prevState = state;
            state = YELLOW;
        }

        break;
    
    case YELLOW:
        LED_SetState(RED_LED, LED_STATE_OFF);
        LED_SetState(YELLOW_LED, LED_STATE_ON);
        LED_SetState(GREEN_LED, LED_STATE_OFF);

        if(passedSeconds == YELLOW_LIGHT_ON_TIME && prevState == RED)
        {
            passedSeconds = 0;
            prevState = state;
            state = GREEN;
        }
        else if(passedSeconds == YELLOW_LIGHT_ON_TIME && prevState == GREEN)
        {
            passedSeconds = 0;
            prevState = state;
            state = RED;
        }
        
        break;


    case GREEN:
        LED_SetState(RED_LED, LED_STATE_OFF);
        LED_SetState(YELLOW_LED, LED_STATE_OFF);
        LED_SetState(GREEN_LED, LED_STATE_ON);

        if(passedSeconds == GREEN_LIGHT_ON_TIME)
        {
            passedSeconds = 0;
            prevState = state;
            state = YELLOW;
        }

        break;

    default:
        break;
    }

}



#endif
