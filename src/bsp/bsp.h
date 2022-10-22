/**
 * @file bsp.h
 * @brief BSP wrapper
 * 
 * @author mopsiok
 */

#ifndef BSP_H
#define BSP_H

// Includes ========================================
#include "bspDefines.h"

#ifdef __cplusplus
extern "C" {
#endif

// Macros and defines ==============================

// Typedefs ========================================

// Exported variables ==============================

// Global function prototypes ======================

/**
 * @brief Low-level hardware library initialization.
 * Must be called before using any peripheral.
 */
void bspInit(void);

/**
 * @brief Low-level hardware librady definitialization.
 * Should be called at the end of the program.
 */
void bspDeinit(void);

/**
 * @brief Configure GPIO pin.
 * 
 * @param config Configuration structure.
 * @return BspGpioHandler GPIO handler, used for its control.
 */
BspGpioHandler bspGpioConfig(BspGpioConfig * config);

/**
 * @brief Read the state of given GPIO pin.
 * 
 * @param handler GPIO handler.
 * @return true high state.
 * @return false low state.
 */
bool bspGpioGetState(BspGpioHandler handler);

/**
 * @brief Set the state of given GPIO pin.
 * 
 * @param handler GPIO handler.
 * @param state true for high state, false low state.
 */
void bspGpioSetState(BspGpioHandler handler, bool state);

/**
 * @brief Set given GPIO pin to the opposite state.
 * 
 * @param handler GPIO handler.
 */
void bspGpioToggleState(BspGpioHandler handler);

/**
 * @brief Configure PWM pin.
 * 
 * @param config Configuration structure.
 * @return BspPwmHandler PWM handler, used to its control.
 */
BspGpioHandler bspPwmConfig(BspPwmConfig * config);

/**
 * @brief Set PWM value of given GPIO pin.
 * 
 * @param handler PWM handler.
 * @param value PWM value.
 */
void bspPwmSetValue(BspPwmHandler handler, unsigned int value);

#ifdef __cplusplus
}
#endif

#endif 
