#include "logger.h"


#define CONSOLE_LOG_MESSAGE()       printf("%-12s: ", level_text) && \
                                    vprintf(str, args_copy) &&\
                                    printf("\n")\
                            

#define FILE_LOG_MESSAGE()          fprintf(logger->log_file, "%-12s:",level_text) &&\
                                    vfprintf(logger->log_file ,str, args_copy) &&\
                                    fprintf(logger->log_file, "\n") 


void LOGGER_Init(Logger_t* logger)
{
    logger->log_to_console = LOGGER_TRUE;
    logger->log_to_file = LOGGER_FALSE;
    logger->log_file = NULL;
    logger->log_level = OFF;

}

void LOGGER_SetChannel(Logger_t* logger, int channel_count, ...)
{
    va_list args;
    int i;
    va_start( args, channel_count);

    for(i = 0; i < channel_count; i++)
    {
        switch(va_arg(args, int))
        {
            case LOGGER_CHANNEL_CONSOLE:
                logger->log_to_console = LOGGER_TRUE;
            break;

            case LOGGER_CHANNEL_FILE:
                logger->log_to_file = LOGGER_TRUE;
            break;
        }
    }

    va_end(args);
}


void LOGGER_FileCfg(Logger_t* logger, const char * file_path)
{
    logger->log_file = fopen(file_path, "w");
    if(logger->log_file == NULL)
    {
        printf("FAILED TO OPEN LOG FILE !!!\n");
        logger->log_to_file = LOGGER_FALSE;
    }
}

void LOGGER_write(Logger_t* logger, Log_Level_t level ,const char * str, ...)
{
    va_list args;
    va_start(args, str);

    /* Make a copy of arguments list to send to vprintf() and vfprintf() */
    va_list args_copy;
    va_copy(args_copy, args);

    if( (level != OFF) && (level >= (logger->log_level) ) )
    {
        /* Get the time and formate it in desired formate */
        time_t raw_time = time(NULL);
        struct tm* local = localtime(&raw_time);
        char formatted_time[80];
        strftime(formatted_time, sizeof(formatted_time), "%a %b %d %H:%M:%S %Y", local);
        
        /* Add the time stamp the the beginning of the log message */
        logger->log_to_console ? printf("[%s] ", formatted_time) : 0;
        logger->log_to_file ? fprintf(logger->log_file ,"[%s] ", formatted_time) : 0;

        char * level_text;

        switch(level)
        {
        
            case INFO:
                level_text = "[INFO]";
                break;

            case WARNING:
                level_text = "[WARNING]";
                break;

            case ERROR:
                level_text = "[ERROR]";
                break;

            case CRITICAL:
                level_text = "[CRITICAL]";
                break;

            default:
                break;
        }/* end of level switch */

        logger->log_to_console ? CONSOLE_LOG_MESSAGE() : 0;
        logger->log_to_file ? FILE_LOG_MESSAGE() : 0;
        

    }/* end if level if */

   
    va_end(args_copy);
    va_end(args);
}