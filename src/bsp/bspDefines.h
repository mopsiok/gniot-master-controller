/**
 * @file bspDefines.h
 * @brief BSP-related types
 * 
 * @author mopsiok
 */

#ifndef BSP_DEFINES_H
#define BSP_DEFINES_H

// Includes ========================================
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// Macros and defines ==============================

// Typedefs ========================================

/* Peripheral handler types */
typedef unsigned int BspGpioHandler;
typedef unsigned int BspPwmHandler;

/* GPIO configuration */
typedef enum
{
    GPIO_4 = 4,
    GPIO_17 = 17,
} BspGpioPin;

typedef enum
{
    GPIO_MODE_INPUT = 0,
    GPIO_MODE_OUTPUT = 1,
    // GPIO_MODE_ALT0 = 4,
    // GPIO_MODE_ALT1 = 5,
    // GPIO_MODE_ALT2 = 6,
    // GPIO_MODE_ALT3 = 7,
    // GPIO_MODE_ALT4 = 3,
    // GPIO_MODE_ALT5 = 2,
} BspGpioMode;

typedef enum
{
    GPIO_PULL_OFF = 0,
    GPIO_PULL_DOWN = 1,
    GPIO_PULL_UP = 2,
} BspGpioPull;

typedef struct
{
    BspGpioPin pin;
    BspGpioMode mode;
    BspGpioPull pull;
    bool defaultState;
} BspGpioConfig;

/* PWM configuration */
typedef struct
{
    BspGpioPin pin;
    unsigned int frequency;
    unsigned int range;
    unsigned int defaultValue;
} BspPwmConfig;

/* SPI configuration */

// Exported variables ==============================

// Global function prototypes ======================


#ifdef __cplusplus
}
#endif

#endif
