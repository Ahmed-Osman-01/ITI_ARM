/*
 * NVIC.c
 *
 *  Created on: Mar 4, 2024
 *      Author: Osman
 */


/* ============================================================================ */
/*                                  INCLUDEDS                           	    */
/* ============================================================================ */
#include "LIB/STD_TYPES.h"
#include "stm32f401ccu.h"
#include "MCAL/NVIC/NVIC.h"


/* ============================================================================ */
/*                                   MACROS                           	        */
/* ============================================================================ */

#define SCB_AIRCR_PRIGROUP_MAX 7U


/* ---------------------------------------- */
/*                  VALIDATION              */
/* ---------------------------------------- */

#define IS_INTERRUPT_ID(ID)     ( ((ID) & NVIC_INTERRUPTS_CODE) == NVIC_INTERRUPTS_CODE )


/* ---------------------------------------- */
/*                  REGISTERS               */
/* ---------------------------------------- */
#define NVIC_BASE_ADDRESS   0xE000E100
#define NVIC                ((volatile NVIC_Registerts_t * const)NVIC_BASE_ADDRESS)

#define SCB_AIRCR       (*((volatile u32 * const)(0xE000ED0C)))

/* ---------------------------------------- */
/*                  MASKS                   */
/* ---------------------------------------- */

#define SCB_AIRCR_VECTKEY        ((u32)0x5FA << 16)
#define SCB_AIRCR_VECTKEY_MASK   ((u32)0xFFFF0000)


#define SCB_AIRCR_PRIGROUP_MASK  ((u32)0x00000700)
#define SCB_AIRCR_PRIGROUP_OFFSET  (8U)

/* ============================================================================ */
/*                                  	TYPES                           	    */
/* ============================================================================ */

typedef struct
{
    u32 ISER[8];
    u32 RESERVED0[24];
    u32 ICER[8];
    u32 RESERVED1[24];
    u32 ISPR[8];
    u32 RESERVED2[24];
    u32 ICPR[8];
    u32 RESERVED3[24];
    u32 IABR[8];
    u32 RESERVED4[56];
    // u8 IPR[60];
    u8 IP[240];
    u32 RESERVED5[644];
    u32 STIR;

}NVIC_Registerts_t; 




/* ============================================================================ */
/*                                  	GLOBAL VARIABLES                   	    */
/* ============================================================================ */

static u8 Global_SubGroupsBitsNum = NVIC_NON_IMPLEMENTED_PRIORITY_BITS;


/* ============================================================================ */
/*                                STATIC FUNCTIONS                   	        */
/* ============================================================================ */

static NVIC_ErrorStatus_t NVIC_SetBitInReg(NVIC_InterruptID_t Copy_InterruptID, volatile u32* const Add_Reg)
{
    NVIC_ErrorStatus_t Ret_ErrorStatus = NVIC_OK;
    u8 Local_RegNumber;
    u8 Local_BitNmber;
    if(!IS_INTERRUPT_ID(Copy_InterruptID))
    {
        Ret_ErrorStatus = NVIC_INVALID_INTERRUPT_ID;
    }

    if(Ret_ErrorStatus == NVIC_OK)
    {
        Local_RegNumber = Copy_InterruptID / 32;
        Local_BitNmber  = Copy_InterruptID % 32;
        Add_Reg[Local_RegNumber] = (1 << Local_BitNmber);
    }

    return Ret_ErrorStatus;
}

static NVIC_ErrorStatus_t NVIC_GetBitInReg(NVIC_InterruptID_t Copy_InterruptID, volatile u32* const Add_Reg, u8* Add_Return)
{
    NVIC_ErrorStatus_t Ret_ErrorStatus = NVIC_OK;

    u8 Local_RegNumber;
    u8 Local_BitNmber;
    if(!IS_INTERRUPT_ID(Copy_InterruptID))
    {
        Ret_ErrorStatus = NVIC_INVALID_INTERRUPT_ID;
    }

    if(Ret_ErrorStatus == NVIC_OK)
    {
        Local_RegNumber = Copy_InterruptID / 32;
        Local_BitNmber  = Copy_InterruptID % 32;
        *Add_Return = Add_Reg[Local_RegNumber] & (1 << Local_BitNmber);
    }    

    return Ret_ErrorStatus;
}




/* ============================================================================ */
/*                                  APIS IMPLEMENTATION                       	*/
/* ============================================================================ */


NVIC_ErrorStatus_t NVIC_EnableInterrupt(NVIC_InterruptID_t Copy_InterruptID)
{
    NVIC_ErrorStatus_t Ret_ErrorStatus = NVIC_OK;
    
    Ret_ErrorStatus = NVIC_SetBitInReg(Copy_InterruptID, NVIC->ISER);

    return Ret_ErrorStatus;
}

NVIC_ErrorStatus_t NVIC_DisableInterrupt(NVIC_InterruptID_t Copy_InterruptID)
{
    NVIC_ErrorStatus_t Ret_ErrorStatus = NVIC_OK;

    Ret_ErrorStatus = NVIC_SetBitInReg(Copy_InterruptID, NVIC->ICER);
    
    return Ret_ErrorStatus;
}


NVIC_ErrorStatus_t NVIC_SetPending(NVIC_InterruptID_t Copy_InterruptID)
{
    NVIC_ErrorStatus_t Ret_ErrorStatus = NVIC_OK;
    
    Ret_ErrorStatus = NVIC_SetBitInReg(Copy_InterruptID, NVIC->ISPR);

    return Ret_ErrorStatus;
}

