/**
 * @file hw_config.c
 * @brief Hardware configuration.
 * 
 * @author mopsiok
 */

// Includes ========================================
#include <stdint.h>
#include "hw_config.h"
#include "utils/log.h"

// Private macros and defines ======================
#define THERMOMETER_SPI_BUFFER_SIZE     2
#define THERMOMETER_MAX_TEMPERATURE     1023.75f
#define THERMOMETER_MAX_CODE            4095.0f

#define MIN(a,b) ((a) < (b) ? a : b)

// Private typedefs ================================

// Static variables ================================
static BspGpioHandler ledHandler;
static BspPwmHandler heaterPwmHandler;
static BspSpiHandler thermSpiHandler;
static uint8_t thermRxBuffer[THERMOMETER_SPI_BUFFER_SIZE];

// Global and extern variables =====================

// Static function prototypes ======================

// Static functions ================================

// Global functions ================================
void hardwareInit(void)
{
    bspInit();

    BspGpioConfig ledConfig = { 
        .gpio = 4,
        .mode = GPIO_MODE_OUTPUT,
        .pull = GPIO_PULL_OFF,
        .defaultState = false,
        };
    ledHandler = bspGpioConfig(&ledConfig);

    BspPwmConfig heaterConfig = {
        .gpio = 17,
        .range = HEATER_MAX_PWM_VALUE,
        .frequency = 100,
        .defaultValue = 0,
        };
    heaterPwmHandler = bspPwmConfig(&heaterConfig);

    BspSpiConfig thermConfig = {
        .type = BSP_SPI_TYPE_MAIN,
        .channel = 0,
        .baudrate = 100000,
        .txBuffer = NULL,
        .rxBuffer = thermRxBuffer,
        .maxBufferSize = THERMOMETER_SPI_BUFFER_SIZE,
        .mode = BSP_SPI_MODE_POL0_PHA0,
        .csActiveState = {false, false, false},
        .csEnabled = {true, false, false},
        .mainHalfDuplex = false,
        };
    bspSpiConfig(&thermConfig, &thermSpiHandler);

    logInfo("Hardware successfully initialized.");
}

void hardwareDeinit(void)
{
    bspSpiDeinit(&thermSpiHandler);
    bspDeinit();
    logInfo("Hardware successfully deinitialized.");
}

void setHeaterPower(uint16_t dutyCycle)
{
    dutyCycle = MIN(dutyCycle, HEATER_MAX_PWM_VALUE);
    bspPwmSetValue(heaterPwmHandler, dutyCycle);
}

float getHeaterTemperature(void)
{
    bspSpiRead(&thermSpiHandler, THERMOMETER_SPI_BUFFER_SIZE);
    uint8_t * buffer = thermSpiHandler.rxBuffer;
    uint16_t value = (buffer[0] << 8) | buffer[1];
    value >>= 3; //discard non important flags
    return (value * THERMOMETER_MAX_TEMPERATURE) / THERMOMETER_MAX_CODE;
}

void ledToggleState(void)
{
    //TODO temporary
    bspGpioToggleState(ledHandler);
}
