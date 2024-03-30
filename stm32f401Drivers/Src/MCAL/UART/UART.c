/*
 * UART.c
 *
 *  Created on: Mar 26, 2024
 *      Author: Osman
 */


/* ============================================================================ */
/*                                  INCLUDEDS                           	    */
/* ============================================================================ */

#include "LIB/STD_TYPES.h"
#include "MCAL/UART/UART.h"


/* ============================================================================ */
/*                                   MACROS                             	    */
/* ============================================================================ */


#define _UARTS_NUM  3               /* Number of available uarts */
#define _CLK_FREQ   25000000UL      /* Frequency of the cpu clock */

#define TXE_TIMEOUT_VAL     600     /* Timeout count in cast of Synchronous Transfere of a byte */
#define RXE_TIMEOUT_VAL     600     /* Timeout count in cast of Synchronous Recieve of a byte */


#define MANTISSA_POS    4U          /* Position of the mantissa part in the BRR */

#define READY   0U
#define BUSY    1U

#define UART1_INDEX     0
#define UART2_INDEX     1
#define UART6_INDEX     2


/* ------------------------------------- */
/*                  MASKS                */
/* ------------------------------------- */

#define UART_RE_MASK        ((u32)(1 << 2))
#define UART_TE_MASK        ((u32)(1 << 3))
#define UART_MODE_MASK      ((u32)(3 << 2))
#define UART_RXNEIE_MASK    ((u32)(1 << 5))
#define UART_TXEIE_MASK     ((u32)(1 << 7))
#define UART_PARITY_MASK    ((u32)(3 << 9))
#define UART_LENGTH_MASK    ((u32)(1 << 12))
#define UART_UE_MASK        ((u32)(1 << 13))
#define UART_SAMPLING_MASK  ((u32)(1 << 15))

#define UART_TXE_MASK   ((u32)(1 << 7))
#define UART_RXNE_MASK  ((u32)(1 << 5))

/* ------------------------------------- */
/*                  VALIDATIONS          */
/* ------------------------------------- */

#define IS_VALID_MODE(MODE)   ((MODE) == (UART_MODE_TX)||\
                               (MODE) == (UART_MODE_RX)||\
                               (MODE) == (UART_MODE_TX_RX))

#define IS_VALID_BAUDRATE(BR)  ((BR) < 1000000U)

#define IS_VALID_PARITY(PARITY)  ((PARITY) == UART_PARITY_DISABLE||\
                                  (PARITY) == UART_PARITY_ENABLE_EVEN||\
                                  (PARITY) == UART_PARITY_ENABLE_ODD)


#define IS_VALID_LENGTH(LENGTH)     ((LENGTH) == UART_WORDLENGTH_8||\
                                     (LENGTH) == UART_WORDLENGTH_9)

#define IS_VALID_UART(UART)         ((UART) == UART1||\
                                     (UART) == UART2||\
                                     (UART) == UART6)

#define IS_VALID_SAMPLING(SAMPLING) ((SAMPLING) == UART_SAMPLING_8 || (SAMPLING) == UART_SAMPLING_16)



/* ============================================================================ */
/*                                  	TYPES                           	    */
/* ============================================================================ */

typedef struct
{
    u32 SR;
    u32 DR;
    u32 BRR;
    u32 CR1;
    u32 CR2;
    u32 CR3;
    u32 GTPR;

}UART_Registers_t;


typedef struct
{
    u8 * Data;
    u16 Length;
    u16 CurrIdx;

}UART_Buffer_t;


typedef struct
{
    UART_Buffer_t Buffer;
    u8 State;
    UART_ReqCallback_t Cb;

}UART_Req_t;




/* ============================================================================ */
/*                                  GLOBAL VARIABLES                    	    */
/* ============================================================================ */


static UART_Registers_t* UARTs[_UARTS_NUM] = {(UART_Registers_t*)0x40011000, (UART_Registers_t*)0x40004400,
											  (UART_Registers_t*)0x40011400};

static UART_Req_t TXRequests[_UARTS_NUM];
static UART_Req_t RXRequests[_UARTS_NUM];


/* ============================================================================ */
/*                                  IMPLEMENTATION                           	*/
/* ============================================================================ */


