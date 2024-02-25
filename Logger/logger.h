#ifndef _LOGGER_H
#define _LOGGER_H

#include <stdio.h>
#include <time.h>
#include <stdarg.h>


#define LOGGER_TRUE     1
#define LOGGER_FALSE    0

/* Available output channels */
#define LOGGER_CHANNEL_CONSOLE  10
#define LOGGER_CHANNEL_FILE     20

/* Log message levels */
typedef enum {OFF ,INFO, WARNING, ERROR, CRITICAL} Log_Level_t;


/* Struct defining the logger object so that multiple loggers
could be created each with its own configuration for more flexibility */
typedef struct
{
    char log_to_console;
    char log_to_file;
    FILE* log_file;
    Log_Level_t log_level;

}Logger_t;


/**
 * @brief Initializes the logger object to default values to avoid
 * problems with using the logger
 * 
 * @param logger Pointer to the logger obejct
 */
void LOGGER_Init(Logger_t* logger);

/**
 * @brief Sets the output channel for logging
 * Currently available channels are:
 *  - LOGGER_CHANNEL_CONSOLE
 *  - LOGGER_CHANNEL_FILE
 * The order of output channels doesn't matter
 * 
 * @param logger Pointer to the logger object
 * @param channel_count Number of channels to log into
 * @param ... Desired output channels in any order
 */
void LOGGER_SetChannel(Logger_t* logger ,int channel_count, ...);

/**
 * @brief Configures the file to log into 
 * 
 * @param logger Pointer to the logger object
 * @param file_path Path to the log file
 * 
 * @note The path can be relative path
 * @note The file will be created if it doesn't exist
 * @note If it failes to open or create a file, log_to_file will be set to FALSE
 */
void LOGGER_FileCfg(Logger_t* logger ,const char * file_path);


/**
 * @brief Logs the formated string with given level into the log channels configured in the 
 * given logger
 * 
 * @param logger Pointer to the logger object where output channels and level filtere are configured 
 * @param level Level of the log message (INFO, WARRNING, ERROR, CRITICAL)
 * @param str Formatted string to log
 * @param ... Arguments the formatted string uses ( just like printf() )
 * 
 * @note Recommended to call LOGGER_Init(Logger_object) first 
 * @note The logger object needs to be configured first 
 * @note Level filter must be configured in the logger object before using this function
 * @note Output channels must be configured in the logger object before using this function
 * @note File path must be configured if file is choosen as one of the output channels
 */
void LOGGER_write(Logger_t* logger, Log_Level_t level ,const char * str, ...);

#endif