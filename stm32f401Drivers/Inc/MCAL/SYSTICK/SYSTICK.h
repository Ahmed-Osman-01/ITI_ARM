/*
 * SYSTICK.h
 *
 *  Created on: Mar 11, 2024
 *      Author: Osman
 */

#ifndef MCAL_SYSTICK_SYSTICK_H_
#define MCAL_SYSTICK_SYSTICK_H_


/* ============================================================================ */
/*                                  INCLUDEDS                           	    */
/* ============================================================================ */


/* ============================================================================ */
/*                                  MACROS                                 	    */
/* ============================================================================ */

#define SYSTICK_CLKSOURCE_PROCESSOR     (u32)0x00000004
#define SYSTICK_CLKSOURCE_EXTERNAL      (u32)0x00000000

#define SYSTICK_MODE_PERIODIC           (u32)0x00000002
#define SYSTICK_MODE_ONESHOT            (u32)0x00000000

/* ============================================================================ */
/*                                  	TYPES                           	    */
/* ============================================================================ */

typedef enum
{
    SYSTICK_OK,
    SYSTICK_NOK,
    SYSTICK_NULL_PTR,

}SYSTICK_ErrorStatus_t;

typedef void (*systickcbf_t) (void);    /* Systick callback function type */

/* ============================================================================ */
/*                                  	PROTOTYPES				                */
/* ============================================================================ */


/**
 * @brief Sets the clock source for the Systick as either Processor clock or External Reference Clock
 * 
 * @param Copy_ClockSource SYSTICK_CLKSOURCE_PROCESSOR or SYSTICK_CLKSOURCE_EXTERNAL
 * @return SYSTICK_ErrorStatus_t Systick module error status
 */
SYSTICK_ErrorStatus_t SYSTICK_ConfigClkSource(u8 Copy_ClockSource);


/**
 * @brief Sets the Time in milli seconds
 * 
 * @param Copy_Time Time in Milli seconds
 * @return SYSTICK_ErrorStatus_t Systick module error status
 * 
 * @note Always consider the selected Clock speed when setting the time
 * @note This function sets the number of ticks to each underflow
 * @note The max number of ticks is 0xFFFFFF(16777215) so for 16MHz source clock the max time is 16777215/16000000
 */
SYSTICK_ErrorStatus_t SYSTICK_SetTimeMs(u32 Copy_Time);


/**
 * @brief Starts the Systick timer in the given mode, if the Mode is Periodic it will keep counting
 * untill stoped and if there is a callback function set, this callback function will be called each
 * period time. 
 * If mode is one shot, timer will start for one time and no callback function will be called
 * 
 * @param Copy_Mode SYSTICK_MODE_PERIODIC or SYSTICK_MODE_ONESHOT
 * @return SYSTICK_ErrorStatus_t Systick module error status 
 */
SYSTICK_ErrorStatus_t SYSTICK_Start(u8 Copy_Mode);


/**
 * @brief Sets the callback function that will be called Periodically
 * 
 * @param cbf The given callback function
 * @return SYSTICK_ErrorStatus_t Systick module error status
 */
SYSTICK_ErrorStatus_t SYSTICK_SetCallback(systickcbf_t cbf);


/**
 * @brief This function is used after starting the timer in one shot mode to make a delay effect
 * 
 * @note This funciton holds the processor busy then stops the timer after the time has passed
 * @note If used after starting the timer in periodic mode, it will wait for the current period to pass, then
 * call the callback function, then stop the timer.
 */
void SYSTICK_IsExpired(void);

#endif /* MCAL_SYSTICK_SYSTICK_H_ */
