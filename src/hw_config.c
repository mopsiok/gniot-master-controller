/**
 * @file hw_config.c
 * @brief Hardware configuration.
 * 
 * @author mopsiok
 */

// Includes ========================================
#include "bsp.h"

// Private macros and defines ======================

// Private typedefs ================================

// Static variables ================================
static BspGpioHandler ledHandler;

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
        .defaultState = false 
        };
    ledHandler = bspGpioConfig(&ledConfig);
}


void ledToggleState(void)
{
    bspGpioToggleState(ledHandler);
}
