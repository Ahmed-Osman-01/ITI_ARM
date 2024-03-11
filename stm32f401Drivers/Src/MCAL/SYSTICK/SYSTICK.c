/*
 * SYSTICK.c
 *
 *  Created on: Mar 11, 2024
 *      Author: Osman
 */


/* ============================================================================ */
/*                                  INCLUDEDS                           	    */
/* ============================================================================ */

#include "LIB/STD_TYPES.h"
#include "MCAL/SYSTICK/SYSTICK.h"
#include "MCAL/SYSTICK/SYSTICK_config.h"


/* ============================================================================ */
/*                                   MACROS                             	    */
/* ============================================================================ */

#define SYSTICK_MAX_TICKS    0xFFFFFF

/* ------------------------------------- */
/*                  MASKS                */
/* ------------------------------------- */

#define SYSTICK_TIMER_START     0x00000001

#define SYSTICK_INT_MASK        0x00000002

#define SYSTICK_COUNT_FLAG_MASK  ((u32)0x00000001 << 16)

/* ------------------------------------- */
/*                  VALIDATIONS          */
/* ------------------------------------- */

#define IS_VALID_MODE(MODE)     ((MODE) == SYSTICK_MODE_PERIODIC || (MODE) == SYSTICK_MODE_ONESHOT)

/* ------------------------------------- */
/*                  REGISTERS            */
/* ------------------------------------- */

#define SYSTICK_BASE_ADDRESS    0xE000E010

#define SYSTICK     ((volatile SYSTICK_Registers_t * const)SYSTICK_BASE_ADDRESS)

/* ============================================================================ */
/*                                  	TYPES                           	    */
/* ============================================================================ */

typedef struct
{
    u32 CTRL;
    u32 LOAD;
    u32 VAL;
    u32 CALIB;

}SYSTICK_Registers_t;



/* ============================================================================ */
/*                                  GLOBAL VARIABLES                    	    */
/* ============================================================================ */

static systickcbf_t     G_systickcbf;

/* ============================================================================ */
/*                                  STATIC FUNCTIONS                    	    */
/* ============================================================================ */

static SYSTICK_ErrorStatus_t SYSTICK_SetTicks(u32 Copy_Ticks)
{
    SYSTICK_ErrorStatus_t Ret_ErrorStatus = SYSTICK_OK;

    if(Copy_Ticks > SYSTICK_MAX_TICKS)
    {
        Ret_ErrorStatus = SYSTICK_NOK;
    }

    if(Ret_ErrorStatus == SYSTICK_OK)
    {
        SYSTICK->LOAD = Copy_Ticks;
    }

    return Ret_ErrorStatus;
}

/* ============================================================================ */
/*                                  IMPLEMENTATION                           	*/
/* ============================================================================ */

SYSTICK_ErrorStatus_t SYSTICK_ConfigClkSource(u8 Copy_ClockSource)
{
    SYSTICK_ErrorStatus_t Ret_ErrorStatus = SYSTICK_OK;

    switch(Copy_ClockSource)
    {
        case SYSTICK_CLKSOURCE_PROCESSOR:
            SYSTICK->CTRL |= SYSTICK_CLKSOURCE_PROCESSOR;
            break;
        
        case SYSTICK_CLKSOURCE_EXTERNAL:
            SYSTICK->CTRL &= ~SYSTICK_CLKSOURCE_PROCESSOR;
            break;

        default:
            Ret_ErrorStatus = SYSTICK_NOK;
    }
    return Ret_ErrorStatus;
}


SYSTICK_ErrorStatus_t SYSTICK_SetTimeMs(u32 Copy_Time)
{
    SYSTICK_ErrorStatus_t Ret_ErrorStatus = SYSTICK_OK;
    u32 Local_ClockSpeed;
    u32 Local_LoadTicks;

    if( (SYSTICK->CTRL & SYSTICK_CLKSOURCE_PROCESSOR) == SYSTICK_CLKSOURCE_PROCESSOR )
    {
        Local_ClockSpeed = SYSTICK_PROCESSOR_CLOCK;
    }
    else
    {
        Local_ClockSpeed = SYSTICK_EXTERNAL_CLOCK;
    }

//    Local_LoadTicks = Local_ClockSpeed * ((f32)Copy_Time/1000) ;

    Local_LoadTicks = ( (Local_ClockSpeed/1000) * Copy_Time ) - 1 ;
    

    Ret_ErrorStatus = SYSTICK_SetTicks(Local_LoadTicks);

    return Ret_ErrorStatus;
}


SYSTICK_ErrorStatus_t SYSTICK_Start(u8 Copy_Mode)
{

    SYSTICK_ErrorStatus_t Ret_ErrorStatus = SYSTICK_OK;

    if(!IS_VALID_MODE(Copy_Mode))
    {
        Ret_ErrorStatus = SYSTICK_NOK;
    }

    if(Ret_ErrorStatus == SYSTICK_OK)
    {
        /* clear the curr timer value */
        SYSTICK->VAL = 1U;

        /* Clear the Interrupt bit then set it according to mode
         if mode is periodic Int bit will be set if not it will stay cleared */
        SYSTICK->CTRL &= ~SYSTICK_INT_MASK;

        /* Enable the systick timer to start it*/
        SYSTICK->CTRL |= (SYSTICK_TIMER_START | Copy_Mode);

    }

    return Ret_ErrorStatus;

}

void SYSTICK_IsExpired(void)
{

	while( !(SYSTICK->CTRL & SYSTICK_COUNT_FLAG_MASK) );

    /* Disable systick */
	SYSTICK->CTRL = 0;

}

SYSTICK_ErrorStatus_t SYSTICK_SetCallback(systickcbf_t cbf)
{
    SYSTICK_ErrorStatus_t Ret_ErrorStatus = SYSTICK_OK;

    if(cbf == NULL)
    {
        Ret_ErrorStatus = SYSTICK_NULL_PTR;
    }

    if(Ret_ErrorStatus == SYSTICK_OK)
    {
        G_systickcbf = cbf;
    }

    return Ret_ErrorStatus;
}


void SysTick_Handler(void)
{
    if(G_systickcbf)
    {
        G_systickcbf();
    }
}
