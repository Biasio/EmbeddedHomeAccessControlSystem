#include "push_button.h"

volatile uint8_t buttonA_pressed = 0;
volatile uint8_t buttonB_pressed = 0;

int timer_int_counter_button = 0;

static const Timer_A_UpModeConfig debounceTimerConfig =
{
    TIMER_A_CLOCKSOURCE_ACLK,       // VLO ~9.4kHz
    TIMER_A_CLOCKSOURCE_DIVIDER_64, // ~146 Hz
    1,                                   // CCR0 Value (1 count = ~6ms) CCR Value = f_{CLK} x desired_time
    TIMER_A_TAIE_INTERRUPT_DISABLE,         // Disable Overflow ISR
    TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE      // Enable interrupt for CCR0
};

void _timerInitButton(){
    /* Configuring Continuous Mode */
    Timer_A_configureUpMode(TIMER_A1_BASE, &debounceTimerConfig);

    Interrupt_enableInterrupt(INT_TA1_0);
}


void _pushButtonsInit(){
        //Set pushBUTTONS
        //S1 = 4.33 = P5.1
        //S2 = 4.32 = P3.5

        GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P5, GPIO_PIN1);
        GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P3, GPIO_PIN5);

        GPIO_interruptEdgeSelect(GPIO_PORT_P5, GPIO_PIN1, GPIO_HIGH_TO_LOW_TRANSITION);
        GPIO_interruptEdgeSelect(GPIO_PORT_P3, GPIO_PIN5, GPIO_HIGH_TO_LOW_TRANSITION);

        //enable interrupts on buttons
        GPIO_enableInterrupt(GPIO_PORT_P5, GPIO_PIN1);
        GPIO_enableInterrupt(GPIO_PORT_P3, GPIO_PIN5);

        Interrupt_enableInterrupt(INT_PORT5);
        Interrupt_enableInterrupt(INT_PORT3);

        Interrupt_enableMaster(); //there must be just one of this instruction

        _timerInitButton();
}

void TA1_0_IRQHandler(void)
{
    // Stop the timer
    Timer_A_stop(TIMER_A1_BASE);
    Timer_A_clearCaptureCompareInterrupt(TIMER_A1_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0);

    // Check state of pin
    if (GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN1) == GPIO_INPUT_PIN_LOW) {
        buttonA_pressed = 1; // Valid pressure
        //printf("Valid button A press detected.\n\n");
    }
    if (GPIO_getInputPinValue(GPIO_PORT_P3, GPIO_PIN5) == GPIO_INPUT_PIN_LOW) {
        buttonB_pressed = 1; // Valid pressure
        //printf("Valid button B press detected.\n\n");
    }

    // Clear possible pending interrupts flags set during debounce time
    GPIO_clearInterruptFlag(GPIO_PORT_P5, GPIO_PIN1);
    GPIO_clearInterruptFlag(GPIO_PORT_P3, GPIO_PIN5);

    // Enable interrupt for push buttons
    GPIO_enableInterrupt(GPIO_PORT_P5, GPIO_PIN1);
    GPIO_enableInterrupt(GPIO_PORT_P3, GPIO_PIN5);
}


//S1 = FORWARD BUTTON
void PORT5_IRQHandler(void)
{
    uint_fast16_t status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P5);

    GPIO_clearInterruptFlag(GPIO_PORT_P5, status);

    if(status & GPIO_PIN1){
        //printf("Button pressed - Debounce started\n");

        // Disable interrupts of PORT5 until timer has passed
        GPIO_disableInterrupt(GPIO_PORT_P5, GPIO_PIN1);

        /* Starting the Timer_A0 in continuous mode */
        Timer_A_clearTimer(TIMER_A1_BASE); // Reset counter at 0
        Timer_A_startCounter(TIMER_A1_BASE, TIMER_A_UP_MODE);
    }
}

//S2 = BACKWARD BUTTON
void PORT3_IRQHandler(void)
{

    uint_fast16_t status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P3);

    GPIO_clearInterruptFlag(GPIO_PORT_P3, status);

    if(status & GPIO_PIN5){
        GPIO_disableInterrupt(GPIO_PORT_P3, GPIO_PIN5);

        /* Starting the Timer_A0 in continuous mode */
        Timer_A_clearTimer(TIMER_A1_BASE); // Reset counter at 0
        Timer_A_startCounter(TIMER_A1_BASE, TIMER_A_UP_MODE);
    }

}