UART_ErrorStatus_t  UART_SetConfig(u8 uartID, UART_Config_t* config)
{
    UART_ErrorStatus_t Ret_ErrorStatus = UART_OK;
    u32 tmpReg;
    u32 uartdiv;
    u8 mantissa;
    u32 fraction;

    if(!IS_VALID_UART(uartID))
    {
        Ret_ErrorStatus = UART_INVALID_UART;
    }
    else if(!IS_VALID_BAUDRATE(config->BaudRate))
    {
        Ret_ErrorStatus = UART_INVALID_BAUDRATE;
    }
    else if(!IS_VALID_LENGTH(config->WordLength))
    {
        Ret_ErrorStatus = UART_INVALID_WORD_LENGTH;
    }
    else if(!IS_VALID_MODE(config->Mode))
    {
        Ret_ErrorStatus = UART_INVALID_MODE;
    }
    else if(!IS_VALID_PARITY(config->Parity))
    {
        Ret_ErrorStatus = UART_INVALID_PARITY;
    }
    else if(!IS_VALID_SAMPLING(config->Sampling))
    {
        Ret_ErrorStatus = UART_INVALID_SAMPLING;
    }
    else
    {
        /* do nothing */
    }


    if(Ret_ErrorStatus == UART_OK)
    {
        tmpReg = UARTs[uartID]->CR1;
        tmpReg &= (~UART_MODE_MASK) | (~UART_RXNEIE_MASK) | (~UART_TXEIE_MASK) | (~UART_PARITY_MASK)|\
                    (~UART_LENGTH_MASK) | (~UART_SAMPLING_MASK);
        tmpReg |= (config->Mode) | (config->Parity) | (config->WordLength) | (config->Sampling) | (UART_UE_MASK);
        UARTs[uartID]->CR1 = tmpReg;

        /* Calculate Mantissa and Fraction for BaudRate*/

        uartdiv = ((u64)_CLK_FREQ * 1000)/((2-(UARTs[uartID]->CR1 & UART_SAMPLING_MASK)) * 8 * config->BaudRate);

        mantissa = uartdiv/1000;

        fraction = (uartdiv % 1000) * ((2-(UARTs[uartID]->CR1 & UART_SAMPLING_MASK)) * 8);
        

        if(fraction % 1000 >= 500)
        {
            fraction = (fraction/1000) + 1 ;          
        }
        else
        {
            fraction = fraction/1000;
        }

        if( ((UARTs[uartID]->CR1 & UART_SAMPLING_MASK) == UART_SAMPLING_16) && (fraction > 15) )
        {
            fraction = 0;
            mantissa++;
        }

        if( ((UARTs[uartID]->CR1 & UART_SAMPLING_MASK) == UART_SAMPLING_8) && (fraction > 7) )
        {
            fraction = 0;
            mantissa++;
        }

        UARTs[uartID]->BRR = (mantissa << MANTISSA_POS) | fraction;

    }

    return Ret_ErrorStatus;
}


UART_ErrorStatus_t UART_TXByte(u8 uartID, u8 byte)
{
    UART_ErrorStatus_t Ret_ErrorStatus = UART_OK;
    u16 timeout = TXE_TIMEOUT_VAL;

    if(!IS_VALID_UART(uartID))
    {
        Ret_ErrorStatus = UART_INVALID_UART;
    }
    else
    {
        /* do nothing */
    }

    if(Ret_ErrorStatus == UART_OK)
    {
        /* Disable TXE Interrupt */
        UARTs[uartID]->CR1 &= ~UART_TXEIE_MASK;
        /* Send the Byte */
        UARTs[uartID]->DR = byte;
        /* Wait till Byte is sent */
        while( ((UARTs[uartID]->SR & UART_TXE_MASK) == 0) && timeout )
        {
            timeout--;
        }

        if( (timeout == 0) && ((UARTs[uartID]->SR & UART_TXE_MASK) == 0))
        {
            Ret_ErrorStatus = UART_TX_TIMEOUT;
        }
    }

    return Ret_ErrorStatus;
}


