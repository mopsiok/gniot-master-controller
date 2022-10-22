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


BspPwmHandler bspPwmConfig(BspPwmConfig * config)
{
    assert(NULL != config && "wrong input parameters");

    gpioPWM(config->pin, 0);
    gpioSetPWMrange(config->pin, config->range);
    gpioSetPWMfrequency(config->pin, config->frequency);
    gpioPWM(config->pin, config->defaultValue);

    unsigned int realRange = gpioGetPWMrealRange(config->pin);
    printf("real range: %d\n", realRange); //TODO debug module
    assert(realRange == config->range && "PWM range mismatch, configuration change is needed");

    return (BspPwmHandler)(config->pin);
}

void bspPwmSetValue(BspPwmHandler handler, unsigned int value)
{
    gpioPWM(handler, value);
}


/* SPI */

