#include "push_button.h"

//variable used to see if the button is already pressed
bool button_pressed = 0;

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

//S1 = FORWARD BUTTON
void PORT5_IRQHandler(void)
{
    uint_fast16_t status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P5);

    GPIO_clearInterruptFlag(GPIO_PORT_P5, status);

    if(status && GPIO_PIN1){
        if(!(button_pressed)){
            button_pressed=1;
            //number_selected(); //is not right that this file include display.h
                               //this ISR should just return a bool button_pressed
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
