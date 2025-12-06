#include "joystick.h"
#include "display.h"

void _timerInit(){
    /* Configuring Continuous Mode */
    Timer_A_configureContinuousMode(TIMER_A0_BASE, &continuousModeConfig);

    Interrupt_enableInterrupt(INT_TA0_N);

    /* Starting the Timer_A0 in continuous mode */
    Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_CONTINUOUS_MODE);
}

void _adcInit(){
    /* Configures Pin 6.0 and 4.4 as ADC input */
        GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6, GPIO_PIN0, GPIO_TERTIARY_MODULE_FUNCTION);
        GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4, GPIO_PIN4, GPIO_TERTIARY_MODULE_FUNCTION);

        /* Initializing ADC (ADCOSC/64/8) */
        ADC14_enableModule();
        ADC14_initModule(ADC_CLOCKSOURCE_ADCOSC, ADC_PREDIVIDER_64, ADC_DIVIDER_8, 0);

        /* Configuring ADC Memory (ADC_MEM0 - ADC_MEM1 (A15, A9)  with repeat)
             * with internal 2.5v reference */
        ADC14_configureMultiSequenceMode(ADC_MEM0, ADC_MEM1, true);
        ADC14_configureConversionMemory(ADC_MEM0,
                ADC_VREFPOS_AVCC_VREFNEG_VSS,
                ADC_INPUT_A15, ADC_NONDIFFERENTIAL_INPUTS);

        ADC14_configureConversionMemory(ADC_MEM1,
                ADC_VREFPOS_AVCC_VREFNEG_VSS,
                ADC_INPUT_A9, ADC_NONDIFFERENTIAL_INPUTS);

        /* Enabling the interrupt when a conversion on channel 1 (end of sequence)
         *  is complete and enabling conversions */
        ADC14_enableInterrupt(ADC_INT1);

        /* Enabling Interrupts */
        Interrupt_enableInterrupt(INT_ADC14);
        Interrupt_enableMaster();

        /* Setting up the sample timer to automatically step through the sequence
         * convert.
         */
        ADC14_enableSampleTimer(ADC_AUTOMATIC_ITERATION);

        /* Triggering the start of the sample */
        ADC14_enableConversion();
        ADC14_toggleConversionTrigger();
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
}

bool update_rectangle_pos(uint64_t status)
{
    return move_rectangle && (status & ADC_INT1);
}

void TA0_N_IRQHandler(void)
{
    /* clear the timer pending interrupt flag */
    Timer_A_clearInterruptFlag(TIMER_A0_BASE);

    move_rectangle=1;
}

void ADC14_IRQHandler(void)
{
    uint64_t status;

    const int RIGHT = 16000;
    const int LEFT = 300;
    const int UP = 16000;
    const int DOWN = 100;

    status = ADC14_getEnabledInterruptStatus();
    ADC14_clearInterruptFlag(status);

    if(update_rectangle_pos(status))
    {
        resultsBuffer[0] = ADC14_getResult(ADC_MEM0);
        resultsBuffer[1] = ADC14_getResult(ADC_MEM1);

        if(resultsBuffer[0]>RIGHT) {
            move_rectangle_right();
        }
        if(resultsBuffer[0]<LEFT) {
            move_rectangle_left();
        }
        if(resultsBuffer[1]>UP) {
            move_rectangle_up();
        }
        if(resultsBuffer[1]<DOWN) {
            move_rectangle_down();
        }
    }
    move_rectangle=0;
}

//S1 = FORWARD BUTTON
void PORT5_IRQHandler(void)
{
    uint_fast16_t status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P5);

    GPIO_clearInterruptFlag(GPIO_PORT_P5, status);

    if(status && GPIO_PIN1){
        if(!(button_pressed)){
            button_pressed=1;
            number_selected();
        }
    }



}

//S2 = BACKWARD BUTTON
void PORT3_IRQHandler(void)
{

    uint_fast16_t status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P3);

    GPIO_clearInterruptFlag(GPIO_PORT_P3, status);

    if(status && GPIO_PIN5){

    }

}

int main(void)
{
    _hwInit();
    draw_grid();
    _adcInit();
    _timerInit();
    _pushButtonsInit();

    while(1){
        PCM_gotoLPM0();
        if(GPIO_PORT_P5 && GPIO_PIN1){ //button released
                button_pressed=0;
            }

    }
}

