#include <stdio.h>
#include <pigpio.h>

#include "bsp.h"


#define MODE_GPIO           0
#define MODE_PWM            1
#define RUN_MODE            MODE_GPIO

#define LED_PIN         4
#define PWM_RANGE       1000
#define PWM_FREQ        100
#define PWM_LOOP_COUNT  20


int bspInit(void)
{
    if (gpioInitialise() < 0) 
    {
        return 1;
    }

    gpioSetMode(LED_PIN, PI_OUTPUT);
    gpioSetPullUpDown(LED_PIN, PI_PUD_OFF);
    #if RUN_MODE == MODE_GPIO
        gpioWrite(LED_PIN, 0);
    #else
        gpioPWM(LED_PIN, 0);
        gpioSetPWMrange(LED_PIN, PWM_RANGE);
        gpioSetPWMfrequency(LED_PIN, PWM_FREQ);

        printf("PWM freq=%d, duty=%d, duty_real=%d\n", 
            gpioGetPWMfrequency(LED_PIN),
            gpioGetPWMrange(LED_PIN),
            gpioGetPWMrealRange(LED_PIN)
            );
    #endif
    return 0;
}


void bspDeinit(void)
{
    #if RUN_MODE == MODE_GPIO
        gpioWrite(LED_PIN, 0);
    #else
        gpioPWM(LED_PIN, 0);
    #endif

    gpioTerminate();
}


void bspBeep(void)
{
    static size_t iteration = 0;

    #if RUN_MODE == MODE_GPIO
        uint8_t level = iteration % 2;
        gpioWrite(LED_PIN, level);
        printf("\tBSP: level = %d\n", level);
    #else
        size_t counter = iteration % (PWM_LOOP_COUNT + 1);
        uint16_t pwm = (PWM_RANGE * counter) / PWM_LOOP_COUNT;
        gpioPWM(LED_PIN, pwm);
        printf("\tBSP: pwm = %d\n", pwm);
    #endif

    iteration++;
}