UART_ErrorStatus_t UART_TXBufferAsyncZC(u8 uartID, u8 * buffer, u16 length, UART_ReqCallback_t cb )
{
    UART_ErrorStatus_t Ret_ErrorStatus = UART_OK;

    if(!IS_VALID_UART(uartID))
    {
        Ret_ErrorStatus = UART_INVALID_UART;
    }
    else if(buffer == NULL || cb == NULL)
    {
        Ret_ErrorStatus = UART_NULL_PTR;
    }
    else
    {
        /* do nothing */
    }

    if(Ret_ErrorStatus == UART_OK)
    {
       
        if(TXRequests[uartID].State == READY)
        {
            TXRequests[uartID].State = BUSY;
            TXRequests[uartID].Cb = cb;

            TXRequests[uartID].Buffer.Data = buffer;
            TXRequests[uartID].Buffer.Length = length;

            /* Send the firts byte to start the chain */
            TXRequests[uartID].Buffer.CurrIdx = 1;
            UARTs[uartID]->DR = TXRequests[uartID].Buffer.Data[0];

            /* Enable TXE interrupt */
            UARTs[uartID]->CR1 |= UART_TXEIE_MASK;
        }
    }

    return Ret_ErrorStatus;
}


UART_ErrorStatus_t UART_RXByte(u8 uartID, u8 *byte)
{
    UART_ErrorStatus_t Ret_ErrorStatus = UART_OK;
    u16 timeout = RXE_TIMEOUT_VAL;

    if(!IS_VALID_UART(uartID))
    {
        Ret_ErrorStatus = UART_INVALID_UART;
    }
    else if(byte == NULL)
    {
        Ret_ErrorStatus = UART_NULL_PTR;
    }
    else
    {
        /* do nothing */
    }

    if(Ret_ErrorStatus == UART_OK)
    {
        /* Disable RXNE Interrupt */
        UARTs[uartID]->CR1 &= ~UART_RXNEIE_MASK;

        /* Wait till Byte is recieved */
        while( ((UARTs[uartID]->SR & UART_TXE_MASK) == 0) && timeout )
        {
            timeout--;
        }

        if( (timeout == 0) && ((UARTs[uartID]->SR & UART_TXE_MASK) == 0))
        {
            Ret_ErrorStatus = UART_RX_TIMEOUT;
        }
        else
        {
            /* Get value if no timeout */
            *byte = UARTs[uartID]->DR;
        }

    }

    return Ret_ErrorStatus;
}


UART_ErrorStatus_t UART_RXBufferAsyncZC(u8 uartID, u8 * buffer, u16 length, UART_ReqCallback_t cb )
{
    UART_ErrorStatus_t Ret_ErrorStatus = UART_OK;

    if(!IS_VALID_UART(uartID))
    {
        Ret_ErrorStatus = UART_INVALID_UART;
    }
    else if(buffer == NULL || cb == NULL)
    {
        Ret_ErrorStatus = UART_NULL_PTR;
    }
    else
    {
        /* do nothing */
    }


     if(Ret_ErrorStatus == UART_OK)
    {
        if(RXRequests[uartID].State == READY)
        {
            RXRequests[uartID].State = BUSY;
            RXRequests[uartID].Cb = cb;

            RXRequests[uartID].Buffer.Data = buffer;
            RXRequests[uartID].Buffer.Length = length;

            RXRequests[uartID].Buffer.CurrIdx = 0;

            /* Clear RXNE flag */
            UARTs[uartID]->SR &= ~UART_RXNE_MASK;

            /* Enable RXNE interrupt */
            UARTs[uartID]->CR1 |= UART_RXNEIE_MASK;

        }
    }

    return Ret_ErrorStatus;
}



