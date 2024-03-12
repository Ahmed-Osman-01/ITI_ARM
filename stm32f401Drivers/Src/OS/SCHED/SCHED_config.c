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
#include "OS/SCHED/SCHED.h"
#include "OS/SCHED/SCHED_config.h"


/* ============================================================================ */
/*                                  Extern Functions                       	    */
/* ============================================================================ */

// extern void APP1(void);
// extern void SWITCH_Update(void);

extern void blinkingLed_Update(void);
extern void traffic_Update(void);

/* ============================================================================ */
/*                                  Runnable Objects                       	    */
/* ============================================================================ */

/* ------------------------------------- */
/* Create Runnable objects here for each */
/* runnable in the system                */
/* ------------------------------------- */


Runnable_t runnable1 = {.name = "blinking led", .periodicityMs = 500, .periority = BLINKING_LED, .delayMs = 0, .cb = blinkingLed_Update};
Runnable_t runnable2 = {.name = "traffic light", .periodicityMs = 2000, .periority = TRAFFIC_LIGHT, .delayMs = 0, .cb = traffic_Update};
//Runnable_t runnable3 = {.name = "run2", .periodicityMs = 1000, .periority = APP3_RUNNABLE, .delayMs = 0, .cb = APP3};
//Runnable_t runnable4 = {.name = "run2", .periodicityMs = 2000, .periority = APP4_RUNNABLE, .delayMs = 0, .cb = APP4};
//Runnable_t runnable5 = {.name = "run2", .periodicityMs = 5000, .periority = APP5_RUNNABLE, .delayMs = 0, .cb = APP5};


RunnableInfo_t Runnables [_NUM_RUNNABLE] = {

    [BLINKING_LED] = {.runnable = &runnable1},
    [TRAFFIC_LIGHT] ={.runnable = &runnable2},
//    [APP3_RUNNABLE] ={.runnable = &runnable3},
//    [APP4_RUNNABLE] ={.runnable = &runnable4},
//    [APP5_RUNNABLE] ={.runnable = &runnable5},
};