NVIC_ErrorStatus_t NVIC_ClearPending(NVIC_InterruptID_t Copy_InterruptID)
{
    NVIC_ErrorStatus_t Ret_ErrorStatus = NVIC_OK;

    Ret_ErrorStatus = NVIC_SetBitInReg(Copy_InterruptID, NVIC->ICPR);

    return Ret_ErrorStatus;
}

NVIC_ErrorStatus_t NVIC_GetPending(NVIC_InterruptID_t Copy_InterruptID, u8 *Add_ReturnPending)
{
    NVIC_ErrorStatus_t Ret_ErrorStatus = NVIC_OK;

    Ret_ErrorStatus = NVIC_GetBitInReg(Copy_InterruptID, NVIC->ISPR, Add_ReturnPending);

    return Ret_ErrorStatus;
}

NVIC_ErrorStatus_t NVIC_GetActive(NVIC_InterruptID_t Copy_InterruptID, u8* Add_ReturnActive)
{
    NVIC_ErrorStatus_t Ret_ErrorStatus = NVIC_OK;

    Ret_ErrorStatus = NVIC_GetBitInReg(Copy_InterruptID, NVIC->IABR, Add_ReturnActive);

    return Ret_ErrorStatus;
}


NVIC_ErrorStatus_t NVIC_SetPeriority(NVIC_InterruptID_t Copy_InterruptID, u8 Copy_Periority)
{
    NVIC_ErrorStatus_t Ret_ErrorStatus = NVIC_OK;

    if(!IS_INTERRUPT_ID(Copy_InterruptID))
    {
        Ret_ErrorStatus = NVIC_INVALID_INTERRUPT_ID;
    }
    else if(Copy_Periority > NVIC_MAX_PERIORITY)
    {
        Ret_ErrorStatus = NVIC_INVALID_PERIORITY;
    }
    else
    {
        /* do nothig */
    }


    if(Ret_ErrorStatus == NVIC_OK)
    {
        NVIC->IP[Copy_InterruptID] = Copy_Periority << NVIC_NON_IMPLEMENTED_PRIORITY_BITS;
    }

    return Ret_ErrorStatus;
}

NVIC_ErrorStatus_t NVIC_GetPeriority(NVIC_InterruptID_t Copy_InterruptID, u8 *Add_Periority)
{
    NVIC_ErrorStatus_t Ret_ErrorStatus = NVIC_OK;

    if(!IS_INTERRUPT_ID(Copy_InterruptID))
    {
        Ret_ErrorStatus = NVIC_INVALID_INTERRUPT_ID;
    }
    else if(Add_Periority == NULL)
    {
        Ret_ErrorStatus = NVIC_NULL_PTR;
    }
    else
    {
        /* do nothig */
    }


    if(Ret_ErrorStatus == NVIC_OK)
    {
        *Add_Periority = NVIC->IP[Copy_InterruptID] << NVIC_NON_IMPLEMENTED_PRIORITY_BITS;
    }

    return Ret_ErrorStatus;
}


NVIC_ErrorStatus_t NVIC_EncodePeriority(NVIC_InterruptID_t Copy_InterruptID, u8 Copy_GroupPeriority, u8 Copy_SubgroupPeriority)
{
    NVIC_ErrorStatus_t Ret_ErrorStatus = NVIC_OK;

    if(!IS_INTERRUPT_ID(Copy_InterruptID))
    {
        Ret_ErrorStatus = NVIC_INVALID_INTERRUPT_ID;
    }
    
    if(Ret_ErrorStatus == NVIC_OK)
    {
        NVIC->IP[Copy_InterruptID] = (Copy_GroupPeriority << Global_SubGroupsBitsNum) | (Copy_SubgroupPeriority << NVIC_NON_IMPLEMENTED_PRIORITY_BITS);
    }

    return Ret_ErrorStatus;
}

NVIC_ErrorStatus_t NVIC_SetSubGroupsBits(u8 Copy_SubGroupsBitsNum)
{
    NVIC_ErrorStatus_t Ret_ErrorStatus = NVIC_OK;
    u32 Local_TmpReg;

    if ( Copy_SubGroupsBitsNum  > SCB_AIRCR_PRIGROUP_MAX )
    {
        Ret_ErrorStatus = NVIC_INVALID_GROUPS_NUMBER;
    }

    if(Ret_ErrorStatus == NVIC_OK)
    {
        Local_TmpReg = SCB_AIRCR;
        Local_TmpReg &= ~(SCB_AIRCR_VECTKEY_MASK | SCB_AIRCR_PRIGROUP_MASK);
        Local_TmpReg |= (SCB_AIRCR_VECTKEY) | (Copy_SubGroupsBitsNum << SCB_AIRCR_PRIGROUP_OFFSET);
        SCB_AIRCR = Local_TmpReg;

        if( (Copy_SubGroupsBitsNum + 1) > NVIC_NON_IMPLEMENTED_PRIORITY_BITS)
        {
            Global_SubGroupsBitsNum = Copy_SubGroupsBitsNum + 1;
        }
        else
        {
            Global_SubGroupsBitsNum = NVIC_NON_IMPLEMENTED_PRIORITY_BITS;
        }
    }

    return Ret_ErrorStatus;
}

NVIC_ErrorStatus_t NVIC_GetSubGroupsBits(u8 *Copy_SubGroupsBitsNum)
{
    NVIC_ErrorStatus_t Ret_ErrorStatus = NVIC_OK;

    if(Copy_SubGroupsBitsNum == NULL)
    {
        Ret_ErrorStatus = NVIC_NULL_PTR;
    }

    if(Ret_ErrorStatus == NVIC_OK)
    {
        *Copy_SubGroupsBitsNum = Global_SubGroupsBitsNum;
    }

    return Ret_ErrorStatus;
}
