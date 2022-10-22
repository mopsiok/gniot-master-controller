/**
 * @file bsp.c
 * @brief BSP wrapper
 * 
 * @author mopsiok
 */

// Includes ========================================
#include <pigpio.h>
#include <assert.h>

#include "bsp.h"

// Private macros and defines ======================

// Private typedefs ================================

// Static variables ================================

// Global and extern variables =====================

// Static function prototypes ======================

// Static functions ================================

// Global functions ================================

/* BSP module initialization */
void bspInit(void)
{
    int result = gpioInitialise();
    assert(result >= 0 && "pigpio initialization failed");
}


void bspDeinit(void)
{
    gpioTerminate();
}


/* GPIO */
BspGpioHandler bspGpioConfig(BspGpioConfig * config)
{
    assert(NULL != config && "wrong input parameters");
    
    gpioSetMode(config->pin, config->mode);
    gpioSetPullUpDown(config->pin, config->pull);

    bspGpioSetState(config->pin, config->defaultState);
    return config->pin;
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


/* SPI */

