/*
 * GPIO.c
 *
 *  Created on: Feb 13, 2024
 *      Author: Osman
 */

#include "LIB/STD_TYPES.h"
#include "MCAL/GPIO/GPIO.h"


#define GPIO_MODE_MASK      0x00000003
#define GPIO_OTYPE_MASK     0x00000004
#define GPIO_PUPD_MASK      0x00000018
#define GPIO_CLEAR_MASK     0x00000003
#define GPIO_PIN_OFFSET_2   0x00000002

#define GPIOA_BASE_ADDRESS  0x40020000
#define GPIOB_BASE_ADDRESS  0x40020400
#define GPIOC_BASE_ADDRESS  0x40020800

typedef struct
{
    u32 MODER;
    u32 OTYPER;
    u32 OSPEEDR;
    u32 PUPDR;
    u32 IDR;
    u32 ODR;
    u32 BSRR;
    u32 LCKR;
    u32 AFRL;
    u32 AFRH;

}GPIO_Registers_t;

static volatile GPIO_Registers_t * const GPIOs[3] = {GPIOA_BASE_ADDRESS, GPIOB_BASE_ADDRESS,GPIOC_BASE_ADDRESS};




GPIO_ErrorStatus_t GPIO_Init(GPIO_Pin_t* ADD_Config)
{
    GPIO_ErrorStatus_t Ret_ErrorStatus = GPIO_OK;

    u32 Local_TmpReg = GPIOs[ADD_Config->Port]->MODER;
    Local_TmpReg &= ~( GPIO_CLEAR_MASK << (ADD_Config->Pin * GPIO_PIN_OFFSET_2)) ;
    Local_TmpReg |= ( (ADD_Config->Mode & GPIO_MODE_MASK) << (ADD_Config->Pin * GPIO_PIN_OFFSET_2) );
    GPIOs[ADD_Config->Port]->MODER = Local_TmpReg;

    Local_TmpReg = GPIOs[ADD_Config->Port]->OTYPER;
    Local_TmpReg &= ~ ( ( GPIO_CLEAR_MASK)<< (ADD_Config->Pin) );
    Local_TmpReg |= ( (ADD_Config->Mode & GPIO_OTYPE_MASK) << (ADD_Config->Pin) );
    GPIOs[ADD_Config->Port]->OTYPER = Local_TmpReg;

    Local_TmpReg = GPIOs[ADD_Config->Port]->PUPDR;
    Local_TmpReg &= ~( (GPIO_CLEAR_MASK)<< (ADD_Config->Pin*2) );
    Local_TmpReg |= ( (ADD_Config->Mode & GPIO_PUPD_MASK) << (ADD_Config->Pin * GPIO_PIN_OFFSET_2) );
    GPIOs[ADD_Config->Port]->PUPDR = Local_TmpReg;

    Local_TmpReg = GPIOs[ADD_Config->Port]->OSPEEDR;
    Local_TmpReg &= ~( (GPIO_CLEAR_MASK)<< (ADD_Config->Pin*2) );
    Local_TmpReg |= ( (ADD_Config->Speed) << (ADD_Config->Pin * GPIO_PIN_OFFSET_2) );
    GPIOs[ADD_Config->Port]->OSPEEDR = Local_TmpReg;

    return Ret_ErrorStatus;
}