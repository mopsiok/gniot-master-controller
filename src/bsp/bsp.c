/**
 * @file bsp.c
 * @brief BSP wrapper
 * 
 * @author mopsiok
 */

// Includes ========================================
#include <pigpio.h>
#include <assert.h>
#include <stdio.h> //TODO debug module

#include "bsp.h"

// Private macros and defines ======================
#define SPI_CONFIG_MODE_POS 0UL
#define SPI_CONFIG_CS_POL_POS 2UL
#define SPI_CONFIG_HW_CS_POS 5UL
#define SPI_CONFIG_TYPE_POS 8UL
#define SPI_CONFIG_HALFDUPLEX_POS 9UL
#define SPI_CONFIG_HALFDUPLEX_BYTES_POS 10UL
#define SPI_CONFIG_LSB_TX_POS 14UL
#define SPI_CONFIG_LSB_RX_POS 15UL
#define SPI_CONFIG_WORDSIZE_POS 16UL

#define SPI_CONFIG_MODE_MASK 0b11UL
#define SPI_CONFIG_HALFDUPLEX_BYTES_MASK 0b1111UL
#define SPI_CONFIG_WORDSIZE_MASK 0b111111UL


// Private typedefs ================================

// Static variables ================================

// Global and extern variables =====================

// Static function prototypes ======================

/**
 * @brief Initial check of SPI handler structure, executed before each transaction.
 * 
 * @param handler SPI handler.
 * @param count number of bytes to transmit/receive.
 * @param checkTxBuffer check whether TX buffer is not NULL (mandatory for write transactions)
 * @param checkRxBuffer check whether RX buffer is not NULL (mandatory for read transactions)
 */
void bspSpiValidateHandler(BspSpiHandler * handler, uint32_t count, bool checkTxBuffer, bool checkRxBuffer);

// Static functions ================================

void bspSpiValidateHandler(BspSpiHandler * handler, uint32_t count, bool checkTxBuffer, bool checkRxBuffer)
{
    assert((NULL != handler) /* handler is NULL */ );
    assert((count <= handler->maxBufferSize) /* buffers are too small */ );
    if (checkTxBuffer)
    {
        assert((NULL != handler->txBuffer) /* TX buffer is NULL */ );
    }
    if (checkRxBuffer)
    {
        assert((NULL != handler->rxBuffer) /* RX buffer is NULL */ );
    }
}

// Global functions ================================

/* ================================================================================= */
/*                              BSP initialization                                   */
/* ================================================================================= */

void bspInit(void)
{
    int result = gpioInitialise();
    assert(result >= 0 && "pigpio initialization failed");
}


void bspDeinit(void)
{
    gpioTerminate();
}

/* ================================================================================= */
/*                                    GPIO                                           */
/* ================================================================================= */

BspGpioHandler bspGpioConfig(BspGpioConfig * config)
{
    assert(NULL != config && "wrong input parameters");
    
    gpioSetMode(config->gpio, config->mode);
    gpioSetPullUpDown(config->gpio, config->pull);

    bspGpioSetState(config->gpio, config->defaultState);
    return config->gpio;
}

bool bspGpioGetState(BspGpioHandler handler)
{
    return (bool)gpioRead(handler);
}

void bspGpioSetState(BspGpioHandler handler, bool state)
{
    gpioWrite(handler, state ? 1 : 0);
}

void bspGpioToggleState(BspGpioHandler handler)
{
    bspGpioSetState(handler, !bspGpioGetState(handler));
}

/* ================================================================================= */
/*                                    PWM                                            */
/* ================================================================================= */

BspPwmHandler bspPwmConfig(BspPwmConfig * config)
{
    assert(NULL != config && "wrong input parameters");

    gpioPWM(config->gpio, 0);
    gpioSetPWMrange(config->gpio, config->range);
    gpioSetPWMfrequency(config->gpio, config->frequency);
    gpioPWM(config->gpio, config->defaultValue);

    unsigned int realRange = gpioGetPWMrealRange(config->gpio);
    printf("real range: %d\n", realRange); //TODO debug module
    assert(realRange == config->range && "PWM range mismatch, check configuration");

    return (BspPwmHandler)(config->gpio);
}

void bspPwmSetValue(BspPwmHandler handler, unsigned int value)
{
    gpioPWM(handler, value);
}

/* ================================================================================= */
/*                                    SPI                                            */
/* ================================================================================= */

void bspSpiConfig(BspSpiConfig * config, BspSpiHandler * result)
{
    assert(((NULL != config) || (NULL != result)) && "wrong input parameters");

    uint32_t flags = 0;
    flags |= (config->mode & SPI_CONFIG_MODE_MASK) << SPI_CONFIG_MODE_POS;
    for (int cs=0; cs<3; cs++)
    {
        flags |= (config->csActiveState[cs]) ? (1UL<<(SPI_CONFIG_CS_POL_POS+cs)) : 0;
        flags |= (!config->csEnabled[cs]) ? (1UL<<(SPI_CONFIG_HW_CS_POS+cs)) : 0;
    }
    flags |= (config->type) ? (1<<SPI_CONFIG_TYPE_POS) : 0;
    flags |= (config->mainHalfDuplex) ? (1UL<<SPI_CONFIG_HALFDUPLEX_POS) : 0;
    flags |= (config->mainHalfDuplexLen & SPI_CONFIG_HALFDUPLEX_BYTES_MASK) << SPI_CONFIG_HALFDUPLEX_BYTES_POS;
    flags |= (config->auxTxLsbFirst) ? (1UL<<SPI_CONFIG_LSB_TX_POS) : 0;
    flags |= (config->auxRxLsbFirst) ? (1UL<<SPI_CONFIG_LSB_RX_POS) : 0;
    flags |= (config->auxWordSize & SPI_CONFIG_WORDSIZE_MASK) << SPI_CONFIG_WORDSIZE_POS;
    printf("flags: %d\n", flags); //TODO remove
    result->handler = spiOpen(config->channel, config->baudrate, flags);
    assert(result->handler >= 0 && "failed to initialize SPI, check configuration");

    result->maxBufferSize = config->maxBufferSize;
    result->rxBuffer = config->rxBuffer;
    result->txBuffer = config->txBuffer;
}

void bspSpiDeinit(BspSpiHandler * handler)
{
    assert((NULL != handler) /* wrong input parameters */ );
    spiClose(handler->handler);
}

int bspSpiRead(BspSpiHandler * handler, uint32_t count)
{
    bspSpiValidateHandler(handler, count, false, true);
    return spiRead(handler->handler, (char*)handler->rxBuffer, count);
}

int bspSpiWrite(BspSpiHandler * handler, uint32_t count)
{
    bspSpiValidateHandler(handler, count, true, false);
    return spiWrite(handler->handler, (char*)handler->txBuffer, count);
}

int bspSpiReadWrite(BspSpiHandler * handler, uint32_t count)
{
    bspSpiValidateHandler(handler, count, true, true);
    return spiXfer(handler->handler, (char*)handler->txBuffer, (char*)handler->rxBuffer, count);
}
