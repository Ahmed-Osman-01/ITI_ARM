/*
 * NVIC.h
 *
 *  Created on: Mar 4, 2024
 *      Author: Osman
 */

#ifndef MCAL_NVIC_NVIC_H_
#define MCAL_NVIC_NVIC_H_


/* ============================================================================ */
/*                                  INCLUDEDS                           	    */
/* ============================================================================ */

#include "stm32f401ccu.h"

/* ============================================================================ */
/*                                   MACROS                           	        */
/* ============================================================================ */

#define NVIC_INT_ACTIVE         1U
#define NVIC_INT_NOT_ACTIVE     0U

#define NVIC_INT_PENDING        1U
#define NVIC_INT_NOT_PENDING    0U

/* Macros to use as parameter with NVIC_SetSubGroupsBits() API */
#define NVIC_SUB_GROUP_ONE_BITS     0U
#define NVIC_SUB_GROUP_TWO_BITS     1U
#define NVIC_SUB_GROUP_THREE_BITS   2U
#define NVIC_SUB_GROUP_FOUR_BITS    3U
#define NVIC_SUB_GROUP_FIVE_BITS    4U
#define NVIC_SUB_GROUP_SIX_BITS     5U
#define NVIC_SUB_GROUP_SEVEN_BITS   6U
#define NVIC_SUB_GROUP_EIGHT_BITS   7U

/* ============================================================================ */
/*                                  	TYPES                           	    */
/* ============================================================================ */

typedef enum
{
    NVIC_OK,
    NVIC_NOK,
    NVIC_INVALID_INTERRUPT_ID,
    NVIC_INVALID_GROUPS_NUMBER,
    NVIC_INVALID_PERIORITY,
    NVIC_NULL_PTR,
    NVIC_GROUP_PRIORITY_OUT_OF_RANGE,
    
}NVIC_ErrorStatus_t;

/* ============================================================================ */
/*                                  	PROTOTYPES				                */
/* ============================================================================ */


/**
 * @brief Enables the given interrupt
 * 
 * @param Copy_InterruptID Interrupt ID to enable
 * @return NVIC_ErrorStatus_t Module error status
 */
NVIC_ErrorStatus_t NVIC_EnableInterrupt(NVIC_InterruptID_t Copy_InterruptID);


/**
 * @brief Disables the given interrupt
 * 
 * @param Copy_InterruptID Interrupt ID to enable
 * @return NVIC_ErrorStatus_t Module error status
 */
NVIC_ErrorStatus_t NVIC_DisableInterrupt(NVIC_InterruptID_t Copy_InterruptID);


/**
 * @brief Sets the pending state for the given interrupt
 * 
 * @param Copy_InterruptID Interrupt ID to set its pending
 * @return NVIC_ErrorStatus_t Module error status
 */
NVIC_ErrorStatus_t NVIC_SetPending(NVIC_InterruptID_t Copy_InterruptID);


/**
 * @brief Clears the pending state for the given interrupt
 * 
 * @param Copy_InterruptID Interrupt ID to clear its pending
 * @return NVIC_ErrorStatus_t Module error status
 */
NVIC_ErrorStatus_t NVIC_ClearPending(NVIC_InterruptID_t Copy_InterruptID);


/**
 * @brief Returns wether the given interrupt is pending or not
 * 
 * @param Copy_InterruptID Interrupt ID to check its pending
 * @param Add_ReturnPending Returned pending state
 * @return NVIC_ErrorStatus_t Module error status
 */
NVIC_ErrorStatus_t NVIC_GetPending(NVIC_InterruptID_t Copy_InterruptID, u8 *Add_ReturnPending);


/**
 * @brief Returns wether the given interrupt is active or not
 * 
 * @param Copy_InterruptID Interrupt ID to check its active state
 * @param Add_ReturnPending Returned active state
 * @return NVIC_ErrorStatus_t Module error status
 */
NVIC_ErrorStatus_t NVIC_GetActive(NVIC_InterruptID_t Copy_InterruptID, u8* Add_ReturnActive);


/**
 * @brief Sets the priority for the given interrupt
 * 
 * @param Copy_InterruptID Interrupt ID to set its periority
 * @param Copy_Periority The periority value
 * @return NVIC_ErrorStatus_t Module error status
 */
NVIC_ErrorStatus_t NVIC_SetPeriority(NVIC_InterruptID_t Copy_InterruptID, u8 Copy_Periority);


/**
 * @brief Gets the priority for the given interrupt
 * 
 * @param Copy_InterruptID Interrupt ID to get its periority
 * @param Copy_Periority The returned periority value
 * @return NVIC_ErrorStatus_t Module error status
 */
NVIC_ErrorStatus_t NVIC_GetPeriority(NVIC_InterruptID_t Copy_InterruptID, u8 *Copy_Periority);


/**
 * @brief Sets the group and subgroup periority for the given interrupt
 * 
 * @param Copy_InterruptID Interrupt ID
 * @param Copy_GroupPeriority Group (Preemption) periority value
 * @param Copy_SubgroupPeriority Sub-group priority value
 * @return NVIC_ErrorStatus_t Module error status
 * 
 */
NVIC_ErrorStatus_t NVIC_EncodePeriority(NVIC_InterruptID_t Copy_InterruptID, u8 Copy_GroupPeriority, u8 Copy_SubgroupPeriority);


/**
 * @brief Sets the number of sub-group bits that determines the available number of group and sub-group levels
 * 
 * @param Copy_SubGroupsBitsNum Number of sub-group bits
 * 
 * @return NVIC_ErrorStatus_t Module error status
 * 
 * @note When using this function keep in mind that there might be some un-implemented bits in the periority registers
 * @note use values NVIC_SUB_GROUP_ONE_BITS to NVIC_SUB_GROUP_EIGHT_BITS 
 */
NVIC_ErrorStatus_t NVIC_SetSubGroupsBits(u8 Copy_SubGroupsBitsNum);


/**
 * @brief Returns the number of sub-group bits
 * 
 * @param Copy_NumOfGroups Returned number of sub-group bits
 * @return NVIC_ErrorStatus_t Module error status
 */
NVIC_ErrorStatus_t NVIC_GetSubGroupsBits(u8 *Copy_NumOfGroups);





#endif /* MCAL_NVIC_NVIC_H_ */
