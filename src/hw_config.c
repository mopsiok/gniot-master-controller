/**
 * @file hw_config.c
 * @brief Hardware configuration.
 * 
 * @author mopsiok
 */

// Includes ========================================
#include "hw_config.h"
#include "utils/log.h"

// Private macros and defines ======================
#define SPI_BUFFER_SIZE 2

// Private typedefs ================================

// Static variables ================================
static BspGpioHandler ledHandler;
static BspPwmHandler pwmHandler;
static BspSpiHandler spiHandler;
static uint8_t spiRxBuffer[SPI_BUFFER_SIZE];

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

    BspPwmConfig pwmConfig = {
        .gpio = 17,
        .range = PWM_MAX_VALUE,
        .frequency = 100,
        .defaultValue = 250,
        };
    pwmHandler = bspPwmConfig(&pwmConfig);

    BspSpiConfig spiConfig = {
        .type = BSP_SPI_TYPE_MAIN,
        .channel = 0,
        .baudrate = 100000,
        .txBuffer = NULL,
        .rxBuffer = spiRxBuffer,
        .maxBufferSize = SPI_BUFFER_SIZE,
        .mode = BSP_SPI_MODE_POL0_PHA0,
        .csActiveState = {false, false, false},
        .csEnabled = {true, false, false},
        .mainHalfDuplex = false,
        };
    bspSpiConfig(&spiConfig, &spiHandler);

    logInfo("Hardware successfully initialized.");
}

void hardwareDeinit(void)
{
    bspSpiDeinit(&spiHandler);
    bspDeinit();
    logInfo("Hardware successfully deinitialized.");
}

void ledToggleState(void)
{
    bspGpioToggleState(ledHandler);
}

void pwmSetValue(unsigned int value)
{
    bspPwmSetValue(pwmHandler, value);
}

uint16_t spiReceive()
{
    bspSpiRead(&spiHandler, SPI_BUFFER_SIZE);
    logDebugMemory(spiHandler.rxBuffer, 2, "SPI rx");
    return 1000;
}