/*
 * LCD.c
 *
 *  Created on: Mar 22, 2024
 *      Author: Osman
 */


/* ============================================================================ */
/*                                  INCLUDEDS                           	    */
/* ============================================================================ */

#include "LIB/STD_TYPES.h"
#include "MCAL/GPIO/GPIO.h"
#include "HAL/LCD/LCD_priv.h"
#include "HAL/LCD/LCD.h"
#include "HAL/LCD/LCD_config.h"


/* ============================================================================ */
/*                                   MACROS                             	    */
/* ============================================================================ */

/* helping macros to concat the LCD configurations into their macros */
#define CONCAT_H(d7,d6,d5,d4,d3,d2,d1,d0)       0b##d7##d6##d5##d4##d3##d2##d1##d0
#define CONCAT(d7,d6,d5,d4,d3,d2,d1,d0)         CONCAT_H(d7,d6,d5,d4,d3,d2,d1,d0)


#define LCD_DISPLAY_CONTROL     CONCAT(0,0,0,0,1,LCD_DISPLAY,LCD_CURSER,LCD_BLINKING)
#define LCD_ENTRY_MODE          CONCAT(0,0,0,0,0,1,LCD_INCREMENT_DECREMENT,LCD_SHIFTING)

#define LCD_CLEAR_DISPLAY               0x01    /* Clear display command */
#define LCD_SET_DDR_ADDRESS            0X80    /* Set pos of DDR command */

#if LCD_MODE == LCD_8_BIT_MODE
#define FUNCTION_SET        CONCAT(0,0,1,1,LCD_LINES_NUMBER,LCD_FORMAT,0,0)
#define LCD_PINS_NUM        8

#elif LCD_MODE == LCD_4_BIT_MODE
#define FUNCTION_SET        CONCAT(0,0,1,0,LCD_LINES_NUMBER,LCD_FORMAT,0,0)
#define LCD_PINS_NUM        4

#endif

#define ENABLE_PIN_LOW      0U
#define ENABLE_PIN_HIGH     1U


#define HIGH_NIBBLE     4U
#define LOW_NIBBLE      0U

#if LCD_MODE == LCD_8_BIT_MODE
#define LATCH_TARGET_COUNT    2U        /* Number of times latch needs to be called */
#elif LCD_MODE == LCD_4_BIT_MODE
#define LATCH_TARGET_COUNT    4U        /* Number of times latch needs to be called */
#endif




/* ============================================================================ */
/*                                  	TYPES                           	    */
/* ============================================================================ */

typedef void (*LCDCallBack)(void);

/* stores the state of a user request.
    Available types are:
        - WRITE_STRING
        - CLEAR_SCREEN
        - SET_POS 
    If state is busy, that means a process is currently being handled and
    can't accept new requests*/
typedef struct
{
    u8 type;
    u8 state;
    LCDCallBack cb;

}LCD_Request_t;

/* Stores the string to be printed information */
typedef struct
{
    const u8 * string;
    u8 length;
    u8 currIndex;
}LCD_StringRequest_t;

/* Cursor position */
typedef struct
{
    u8 row;
    u8 col;
}LCD_Pos_t;

/* States of the LCD */
typedef enum {LCD_OFF, LCD_INIT, LCD_OPERATION}LCD_State_t;


/* Init Process states */
#if LCD_MODE == LCD_8_BIT_MODE
typedef enum {
    POWER_ON_STATE,
    FUNCTIONAL_SET_STATE,
    DISPLAY_CTRL_STATE,
    CLEAR_DISPLAY_STATE,
    ENTRY_MODE_STATE,
    END_STATE
}LCD_Init_States_t;

#elif LCD_MODE == LCD_4_BIT_MODE
typedef enum {
    POWER_ON_STATE,
    PRE_FUNCTIONAL_SET_STATE,
    FUNCTIONAL_SET_STATE,
    DISPLAY_CTRL_STATE,
    CLEAR_DISPLAY_STATE,
    ENTRY_MODE_STATE,
    END_STATE
}LCD_Init_States_t;
#endif

/* Request states */
typedef enum
{
    AVAILABLE,
    BUSY,
}LDC_RequestStates_t;

/* User Request types */
typedef enum
{
    NONE,
    WRITE_STRING,
    CLEAR_SCREEN,
    SET_CURSOR_POS,
}LCD_RequestTypes_t;

/* ============================================================================ */
/*                                  	EXTERNS                           	    */
/* ============================================================================ */

/* LCD Pins array */
extern const LCD_Pin_t LCD_Pins[LCD_PINS_NUM];

/* ============================================================================ */
/*                                  GLOBAL VARIABLES                    	    */
/* ============================================================================ */


static LCD_State_t G_LCDState = LCD_OFF;        /* States of LCD */

