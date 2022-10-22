/**
 * @file main.c
 * @brief gnIoT master controller main file.
 * 
 * @author mopsiok
 */

// Includes ========================================
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "hw_config.h"

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
    hardwareConfig();
    
    float dt = LOOP_DELAY_US / 1000000.0f;
    for (int i = 0; i <= LOOP_COUNT; i++)
    {
        printf("elapsed: %05.2f\n", dt * i);

        ledToggleState();
        pwmSetValue((250 + i * 100) % PWM_MAX_VALUE);
        spiReceive();
        usleep(LOOP_DELAY_US);
    }

    bspDeinit();

    printf("Done.\n");
    return 0;
}
