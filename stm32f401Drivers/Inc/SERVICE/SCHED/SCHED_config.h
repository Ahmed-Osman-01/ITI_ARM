/*
 * SCHED_config.h
 *
 *  Created on: Mar 11, 2024
 *      Author: Osman
 */

#ifndef OS_SCHED_CONFIG_H_
#define OS_SCHED_CONFIG_H_


/* Add or remove Runnables here for each runnable object added to the config array in config.c */
typedef enum
{
    LCD,
    BLINKING_LED,
    LCD_APP,
	LCD_CLEAR,

    /* Dont' remove this or add any runnable after it */
    _NUM_RUNNABLE,
}RunnabaleID_t;


/* Configure tick period to be equal to or less than the period of the smallest period in all runnables */
#define SCHED_TICK_PERIOD_MS      2

#endif /* OS_SCHED_CONFIG_H_ */
