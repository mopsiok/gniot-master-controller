/**
 * @file log.c
 * @brief Simple logger.
 * 
 * @author mopsiok
 */

// Includes ========================================
#include "log.h"

#if LOG_LEVEL > LOG_LEVEL_OFF
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

// Private macros and defines ======================

// Private typedefs ================================

// Static variables ================================
static const char levelDescriptionError[]   = "ERROR";
static const char levelDescriptionInfo[]    = "INFO ";
static const char levelDescriptionDebug[]   = "DEBUG";
static const char levelDescriptionUnknown[] = "  ?  ";

static const char rawDataIndentation[]      = "                             ";

// Global and extern variables =====================

// Static function prototypes ======================
/**
 * @brief Printing optional description.
 * 
 * @param description Use NULL if not used.
 */
static void printOptionalDescription(const char * description);

/**
 * @brief Convert log level to its text description.
 * 
 * @param level Log level.
 * @return const char* String associated with given log level.
 */
static const char * getLogLevelDescription(int level);

// Static functions ================================
static void printOptionalDescription(const char * description)
{
    if (description)
    {
        printf(description);
        printf(": ");
    }
}

static const char * getLogLevelDescription(int level)
{
    switch (level)
    {
        case LOG_LEVEL_ERROR:
        {
            return levelDescriptionError;
        }
        case LOG_LEVEL_INFO:
        {
            return levelDescriptionInfo;
        }
        case LOG_LEVEL_DEBUG:
        {
            return levelDescriptionDebug;
        }
        default:
        {
            return levelDescriptionUnknown;
        }
    }
}

// Global functions ================================

void __internalLog(int level, int line, const char * functionName, const char * format, ...)
{
    const char *levelDescription = getLogLevelDescription(level);
    printf("%s |%4d:%-15s| ", levelDescription, line, functionName);

    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);

    printf(LOG_NEW_LINE);
}

void __internalLogMemory(const uint8_t * buffer, uint16_t size, const char * description)
{
    printf(rawDataIndentation);
    printOptionalDescription(description);
    for (uint16_t index = 0; index < size; index++)
    {
        printf("%02x ", buffer[index]);
    }
    printf(LOG_NEW_LINE);
}

void __internalLogString(const char * string, const char * description)
{
    printf(rawDataIndentation);
    printOptionalDescription(description);
    printf(string);
    printf(LOG_NEW_LINE);
}

#else
void __internalLog(int level, int line, const char * functionName, const char * format, ...)
{
    (void)level;
    (void*)line;
    (void*)format;
}

void __internalLogMemory(const uint8_t * buffer, uint16_t size, const char * description)
{
    (void*)buffer;
    (void)size;
    (void*)description;
}

void __internalLogString(const char * string, const char * description)
{
    (void*)string;
    (void*)description;
}
#endif


