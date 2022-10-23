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
#define LOOP_COUNT      5
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

    float dt = LOOP_DELAY_US / 1000000.0f;
    for (int i = 0; i <= LOOP_COUNT; i++)
    {
        logInfo("elapsed: %05.2f", dt * i);

        ledToggleState();
        pwmSetValue((250 + i * 100) % PWM_MAX_VALUE);
        spiReceive();

        usleep(LOOP_DELAY_US);
    }

    hardwareDeinit();

    logInfo("Exiting.");
    return 0;
}
