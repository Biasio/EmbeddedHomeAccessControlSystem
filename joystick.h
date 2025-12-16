#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdio.h>

volatile uint16_t resultsBuffer[2];

//timer used to slow down the adc conversion from the joystick
static const Timer_A_ContinuousModeConfig continuousModeConfig =
{
    TIMER_A_CLOCKSOURCE_SMCLK,          // SMCLK Clock Source
    TIMER_A_CLOCKSOURCE_DIVIDER_64,      // SMCLK/1 = 32.768khz
    TIMER_A_TAIE_INTERRUPT_ENABLE,      // Enable Overflow ISR
    TIMER_A_DO_CLEAR                    // Clear Counter
};

void _timerInit();
void _adcInit();

const uint16_t* get_results_buffer(void);
bool data_aquired(void);

#endif
