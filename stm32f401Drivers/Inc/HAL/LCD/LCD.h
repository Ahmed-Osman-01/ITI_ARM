/*
 * LCD.h
 *
 *  Created on: Mar 22, 2024
 *      Author: Osman
 */

#ifndef HAL_LCD_LCD_H_
#define HAL_LCD_LCD_H_


/* ============================================================================ */
/*                                  	TYPES                           	    */
/* ============================================================================ */


/**
 * Struct defining the LCD pins where:
 *  - Port -> is the GPIO port it's connected to
 *  - Pin -> the GPIO pin it's connected to
 * 
 */
typedef struct
{
    void * Port;
    u8 Pin;

}LCD_Pin_t;


/**
 * LCD Error status
 */
typedef enum
{
    LCD_OK,
    LCD_NOK,
}LCD_ErrorStatus_t;


/* ============================================================================ */
/*                                  	APIS    				                */
/* ============================================================================ */

/**
 * @brief Initializes The LCD Pins and starts the Initialization sequence
 * 
 * @return LCD_ErrorStatus_t 
 */
LCD_ErrorStatus_t LCD_Init(void);


/**
 * @brief  Prints a string on the LCD
 * 
 * @param string String to print
 * @return LCD_ErrorStatus_t 
 */
LCD_ErrorStatus_t LCD_WriteStringAsync(const u8 * string);


/**
 * @brief Clears the LCD and returns the cursor back to zero position
 * 
 * @return LCD_ErrorStatus_t 
 */
LCD_ErrorStatus_t LCD_ClearScreenAsync(void);


/**
 * @brief Sets the cursor position to the given Row and Col
 * 
 * @param row 0 for the first row or 1 for second row
 * @param col 0 to 16
 * @return LCD_ErrorStatus_t 
 */
LCD_ErrorStatus_t LCD_SetCursorPosAsync(u8 row, u8 col);

#endif /* HAL_LCD_LCD_H_ */
