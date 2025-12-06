#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdio.h>

//variable used to see if the button is already pressed
bool button_pressed = 0;

//variable used to move the rectangle in the display after the joystick moved
bool move_rectangle;

static uint16_t resultsBuffer[2];

//timer used to slow down the adc conversion from the joystick
const Timer_A_ContinuousModeConfig continuousModeConfig =
{
    TIMER_A_CLOCKSOURCE_SMCLK,          // SMCLK Clock Source
    TIMER_A_CLOCKSOURCE_DIVIDER_64,      // SMCLK/1 = 32.768khz
    TIMER_A_TAIE_INTERRUPT_ENABLE,      // Enable Overflow ISR
    TIMER_A_DO_CLEAR                    // Clear Counter
};

void _timerInit();
void _adcInit();
void _pushButtonsInit();

#endif
