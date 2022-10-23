/**
 * @file hw_config.h
 * @brief Hardware configuration.
 * 
 * @author mopsiok
 */

#ifndef HW_CONFIG_H
#define HW_CONFIG_H

// Includes ========================================
#include "bsp/bsp.h"

#ifdef __cplusplus
extern "C" {
#endif

// Macros and defines ==============================
#define HEATER_MAX_PWM_VALUE            2000

// Typedefs ========================================

// Exported variables ==============================

// Global function prototypes ======================

/**
 * @brief Hardware initialization, execute before application init.
 * 
 */
void hardwareInit(void);

/**
 * @brief Hardware deinitialization, execute before exiting the program.
 * 
 */
void hardwareDeinit(void);

/**
 * @brief Set heater PWM output to given duty cycle.
 * 
 * @param dutyCycle Duty cycle in PWM ticks, [0 to HEATER_MAX_PWM_VALUE].
 */
void setHeaterPower(uint16_t dutyCycle);

/**
 * @brief Get single temperature readout from heater thermocouple (via MAX6675).
 * 
 * @return float Temperature sample in Celsius [0 to 1023.75*C].
 */
float getHeaterTemperature(void);

void ledToggleState(void);


#ifdef __cplusplus
}
#endif

#endif 
