/**
 * @file main.c
 * @brief gnIoT master controller main file.
 * 
 * @author mopsiok
 */

// Includes ========================================
#include <stdint.h>
#include <stdbool.h>

#include "hw_config.h"
#include "utils/log.h"

// Private macros and defines ======================
#define LOOP_COUNT      20
#define LOOP_DELAY_US   500000

// Private typedefs ================================

// Static variables ================================

// Global and extern variables =====================

// Static function prototypes ======================

// Static functions ================================

// Global functions ================================

int main()
{
    logInfo("gnIoT master controller");

    hardwareInit();

    for (int i = 0; i <= LOOP_COUNT; i++)
    {
        ledToggleState();
        setHeaterPower((250 + i * 100) % HEATER_MAX_PWM_VALUE);
        float temp = getHeaterTemperature();

        logDebug("temperature: %5.2f", temp);

        usleep(LOOP_DELAY_US);
    }

    hardwareDeinit();

    logInfo("Exiting.");
    return 0;
}