static LCD_Request_t G_Request;                 
static LCD_StringRequest_t G_StringReq;         /* Info of the string request */
static LCD_Pos_t G_Pos;


static u8 G_OperationLatchCount;       /* counter used by operation requests to check if number of latches required is reached */

static u8 G_CharCount;              /* Number of characters written on the LCD */

/* ============================================================================ */
/*                                  STATIC FUNCTIONS                           	*/
/* ============================================================================ */

/**
 * @brief Hanldes the writing of LCD pins, also enabling and disabling the latch.
 * It also handles the case of 8-bit mode and 4-bit mode
 * 
 * @param byte The byte to be written on LCD pins
 */
static void Latch(u8 byte)
{
    #if LCD_MODE == LCD_4_BIT_MODE
    static u8 currNibble = HIGH_NIBBLE;
    #endif

    static u8 EnablePinState = ENABLE_PIN_LOW;      /* State of the Enable Pin */
    u8 iter;

    if(EnablePinState == ENABLE_PIN_LOW)
    {
        for(iter = 0; iter < LCD_PINS_NUM; iter++)
        {
            /* set the lcd pin state with the value corresponding to the bit in the sent byte */

            #if LCD_MODE == LCD_8_BIT_MODE
            GPIO_SetPinState( LCD_Pins[iter].Port, LCD_Pins[iter].Pin, (byte >> iter)&1 );
            #elif LCD_MODE == LCD_4_BIT_MODE
            GPIO_SetPinState( LCD_Pins[iter].Port, LCD_Pins[iter].Pin, (byte >> (iter+currNibble))&1 );
            #endif

        }

        EnablePinState = ENABLE_PIN_HIGH;
    }
    else
    {
        EnablePinState = ENABLE_PIN_LOW;

        #if LCD_MODE == LCD_4_BIT_MODE
        /* Change the Nibble to be latched to the opposite Nibble
            Since in 4-bit mode, the high nibble is handled first then
            low nibble, then each time a nibble is latched we need to change
            the nibble to be latched to the opposite nibble */
        currNibble = (currNibble == HIGH_NIBBLE)? LOW_NIBBLE : HIGH_NIBBLE;
        #endif
    }
    GPIO_SetPinState(LCD_PORT_E, LCD_PIN_E, EnablePinState);
}


static void WriteCommand(u8 command)
{
    GPIO_SetPinState(LCD_PORT_RS, LCD_PIN_RS, 0);   
    GPIO_SetPinState(LCD_PORT_RW, LCD_PIN_RW, 0);   
    Latch(command);
}


static void WriteData(u8 data)
{

    GPIO_SetPinState(LCD_PORT_RS, LCD_PIN_RS, 1);   
    GPIO_SetPinState(LCD_PORT_RW, LCD_PIN_RW, 0); 

    Latch(data);
}


#if LCD_MODE == LCD_8_BIT_MODE

static void InitProcess(void)
{
    static LCD_Init_States_t InitState = POWER_ON_STATE;
    static u8 counter = 0;

    switch(InitState)
    {
        case POWER_ON_STATE:
            /* Delay for 30 ms */
            counter += LCD_UPDATE_PERIODICITY_MS;

            if(counter >= 30)
            {
                /* Move to next state if dealy reaches 30ms */
                counter = 0;
                InitState = FUNCTIONAL_SET_STATE;
            }
            break;

        case FUNCTIONAL_SET_STATE:
            counter++;
            if(counter == LATCH_TARGET_COUNT)
            {
                counter = 0;
                InitState = DISPLAY_CTRL_STATE;
            }
            WriteCommand(FUNCTION_SET);
            break;

        case DISPLAY_CTRL_STATE:
            counter++;
            if(counter == LATCH_TARGET_COUNT)
            {
                counter = 0;
                InitState = CLEAR_DISPLAY_STATE;
            }
            WriteCommand(LCD_DISPLAY_CONTROL);
            break;

        case CLEAR_DISPLAY_STATE:
            counter++;
            if(counter == LATCH_TARGET_COUNT)
            {
                counter = 0;
                InitState = ENTRY_MODE_STATE;
            }
            WriteCommand(LCD_CLEAR_DISPLAY);
            break;
                    
        case ENTRY_MODE_STATE:
            counter++;
            if(counter == LATCH_TARGET_COUNT)
            {
                counter = 0;
                InitState = END_STATE;
            }
            WriteCommand(LCD_ENTRY_MODE);
            break;

        case END_STATE:
            G_LCDState = LCD_OPERATION;
            break;
        
        default:
            break;
    }
}

#elif LCD_MODE == LCD_4_BIT_MODE

