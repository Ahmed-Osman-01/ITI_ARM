/*
 * stm32f401ccu.h
 *
 *  Created on: Mar 4, 2024
 *      Author: Osman
 */

#ifndef MCAL_NVIC_STM32F401CCU_INTERRUPTS_H_
#define MCAL_NVIC_STM32F401CCU_INTERRUPTS_H_

/* ==============================================================================*/
/*                                INTERRUPTS                                     */
/* ==============================================================================*/

#define NVIC_NON_IMPLEMENTED_PRIORITY_BITS   4U
#define NVIC_MAX_NUMBER_OF_SUB_GROUPS     15U
#define NVIC_MAX_PERIORITY    15U

#define  NVIC_INTERRUPTS_CODE         (u64)0xF00000000

typedef enum
{
   NVIC_WWDG = (u64)0 + NVIC_INTERRUPTS_CODE,
   NVIC_EXTI16,
   NVIC_EXTI21,
   NVIC_EXTI22,
   NVIC_FLASH,
   NVIC_RCC,
   NVIC_EXTI0, 
   NVIC_EXTI1, 
   NVIC_EXTI2, 
   NVIC_EXTI3, 
   NVIC_EXTI4,
   NVIC_DMA1_Stream0, 
   NVIC_DMA1_Stream1, 
   NVIC_DMA1_Stream2, 
   NVIC_DMA1_Stream3,
   NVIC_DMA1_Stream4,
   NVIC_DMA1_Stream5,
   NVIC_DMA1_Stream6,
   NVIC_ADC,
   NVIC_EXTI9_5 = (u64)23 + NVIC_INTERRUPTS_CODE,
   NVIC_TIM1_BRK_TIM9,
   NVIC_TIM1_UP_TIM10,
   NVIC_TIM1_TRG_COM_TIM11,
   NVIC_TIM1_CC,
   NVIC_TIM2,
   NVIC_TIM3,
   NVIC_TIM4,
   NVIC_I2C1_EV,
   NVIC_I2C1_ER,
   NVIC_I2C2_EV,
   NVIC_I2C2_ER,
   NVIC_SPI1,
   NVIC_SPI2,
   NVIC_USART1,
   NVIC_USART2,
   NVIC_EXTI15_10 = (u64)40 + NVIC_INTERRUPTS_CODE,
   NVIC_EXTI17_RTC_ALARM,
   NVIC_EXTI18_OTG_FS_WKUP,
   NVIC_DMA1_Stream7 = (u64)47 + NVIC_INTERRUPTS_CODE,
   NVIC_SDIO = (u64)49 + NVIC_INTERRUPTS_CODE,
   NVIC_TIM5,
   NVIC_SPI3,
   NVIC_DMA2_Stream0 = (u64)56 + NVIC_INTERRUPTS_CODE,
   NVIC_DMA2_Stream1,
   NVIC_DMA2_Stream2,
   NVIC_DMA2_Stream3,
   NVIC_DMA2_Stream4,
   NVIC_OTG_FS = (u64)67 + NVIC_INTERRUPTS_CODE,
   NVIC_DMA2_Stream5,
   NVIC_DMA2_Stream6,
   NVIC_DMA2_Stream7,
   NVIC_USART6,
   NVIC_I2C3_EV,
   NVIC_I2C_ER,
   NVIC_FPU = (u64)81 + NVIC_INTERRUPTS_CODE,
   NVIC_SPI4 = (u64)84 + NVIC_INTERRUPTS_CODE,

}NVIC_InterruptID_t;



#endif /* MCAL_NVIC_STM32F401CCU_INTERRUPTS_H_ */
