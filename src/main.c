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
#define HEATER_TIMER_ID         0
#define LED_TIMER_ID            1

#define HEATER_TIMER_PERIOD_MS  500
#define LED_TIMER_PERIOD_MS     150

#define MAIN_LOOP_SLEEP_S       10


// Private typedefs ================================

// Static variables ================================

// Global and extern variables =====================

// Static function prototypes ======================

// Static functions ================================
static void heaterCallback(void)
{
    static int i = 0;

    setHeaterPower((250 + i * 100) % HEATER_MAX_PWM_VALUE);
    float temp = getHeaterTemperature();
    logDebug("temperature: %5.2f", temp);
    
    i++;
}

static void ledCallback(void)
{
    ledToggleState();
}

// Global functions ================================

int main()
{
    logInfo("gnIoT master controller");

    hardwareInit();

    bspTimerStart(HEATER_TIMER_ID, HEATER_TIMER_PERIOD_MS, heaterCallback);
    bspTimerStart(LED_TIMER_ID, LED_TIMER_PERIOD_MS, ledCallback);

    usleep(MAIN_LOOP_SLEEP_S*1000000UL);

    bspTimerStopAll();
    hardwareDeinit();

    logInfo("Exiting.");
    return 0;
}
