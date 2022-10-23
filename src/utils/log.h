/**
 * @file log.h
 * @brief Simple logger.
 * 
 * @author mopsiok
 */

#ifndef LOG_H
#define LOG_H

// Includes ========================================
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Macros and defines ==============================

/* Possible log levels. */
#define LOG_LEVEL_OFF       0
#define LOG_LEVEL_ERROR     1
#define LOG_LEVEL_INFO      2
#define LOG_LEVEL_DEBUG     3

/* All log levels above this value will be omitted. */
#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_LEVEL_DEBUG
#endif

/* New line string. */
#ifndef LOG_NEW_LINE
#define LOG_NEW_LINE "\n"
#endif

/* ERROR log macros. */
#if LOG_LEVEL >= LOG_LEVEL_ERROR
#define logError(format, ...)                       __internalLog(LOG_LEVEL_ERROR, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define logErrorMemory(buffer, size, description)   __internalLogMemory(buffer, size, description)
#define logErrorString(string, description)         __internalLogString(string, description)
#else
#define logError(format, ...)                       do {} while(0);
#define logErrorMemory(buffer, size, description)   do {} while(0);
#define logErrorString(string, description)         do {} while(0);
#endif

/* INFO log macros. */
#if LOG_LEVEL >= LOG_LEVEL_INFO
#define logInfo(format, ...)                        __internalLog(LOG_LEVEL_INFO, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define logInfoMemory(buffer, size, description)    __internalLogMemory(buffer, size, description)
#define logInfoString(string, description)          __internalLogString(string, description)
#else
#define logInfo(format, ...)                        do {} while(0);
#define logInfoMemory(buffer, size, description)    do {} while(0);
#define logInfoString(string, description)          do {} while(0);
#endif

/* DEBUG log macros. */
#if LOG_LEVEL >= LOG_LEVEL_DEBUG
#define logDebug(format, ...)                       __internalLog(LOG_LEVEL_DEBUG, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define logDebugMemory(buffer, size, description)   __internalLogMemory(buffer, size, description)
#define logDebugString(string, description)         __internalLogString(string, description)
#else
#define logDebug(format, ...)                       do {} while(0);
#define logDebugMemory(buffer, size, description)   do {} while(0);
#define logDebugString(string, description)         do {} while(0);
#endif


// Typedefs ========================================

// Exported variables ==============================

// Global function prototypes ======================

/**
 * @brief Log single message in predefined format. For internal use only - use logX macros instead.
 * 
 * @param level Log level.
 * @param line Execution line number.
 * @param functionName Execution function name.
 * @param format Format of the message.
 * @param ... Optional arguments to be used while formatting.
 */
void __internalLog(int level, int line, const char * functionName, const char * format, ...);

/**
 * @brief Log memory block in hexadecimal format. For internal use only - use logXMemory macros instead.
 * 
 * @param buffer Pointer to memory block.
 * @param size Length of the block in bytes.
 * @param description Optional description, set to NULL if not used.
 */
void __internalLogMemory(const uint8_t * buffer, uint16_t size, const char * description);

/**
 * @brief Log simple string. For internal use only - use logXString macros instead.
 * 
 * @param string String to print.
 * @param description Optional description, set to NULL if not used.
 */
void __internalLogString(const char * string, const char * description);

#ifdef __cplusplus
}
#endif

#endif 