void USART1_IRQHandler(void)
{
    if(UARTs[UART1]->SR & UART_TXE_MASK)
    {
        if(TXRequests[UART1_INDEX].Buffer.CurrIdx < TXRequests[UART1_INDEX].Buffer.Length)
        {
            UARTs[UART1]->DR = TXRequests[UART1_INDEX].Buffer.Data[TXRequests[UART1_INDEX].Buffer.CurrIdx];
            TXRequests[UART1_INDEX].Buffer.CurrIdx++;
        }
        else
        {
            TXRequests[UART1_INDEX].State = READY;
            /* DISABLE TXE interrupt */
            UARTs[UART1]->CR1 &= ~UART_TXEIE_MASK;

            TXRequests[UART1_INDEX].Cb();
        }
    }

    if(UARTs[UART1]->SR & UART_RXNE_MASK)
    {
        if(RXRequests[UART1_INDEX].Buffer.CurrIdx < RXRequests[UART1_INDEX].Buffer.Length)
        {
            RXRequests[UART1_INDEX].Buffer.Data[RXRequests[UART1_INDEX].Buffer.CurrIdx] = UARTs[UART1]->DR;
            RXRequests[UART1_INDEX].Buffer.CurrIdx++;

            if(RXRequests[UART1_INDEX].Buffer.CurrIdx == RXRequests[UART1_INDEX].Buffer.Length)
            {
                RXRequests[UART1_INDEX].State = READY;
                /* DISABLE RXE interrupt */
                UARTs[UART1]->CR1 &= ~UART_RXNEIE_MASK;

                RXRequests[UART1_INDEX].Cb();
            }

        }    
    }
} 


void USART2_IRQHandler(void)
{
    if(UARTs[UART2]->SR & UART_TXE_MASK)
    {
        if(TXRequests[UART2_INDEX].Buffer.CurrIdx < TXRequests[UART2_INDEX].Buffer.Length)
        {
            UARTs[UART2]->DR = TXRequests[UART2_INDEX].Buffer.Data[TXRequests[UART2_INDEX].Buffer.CurrIdx];
            TXRequests[UART2_INDEX].Buffer.CurrIdx++;
        }
        else
        {
            TXRequests[UART2_INDEX].State = READY;
            /* DISABLE TXE interrupt */
            UARTs[UART2]->CR1 &= ~UART_TXEIE_MASK;

            TXRequests[UART2_INDEX].Cb();
        }
    }

    if(UARTs[UART2]->SR & UART_RXNE_MASK)
    {
        if(RXRequests[UART2_INDEX].Buffer.CurrIdx < RXRequests[UART2_INDEX].Buffer.Length)
        {
            RXRequests[UART2_INDEX].Buffer.Data[RXRequests[UART2_INDEX].Buffer.CurrIdx] = UARTs[UART2]->DR;
            RXRequests[UART2_INDEX].Buffer.CurrIdx++;

            if(RXRequests[UART2_INDEX].Buffer.CurrIdx == RXRequests[UART2_INDEX].Buffer.Length)
            {
                RXRequests[UART2_INDEX].State = READY;
                /* DISABLE RXE interrupt */
                UARTs[UART2]->CR1 &= ~UART_RXNEIE_MASK;

                RXRequests[UART2_INDEX].Cb();
            }

        }    
    }
} 


void USART6_IRQHandler(void)
{
    if(UARTs[UART6]->SR & UART_TXE_MASK)
    {
        if(TXRequests[UART6_INDEX].Buffer.CurrIdx < TXRequests[UART6_INDEX].Buffer.Length)
        {
            UARTs[UART6]->DR = TXRequests[UART6_INDEX].Buffer.Data[TXRequests[UART6_INDEX].Buffer.CurrIdx];
            TXRequests[UART6_INDEX].Buffer.CurrIdx++;
        }
        else
        {
            TXRequests[UART6_INDEX].State = READY;
            /* DISABLE TXE interrupt */
            UARTs[UART6]->CR1 &= ~UART_TXEIE_MASK;

            TXRequests[UART6_INDEX].Cb();
        }
    }

    if(UARTs[UART6]->SR & UART_RXNE_MASK)
    {
        if(RXRequests[UART6_INDEX].Buffer.CurrIdx < RXRequests[UART6_INDEX].Buffer.Length)
        {
            RXRequests[UART6_INDEX].Buffer.Data[RXRequests[UART6_INDEX].Buffer.CurrIdx] = UARTs[UART6]->DR;
            RXRequests[UART6_INDEX].Buffer.CurrIdx++;

            if(RXRequests[UART6_INDEX].Buffer.CurrIdx == RXRequests[UART6_INDEX].Buffer.Length)
            {
                RXRequests[UART6_INDEX].State = READY;
                /* DISABLE TXE interrupt */
                UARTs[UART6]->CR1 &= ~UART_RXNEIE_MASK;

                RXRequests[UART6_INDEX].Cb();
            }

        }    
    }
} 
