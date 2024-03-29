/*
 * SCHED.h
 *
 *  Created on: Mar 11, 2024
 *      Author: Osman
 */

#ifndef OS_SCHED_H_
#define OS_SCHED_H_


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
    const Runnable_t * runnable;
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


/**
 * @brief Initializes the Schedular According to the Runnables configured in SCHED_config.h and SCHED_config.c
 * 
 * @note ```Pre-Condition``` Configure the Runnables in SHCED_config.h and SCHED_config.c
 * 
 */
void SCHED_Init(void);


/**
 * @brief Starts the Schedular
 * 
 * @note ```Pre-Condition``` SCHED_Init() must be called first
 * 
 */
void SCHED_Start(void);



#endif /* OS_SCHED_H_ */
