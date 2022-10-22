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
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// Macros and defines ==============================

// Typedefs ========================================

/* Helper types */
typedef unsigned int BspGpioPin;
typedef unsigned int BspGpioHandler;
typedef unsigned int BspPwmHandler;

/* GPIO configuration */
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
    BspGpioPin gpio;
    BspGpioMode mode;
    BspGpioPull pull;
    bool defaultState;
} BspGpioConfig;

/* PWM configuration */
typedef struct
{
    BspGpioPin gpio;
    unsigned int frequency;
    unsigned int range;
    unsigned int defaultValue;
} BspPwmConfig;

/* SPI configuration */
typedef enum
{
    BSP_SPI_TYPE_MAIN = 0,  /* MISO=9,  MOSI=10, SCLK=11, CE0=8,  CE1=7,  CE2=-  */
    BSP_SPI_TYPE_AUX = 1,   /* MISO=19, MOSI=20, SCLK=21, CE0=18, CE1=17, CE2=16 */
} BspSpiType;

typedef enum
{
    BSP_SPI_MODE_POL0_PHA0 = 0b00,
    BSP_SPI_MODE_POL0_PHA1 = 0b01,
    BSP_SPI_MODE_POL1_PHA0 = 0b10,
    BSP_SPI_MODE_POL1_PHA1 = 0b11,
} BspSpiMode;

typedef struct
{
    unsigned int handler;
    uint8_t * txBuffer;
    uint8_t * rxBuffer;
    uint32_t maxBufferSize;
} BspSpiHandler;

typedef struct
{
    BspSpiType type;                /* SPI type, main or auxiliary */
    uint8_t channel;                /* 0..2, CE pin to use, 2 is for AUX only */
    uint32_t baudrate;              /* baudrate, >32kHz and <30MHz */
    uint8_t * txBuffer;             /* pointer to allocated transmit buffer, NULL if not used */
    uint8_t * rxBuffer;             /* pointer to allocated receive buffer, NULL if not used */
    uint32_t maxBufferSize;         /* buffer(s) length in bytes */
    BspSpiMode mode;                /* polarity and phase, for AUX SPI only 0 and 2 are working*/
    bool csActiveState[3];          /* given CE pin is active high (true) or low (false) */
    bool csEnabled[3];              /* given CE pin is enabled (true) or disabled (false) */
    bool mainHalfDuplex;            /* 3-wire (true) or 4-wire (false); Main SPI only */
    uint8_t mainHalfDuplexLen;      /* 0..15, for mainHalfDuplex only; number of bytes to write before switching to read mode */
    bool auxTxLsbFirst;             /* LSB transmitted first (true) or MSB first (false) - AUX SPI only*/
    bool auxRxLsbFirst;             /* LSB received first (true) or MSB first (false) - AUX SPI only*/
    uint8_t auxWordSize;            /* 0..32, word size in bits - AUX SPI only */
} BspSpiConfig;

// Exported variables ==============================

// Global function prototypes ======================


#ifdef __cplusplus
}
#endif

#endif
