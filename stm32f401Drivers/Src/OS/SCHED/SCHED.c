/*
 * SCHED.c
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
#include "MCAL/SYSTICK/SYSTICK.h"

/* ============================================================================ */
/*                                   MACROS                             	    */
/* ============================================================================ */


/* ------------------------------------- */
/*                  MASKS                */
/* ------------------------------------- */

/* ------------------------------------- */
/*                  VALIDATIONS          */
/* ------------------------------------- */

/* ------------------------------------- */
/*                  REGISTERS            */
/* ------------------------------------- */



/* ============================================================================ */
/*                                  VALIDATION MACROS                          	*/
/* ============================================================================ */


/* ============================================================================ */
/*                                  	TYPES                           	    */
/* ============================================================================ */


/* ============================================================================ */
/*                                  	EXTERNS                           	    */
/* ============================================================================ */

extern RunnableInfo_t  Runnables[_NUM_RUNNABLE];

/* ============================================================================ */
/*                                  GLOBAL VARIABLES                    	    */
/* ============================================================================ */

/* Initialized to 1 to start handling the runnables at time 0 aka right after calling sched_start */
static volatile u32 G_SchedTicksPending = 1;        /* Variable to tell if sched tick has passed
                                                        if the value of this variable is more than one
                                                        that indicates that CPU load is larger than 100% */

/* ============================================================================ */
/*                                  STATIC FUNCTIONS                           	*/
/* ============================================================================ */

static void SCHED_IncTicksPending(void)
{
    G_SchedTicksPending++;
}

static void SCHED_Scheduler(void)
{
    u16 currRun;

    for(currRun =0; currRun < _NUM_RUNNABLE; currRun++)
    {
        if( (Runnables[currRun].runnable->cb) && (Runnables[currRun].remainingTimeMs == 0) )
        {
            Runnables[currRun].runnable->cb();
            Runnables[currRun].remainingTimeMs = Runnables[currRun].runnable->periodicityMs;
        }

        Runnables[currRun].remainingTimeMs -= SCHED_TICK_PERIOD_MS;
    }
}

/* ============================================================================ */
/*                                  IMPLEMENTATION                           	*/
/* ============================================================================ */


void SCHED_Init(void)
{
    u16 currRun;

    for(currRun = 0; currRun < _NUM_RUNNABLE; currRun++)
    {
        Runnables[currRun].remainingTimeMs = Runnables[currRun].runnable->delayMs;
    }

    SYSTICK_SetTimeMs(SCHED_TICK_PERIOD_MS);
    SYSTICK_SetCallback(SCHED_IncTicksPending);
}

void SCHED_Start(void)
{
    SYSTICK_Start(SYSTICK_MODE_PERIODIC);

    while(1)
    {
        if(G_SchedTicksPending != 0)
        {
            G_SchedTicksPending--;
            SCHED_Scheduler();
        }
    }
}