static void InitProcess(void)
{
    static LCD_Init_States_t InitState = POWER_ON_STATE;
    static u8 counter = 0;

    switch(InitState)
    {
        case POWER_ON_STATE:
            /* Delay for 30 ms */
            counter += LCD_UPDATE_PERIODICITY_MS;

            if(counter >= 30)
            {
                /* Move to next state if dealy reaches 30ms */
                counter = 0;
                InitState = PRE_FUNCTIONAL_SET_STATE;
            }
            break;

        /* The first latch in the Functional Set step as it needs to be done manually */
        case PRE_FUNCTIONAL_SET_STATE:
            counter++;
            if(counter == 1)
            {
                GPIO_SetPinState(LCD_Pins[0].Port, LCD_Pins[0].Pin, GPIO_STATE_LOW);
                GPIO_SetPinState(LCD_Pins[1].Port, LCD_Pins[1].Pin, GPIO_STATE_HIGH);
                GPIO_SetPinState(LCD_Pins[2].Port, LCD_Pins[2].Pin, GPIO_STATE_LOW);
                GPIO_SetPinState(LCD_Pins[3].Port, LCD_Pins[3].Pin, GPIO_STATE_LOW);

                GPIO_SetPinState(LCD_PORT_E, LCD_PIN_E, GPIO_STATE_HIGH);

            }
            else if(counter == 2)
            {
                GPIO_SetPinState(LCD_PORT_E, LCD_PIN_E, GPIO_STATE_LOW);

                counter = 0;
                InitState = FUNCTIONAL_SET_STATE;
            }
            break;

        case FUNCTIONAL_SET_STATE:
            counter++;
            if(counter == LATCH_TARGET_COUNT)
            {
                counter = 0;
                InitState = DISPLAY_CTRL_STATE;
            }
            WriteCommand(FUNCTION_SET);
            break;

        case DISPLAY_CTRL_STATE:
            counter++;
            if(counter == LATCH_TARGET_COUNT)
            {
                counter = 0;
                InitState = CLEAR_DISPLAY_STATE;
            }
            WriteCommand(LCD_DISPLAY_CONTROL);
            break;

        case CLEAR_DISPLAY_STATE:
            counter++;
            if(counter == LATCH_TARGET_COUNT)
            {
                counter = 0;
                InitState = ENTRY_MODE_STATE;
            }
            WriteCommand(LCD_CLEAR_DISPLAY);
            break;
                    
        case ENTRY_MODE_STATE:
            counter++;
            if(counter == LATCH_TARGET_COUNT)
            {
                counter = 0;
                InitState = END_STATE;
            }
            WriteCommand(LCD_ENTRY_MODE);
            break;

        case END_STATE:
            G_LCDState = LCD_OPERATION;
            break;
        
        default:
            break;
    }
}


#endif




/* static void WriteString(void)
{
    static u8 posLatchCount = 0;
    static u8 changeRow = 0;

    if(G_StringReq.string[G_StringReq.currIndex] != '\0')
    {

        if(G_CharCount == 16 && changeRow == 0)
        {
            G_Pos.col = 0;
            G_Pos.row = 1;

            changeRow = 1;
             
        }
        else if(G_CharCount == 32 && changeRow == 0)
        {
            G_Pos.col = 0;
            G_Pos.row = 0;  

            changeRow = 1;
        }
        else if(changeRow == 1 && G_CharCount == 16)
        {
            posLatchCount++;
            if(posLatchCount == LATCH_TARGET_COUNT)
            {
                posLatchCount = 0;
                changeRow = 0;
            }
            WriteCommand(LCD_SET_DDR_ADDRESS); 
        }
        else if(changeRow == 1 && G_CharCount == 32)
        {
            posLatchCount++;
            if(posLatchCount == LATCH_TARGET_COUNT)
            {
                posLatchCount = 0;
                changeRow = 0;
                G_CharCount = 0;
            }
            WriteCommand(LCD_SET_DDR_ADDRESS + 0x40);
        }
        else
        {
            WriteData(G_StringReq.string[G_StringReq.currIndex]);
            G_OperationLatchCount++;

            if(G_OperationLatchCount == LATCH_TARGET_COUNT)
            {
                G_StringReq.currIndex++;
                G_OperationLatchCount = 0;

                G_CharCount++;
            }
        }
        
    }
    else
    {
        G_Request.state = AVAILABLE;
        G_Request.type = NONE;

        // G_StringReq.currIndex = 0;  //---------------------->>>
        // G_StringReq.string = NULL;  //---------------------->>>
    }
} */


