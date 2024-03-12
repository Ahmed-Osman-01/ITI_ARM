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

extern void APP1(void);
extern void SWITCH_Update(void);


/* ============================================================================ */
/*                                  Runnable Objects                       	    */
/* ============================================================================ */

/* ------------------------------------- */
/* Create Runnable objects here for each */
/* runnable in the system                */
/* ------------------------------------- */


Runnable_t runnable1 = {.name = "update switch", .periodicityMs = 5, .periority = SWITCH_UPDATE, .delayMs = 0, .cb = SWITCH_Update};
Runnable_t runnable2 = {.name = "control led", .periodicityMs = 1000, .periority = APP1_RUNNABLE, .delayMs = 0, .cb = APP1};
//Runnable_t runnable3 = {.name = "run2", .periodicityMs = 1000, .periority = APP3_RUNNABLE, .delayMs = 0, .cb = APP3};
//Runnable_t runnable4 = {.name = "run2", .periodicityMs = 2000, .periority = APP4_RUNNABLE, .delayMs = 0, .cb = APP4};
//Runnable_t runnable5 = {.name = "run2", .periodicityMs = 5000, .periority = APP5_RUNNABLE, .delayMs = 0, .cb = APP5};


RunnableInfo_t Runnables [_NUM_RUNNABLE] = {

    [SWITCH_UPDATE] = {.runnable = &runnable1},
    [APP1_RUNNABLE] ={.runnable = &runnable2},
//    [APP3_RUNNABLE] ={.runnable = &runnable3},
//    [APP4_RUNNABLE] ={.runnable = &runnable4},
//    [APP5_RUNNABLE] ={.runnable = &runnable5},
};
