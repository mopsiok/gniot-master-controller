/**
 * @file hw_config.c
 * @brief Hardware configuration.
 * 
 * @author mopsiok
 */

// Includes ========================================
#include "hw_config.h"

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

void hardwareConfig(void)
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
}

void ledToggleState(void)
{
    bspGpioToggleState(ledHandler);
}

void pwmSetValue(unsigned int value)
{
    bspPwmSetValue(pwmHandler, value);
}

#include <stdio.h> //TODO
uint16_t spiReceive()
{
    bspSpiRead(&spiHandler, SPI_BUFFER_SIZE);
    printf("\tSPI: %02x %02x\n", spiHandler.rxBuffer[0], spiHandler.rxBuffer[1]);
    return 1000;
}