/* Iterates through the string and prints each character */
static void WriteString(void)
{

    if(G_StringReq.string[G_StringReq.currIndex] != '\0')
    {
        WriteData(G_StringReq.string[G_StringReq.currIndex]);
        G_OperationLatchCount++;

        if(G_OperationLatchCount == LATCH_TARGET_COUNT)
        {
            G_StringReq.currIndex++;
            G_OperationLatchCount = 0;

            G_CharCount++;
        }     
    }
    else
    {
        G_Request.state = AVAILABLE;
        G_Request.type = NONE;

    }
}

static void ClearScreen(void)
{
    if(G_OperationLatchCount == LATCH_TARGET_COUNT)
    {
        G_OperationLatchCount = 0;

        G_Request.state = AVAILABLE;
        G_Request.type = NONE;
    }
    else
    {
        WriteCommand(LCD_CLEAR_DISPLAY);
        G_OperationLatchCount++;
    }

}

static void SetCursorPos(void)
{

    if(G_OperationLatchCount == LATCH_TARGET_COUNT)
    {
        G_OperationLatchCount = 0;

        G_Request.state = AVAILABLE;
        G_Request.type = NONE;
    }
    else
    {
        if(G_Pos.row == 0)
        {
            WriteCommand(LCD_SET_DDR_ADDRESS + G_Pos.col);
        }
        else if (G_Pos.row == 1)
        {
            WriteCommand(LCD_SET_DDR_ADDRESS + (G_Pos.col + 0x40) );
        }

        G_OperationLatchCount++;

    }

}


/* If the LCD finished Initialization and is in Operation mode */
static void OperationProcess(void)
{
    if(G_Request.type == WRITE_STRING)
    {
        WriteString();
    }
    else if(G_Request.type == CLEAR_SCREEN)
    {
        ClearScreen();
    }
    else if(G_Request.type == SET_CURSOR_POS)
    {
        SetCursorPos();
    }
}

/* ============================================================================ */
/*                                 IMPLEMENTATION                           	*/
/* ============================================================================ */

/* The runnable of LCD */
void LCD_Update(void)
{
    if(G_LCDState == LCD_INIT)
    {
        InitProcess();
    }
    else if(G_LCDState == LCD_OPERATION)
    {
        OperationProcess();
    }
    else
    {
        /* do nothing */
    }
}


LCD_ErrorStatus_t LCD_Init(void)
{
    LCD_ErrorStatus_t Ret_ErrorStatus = LCD_OK;
    u8 iter;
    GPIO_Pin_t lcdPin;
    lcdPin.Mode = GPIO_MODE_OP_PP;
    lcdPin.AF = GPIO_AF_SYSTEM;
    lcdPin.Speed = GPIO_SPEED_HIGH;

    /* Initialize the LCD pins */
    for(iter = 0; iter < LCD_PINS_NUM; iter++)
    {
        lcdPin.Pin = LCD_Pins[iter].Pin;
        lcdPin.Port = LCD_Pins[iter].Port;

        GPIO_Init(&lcdPin);
    }

    lcdPin.Pin = LCD_PIN_RS;
    lcdPin.Port = LCD_PORT_RS;
    GPIO_Init(&lcdPin);

    lcdPin.Pin = LCD_PIN_RW;
    lcdPin.Port = LCD_PORT_RW;
    GPIO_Init(&lcdPin);

    lcdPin.Pin = LCD_PIN_E;
    lcdPin.Port = LCD_PORT_E;
    GPIO_Init(&lcdPin);


    /* Change LCD state from OFF to Init */
    G_LCDState = LCD_INIT;

    return Ret_ErrorStatus;
}

LCD_ErrorStatus_t LCD_WriteStringAsync(const u8 * string)
{
    LCD_ErrorStatus_t Ret_ErrorStatus = LCD_OK;

    if(string == NULL)
    {
        Ret_ErrorStatus = LCD_NOK;
    }
    else
    {
        if(G_Request.state == AVAILABLE)
        {
            G_Request.state = BUSY;
            G_Request.type = WRITE_STRING;

            G_StringReq.string = string;
            G_StringReq.currIndex = 0;
        }
    }

    return Ret_ErrorStatus;
}


LCD_ErrorStatus_t LCD_ClearScreenAsync(void)
{
    if(G_Request.state == AVAILABLE)
    {
        G_Request.state = BUSY;
        G_Request.type = CLEAR_SCREEN;
    }
    
    return 0;
}


LCD_ErrorStatus_t LCD_SetCursorPosAsync(u8 row, u8 col)
{
    if(G_Request.state == AVAILABLE)
    {
        G_Request.state = BUSY;
        G_Request.type = SET_CURSOR_POS;

        G_Pos.row = row;
        G_Pos.col = col;

        if(G_Pos.row == 0)
        {
            G_CharCount = G_Pos.col;
        }
        else if(G_Pos.row == 1)
        {
           G_CharCount = G_Pos.col+16; 
        }

    }

    return 0;
}
