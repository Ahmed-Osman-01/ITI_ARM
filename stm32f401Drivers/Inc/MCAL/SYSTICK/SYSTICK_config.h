/*
 * SYSTICK_config.h
 *
 *  Created on: Mar 11, 2024
 *      Author: Osman
 */

#ifndef MCAL_SYSTICK_SYSTICK_CONFIG_H_
#define MCAL_SYSTICK_SYSTICK_CONFIG_H_

/* Configure the Processor clock speed in HZ */
#define SYSTICK_PROCESSOR_CLOCK     25000000


/* Configure the External refrence clock speed in HZ if it exists */
#define SYSTICK_EXTERNAL_CLOCK      3125000  /* AHB/8 */

#endif /* MCAL_SYSTICK_SYSTICK_CONFIG_H_ */
