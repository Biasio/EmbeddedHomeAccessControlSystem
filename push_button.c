#include "push_button.h"

volatile uint8_t buttonA_pressed = 0;
volatile uint8_t buttonB_pressed = 0;

int timer_int_counter_button = 0;

static const Timer_A_UpModeConfig debounceTimerConfig =
{
    TIMER_A_CLOCKSOURCE_SMCLK,              // SMCLK Clock Source
    TIMER_A_CLOCKSOURCE_DIVIDER_64,         // SMCLK/64 = 46.875 Hz
    4688,                                   // CCR0 Value (2344 counts = ~50ms) CCR Value = f_{CLK} x Tempo Desiderato
    TIMER_A_TAIE_INTERRUPT_DISABLE,         // Disable Overflow ISR (non serve)
    TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE      // Abilita l'interrupt per CCR0
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
    // 1. Ferma il timer immediatamente (o azzera il contatore e ferma)
    Timer_A_stop(TIMER_A1_BASE);

    // 2. Controlla lo stato del pin (logica di validazione)
    if (GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN1) == GPIO_INPUT_PIN_LOW) {
        buttonA_pressed = 1; // Pressione valida
        //printf("Valid button A press detected.\n\n");
    }
    if (GPIO_getInputPinValue(GPIO_PORT_P3, GPIO_PIN5) == GPIO_INPUT_PIN_LOW) {
        buttonB_pressed = 1; // Pressione valida
        //printf("Valid button B press detected.\n\n");
    }

    // 3. Riabilita l'interrupt del pulsante
    GPIO_enableInterrupt(GPIO_PORT_P5, GPIO_PIN1);
    GPIO_enableInterrupt(GPIO_PORT_P3, GPIO_PIN5);

    // 4. Cancella il flag di interrupt del CCR0
    Timer_A_clearCaptureCompareInterrupt(TIMER_A1_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0);
}


//S1 = FORWARD BUTTON
void PORT5_IRQHandler(void)
{
    uint_fast16_t status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P5);

    GPIO_clearInterruptFlag(GPIO_PORT_P5, status);

    if(status && GPIO_PIN1){
        //printf("Button pressed - Debounce started\n");

        // Disabilita immediatamente gli interrupt di PORT5
        // Fino a quando il timer non è scaduto, non vogliamo altri interrupt da P5
        GPIO_disableInterrupt(GPIO_PORT_P5, GPIO_PIN1);

        /* Starting the Timer_A0 in continuous mode */
        Timer_A_clearTimer(TIMER_A1_BASE); // Resetta il contatore a 0
        Timer_A_startCounter(TIMER_A1_BASE, TIMER_A_CONTINUOUS_MODE);
    }
}

//S2 = BACKWARD BUTTON
void PORT3_IRQHandler(void)
{

    uint_fast16_t status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P3);

    GPIO_clearInterruptFlag(GPIO_PORT_P3, status);

    if(status && GPIO_PIN5){
        GPIO_disableInterrupt(GPIO_PORT_P3, GPIO_PIN5);

        /* Starting the Timer_A0 in continuous mode */
        Timer_A_clearTimer(TIMER_A1_BASE); // Resetta il contatore a 0
        Timer_A_startCounter(TIMER_A1_BASE, TIMER_A_CONTINUOUS_MODE);
    }

}
