/*
 * LIN_HW.h
 *
 *  Created on: Apr 2, 2024
 *      Author: Osman
 * 
 *  A Separate HW Layer to Handle different used hardwares without the need to change anything in the LIN
 *  upper layer
 */

#ifndef COMM_LIN_LIN_HW_H_
#define COMM_LIN_LIN_HW_H_



/* ============================================================================ */
/*                                  	PROTOTYPES				                */
/* ============================================================================ */


/* Initializes the used hardware (SCI and GPIO if used) according to the configurations in LIN_HW_config.h and LIN_config.h */
void LIN_HW_Init(void);

#endif /* COMM_LIN_LIN_HW_H_ */
