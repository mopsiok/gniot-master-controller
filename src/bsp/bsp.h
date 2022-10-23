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
typedef void (*bspTimerFunc)    (void);

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

/**
 * @brief Configure SPI interface.
 * Check BspSpiConfig typedef for more details.
 * 
 * @param config Configuration structure.
 * @param result Pointer to resulting handler and other useful data.
 */
void bspSpiConfig(BspSpiConfig * config, BspSpiHandler * result);

/**
 * @brief Deinitialize SPI interface.
 * 
 * @param handler Pointer to SPI handler.
 */
void bspSpiDeinit(BspSpiHandler * handler);

/**
 * @brief Read bytes from given SPI handler.
 * 
 * @param handler Pointer to SPI handler.
 * @param count Number of bytes to read.
 * @return int Number of bytes actually read, or error if <0.
 */
int bspSpiRead(BspSpiHandler * handler, uint32_t count);

/**
 * @brief Write bytes from given SPI handler.
 * 
 * @param handler Pointer to SPI handler.
 * @param count Number of bytes to write.
 * @return int Number of bytes actually written, or error if <0.
 */
int bspSpiWrite(BspSpiHandler * handler, uint32_t count);

/**
 * @brief Simultaneous read and write bytes from given SPI handler.
 * 
 * @param handler Pointer to SPI handler.
 * @param count Number of bytes to read/write.
 * @return int Number of bytes actually read/written, or error if <0.
 */
int bspSpiReadWrite(BspSpiHandler * handler, uint32_t count);

/**
 * @brief Start periodic execution of given callback using a specified timer.
 * 
 * @param timer Timer id [0..9].
 * @param period Repeat period in ms [10..60000].
 * @param callback Callback to execute: void callback(void).
 * @return true if started properly, false otherwise.
 */
bool bspTimerStart(unsigned int timer, unsigned int period, bspTimerFunc callback);

/**
 * @brief Stop specified timer.
 * 
 * @param timer Timer id [0..9].
 * @return true if stopped properly, false otherwise.
 */
bool bspTimerStop(unsigned int timer);

/**
 * @brief Stop all timers.
 * 
 */
void bspTimerStopAll();

#ifdef __cplusplus
}
#endif

#endif 
