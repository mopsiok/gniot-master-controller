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
#define PWM_MAX_VALUE           2000

// Typedefs ========================================

// Exported variables ==============================

// Global function prototypes ======================

void hardwareInit(void);
void hardwareDeinit(void);
void ledToggleState(void);
void pwmSetValue(unsigned int value);
uint16_t spiReceive();


#ifdef __cplusplus
}
#endif

#endif 
