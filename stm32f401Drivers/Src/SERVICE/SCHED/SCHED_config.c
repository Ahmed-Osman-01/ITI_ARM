/*
 * SCHED_config.c
 *
 *  Created on: Mar 11, 2024
 *      Author: Osman
 */


/* ============================================================================ */
/*                                  INCLUDEDS                           	    */
/* ============================================================================ */

#include "LIB/STD_TYPES.h"
#include "SERVICE/SCHED/SCHED.h"
#include "SERVICE/SCHED/SCHED_config.h"


/* ============================================================================ */
/*                                  Extern Functions                       	    */
/* ============================================================================ */

// extern void APP1(void);
// extern void SWITCH_Update(void);

extern void blinkingLed_Update(void);
extern void LCD_Update(void);
extern void lcdApp(void);
extern void uartApp(void);

/* ============================================================================ */
/*                                  Runnable Objects                       	    */
/* ============================================================================ */

/* ------------------------------------- */
/* Create Runnable objects here for each */
/* runnable in the system                */
/* ------------------------------------- */


Runnable_t Runnables[_NUM_RUNNABLE] = 
{
    [BLINKING_LED] =  {.name = "blinking led", .periodicityMs = 500, .periority = BLINKING_LED, .delayMs = 0, .cb = blinkingLed_Update},
    [LCD] = {.name = "lcd", .periodicityMs = 2, .periority = LCD, .delayMs = 0, .cb = LCD_Update},
    [LCD_APP] = {.name = "lcd APP", .periodicityMs = 1000, .periority = LCD_APP, .delayMs = 0, .cb = lcdApp},
    [LCD_CLEAR] = {.name = "lcd APP", .periodicityMs = 1100, .periority = LCD_CLEAR, .delayMs = 0, .cb = uartApp},
};
