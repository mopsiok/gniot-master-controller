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

void bspInit(void);
void bspDeinit(void);

BspGpioHandler bspGpioConfig(BspGpioConfig * config);
bool bspGpioGetState(BspGpioHandler handler);
void bspGpioSetState(BspGpioHandler handler, bool state);
void bspGpioToggleState(BspGpioHandler handler);

#ifdef __cplusplus
}
#endif

#endif 
