/*
 * SCHED.h
 *
 *  Created on: Mar 11, 2024
 *      Author: Osman
 */

#ifndef OS_SCHED_H_
#define OS_SCHED_H_



/* ============================================================================ */
/*                                  INCLUDEDS                           	    */
/* ============================================================================ */


/* ============================================================================ */
/*                                  MACROS                                 	    */
/* ============================================================================ */


/* ============================================================================ */
/*                                  	TYPES                           	    */
/* ============================================================================ */

typedef void (*RunnableCb_t)(void);

/* Struct describing the runnable object itself */
typedef struct
{
    char * name;
    u32 periodicityMs;
    u32 periority;
    u32 delayMs;
    RunnableCb_t cb;

}Runnable_t;

/* Describes the runtime information for each runnable that the schedular use */
typedef struct
{
    const Runnable_t * const runnable;
    u32 remainingTimeMs;

}RunnableInfo_t;


typedef enum
{
    SCHED_OK,
    SCHED_NOK,

}SCHED_ErrorStatus_t;

/* ============================================================================ */
/*                                  	PROTOTYPES				                */
/* ============================================================================ */

void SCHED_Init(void);

void SCHED_Start(void);



#endif /* OS_SCHED_H_ */
