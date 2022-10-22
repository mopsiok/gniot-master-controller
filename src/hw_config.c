/**
 * @file hw_config.c
 * @brief Hardware configuration.
 * 
 * @author mopsiok
 */

// Includes ========================================
#include "hw_config.h"

// Private macros and defines ======================

// Private typedefs ================================

// Static variables ================================
static BspGpioHandler ledHandler;
static BspPwmHandler pwmHandler;

// Global and extern variables =====================

// Static function prototypes ======================

// Static functions ================================

// Global functions ================================

void hardwareConfig(void)
{
    bspInit();

    BspGpioConfig ledConfig = { 
        .pin = GPIO_4,
        .mode = GPIO_MODE_OUTPUT,
        .pull = GPIO_PULL_OFF,
        .defaultState = false,
        };
    ledHandler = bspGpioConfig(&ledConfig);

    BspPwmConfig pwmConfig = {
        .pin = GPIO_17,
        .range = PWM_MAX_VALUE,
        .frequency = 100,
        .defaultValue = 250,
        };
    pwmHandler = bspPwmConfig(&pwmConfig);
}


void ledToggleState(void)
{
    bspGpioToggleState(ledHandler);
}


void pwmSetValue(unsigned int value)
{
    bspPwmSetValue(pwmHandler, value);
}
