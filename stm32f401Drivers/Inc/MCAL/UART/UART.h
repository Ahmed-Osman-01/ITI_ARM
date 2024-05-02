/*
 * UART.h
 *
 *  Created on: Mar 26, 2024
 *      Author: Osman
 */

#ifndef MCAL_UART_UART_H_
#define MCAL_UART_UART_H_



/* ============================================================================ */
/*                                  MACROS                                 	    */
/* ============================================================================ */

/* ------------------------------------------------ */
/*              Configuration Options               */
/* ------------------------------------------------ */
#define UART_WORDLENGTH_8               (u32)(0 << 12)
#define UART_WORDLENGTH_9               (u32)(1 << 12)

#define UART_PARITY_DISABLE         (u32)(0 << 10)
#define UART_PARITY_ENABLE_EVEN     (u32)( (1 << 10) | (0 << 9))
#define UART_PARITY_ENABLE_ODD      (u32)( (1 << 10) | (1 << 9))

#define UART_MODE_TX                (u32)(1 << 3)
#define UART_MODE_RX                (u32)(1 << 2)
#define UART_MODE_TX_RX             (u32)((1 << 3) | (1 << 2))

#define UART_SAMPLING_16            (u32)(0 << 15)
#define UART_SAMPLING_8             (u32)(1 << 15)

#define UART_LIN_ENABLED             (u32)(1 << 14)
#define UART_LIN_DISABLED            (u32)(0 << 14)

#define UART_LIN_BREAK_DETECTION_10     (u32)(0 << 5)
#define UART_LIN_BREAK_DETECTION_11     (u32)(1 << 5)

#define UART_LIN_BREAK_INTERRUPT_DISABLED    (u32)(0 << 6)
#define UART_LIN_BREAK_INTERRUPT_ENABLED     (u32)(1 << 6)

#define UART_LIN_SEND_BREAK     (u32)(1 << 0)

/* ------------------------------------------------ */
/*              Available UARTs                     */
/* ------------------------------------------------ */
#define UART1         0U
#define UART2         1U
#define UART6         2U

/* ============================================================================ */
/*                                  	TYPES                           	    */
/* ============================================================================ */

typedef void (*UART_ReqCallback_t) (void);

typedef void (*UART_LBDCallback_t) (void);  /* LIN Break Detection Callback */

/**
 * @brief UART configuraiton struct 
 * 
 * 
 * @note ```Baudrate```: The baudrate (must be within the limits of the uart)
 * @note ```WordLength```: UART_WORDLENGTH_8 or UART_WORDLENGTH_9
 * @note ```Parity```: UART_PARITY_DISABLE , UART_PARITY_ENABLE_EVEN or UART_PARITY_ENABLE_ODD
 * @note ```Mode```: UART_MODE_TX , UART_MODE_RX or UART_MODE_TX_RX
 * @note ```Sampling```: UART_SAMPLING_16 or UART_SAMPLING_8
 * 
 */
typedef struct
{
    u32 BaudRate;
    u32 WordLength;
    u32 Parity;
    u32 Mode;
    u32 Sampling;
}UART_Config_t;


/**
 * @brief LIN configuraiton struct 
 * 
 * 
 * @note ```State```: UART_LIN_ENABLED or UART_LIN_DISABLED
 * @note ```BreakDetectLength```: UART_LIN_BREAK_DETECTION_10 or UART_LIN_BREAK_DETECTION_11
 * @note ```BreakDetectInterrupt```: UART_LIN_BREAK_INTERRUPT_ENABLED or UART_LIN_BREAK_INTERRUPT_DISABLED
 * 
 */
typedef struct
{
    u32 State;
    u32 BreakDetectLength;
    u32 BreakDetectInterrupt;
}UART_LIN_Config_t;


typedef enum
{
    UART_OK,
    UART_NOK,
    UART_INVALID_UART,
    UART_INVALID_BAUDRATE,
    UART_INVALID_WORD_LENGTH,
    UART_INVALID_MODE,
    UART_INVALID_PARITY,
    UART_INVALID_SAMPLING,
    UART_NULL_PTR,
    UART_TX_TIMEOUT,
    UART_RX_TIMEOUT,

}UART_ErrorStatus_t;



/* ============================================================================ */
/*                                  	PROTOTYPES				                */
/* ============================================================================ */

/**
 * @brief Configures the Given UART according to the given configuration struct
 * 
 * @param UARTx The Uart to configure
 * @param config Configuration Struct
 * @return UART_ErrorStatus_t 
 */
UART_ErrorStatus_t  UART_SetConfig(u8 UARTx, UART_Config_t* config);


/**
 * @brief Sends a Byte over the given UART Synchronously
 * 
 * @param UARTx The UART to send the byte over
 * @param byte Byte to Send
 * @return UART_ErrorStatus_t 
 */
UART_ErrorStatus_t UART_TXByte(u8 UARTx, u8 byte);


/**
 * @brief Sends a buffer of data Asynchronously over the given uart then calls the given Callback function after
 * the transfere is completed
 * 
 * @param UARTx UART to send the buffer over
 * @param buffer Buffer of data to send
 * @param length Length of the buffer
 * @param cb Function to call after the transfere is completed
 * @return UART_ErrorStatus_t 
 */
UART_ErrorStatus_t UART_TXBufferAsyncZC(u8  UARTx, u8 * buffer, u16 length, UART_ReqCallback_t cb );


/**
 * @brief Receivess a Byte over the given UART Synchronously
 * 
 * @param UARTx The UART to receive the byte over
 * @param byte Received byte
 * @return UART_ErrorStatus_t 
 */
UART_ErrorStatus_t UART_RXByte(u8 UARTx, u8 *byte);


/**
 * @brief Receivess a buffer of data Asynchronously over the given uart then calls the given Callback function after
 * the buffer is full (aka the buffer received)
 * 
 * @param UARTx UART to receive the buffer over
 * @param buffer Buffer of data to receive
 * @param length Length of the buffer
 * @param cb Function to call after the buffer is filled (Received the buffer)
 * @return UART_ErrorStatus_t 
 */
UART_ErrorStatus_t UART_RXBufferAsyncZC(u8 UARTx, u8 * buffer, u16 length, UART_ReqCallback_t cb );



/* ================================================================= */
/*                        LIN RELATED APIS                           */
/* ================================================================= */


/**
 * @brief Configures the LIN in the specified UART
 * 
 * @param UARTx UART1, UART2 or UART6
 * @param Config Pointer to configuration struct
 * @return UART_ErrorStatus_t 
 */
UART_ErrorStatus_t UART_ConfigLIN(u8 UARTx, UART_LIN_Config_t* Config);



/**
 * @brief Sends a Break Sequence over the TX (13 0's)
 * 
 * @param UARTx UART1, UART2 or UART6
 * @return UART_ErrorStatus_t 
 */
UART_ErrorStatus_t UART_SendBreak(u8 UARTx);


/**
 * @brief Sets the callback function to call when LBD Interrupt happens
 * 
 * @param UARTx UART1, UART2 or UART6
 * @param cb The callback function
 * @return UART_ErrorStatus_t 
 */
UART_ErrorStatus_t UART_SetLBDCallback(u8 UARTx, UART_LBDCallback_t cb);

#endif /* MCAL_UART_UART_H_ */
