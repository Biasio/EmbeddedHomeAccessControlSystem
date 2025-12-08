#include "msp.h"
#include <stdio.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

//#include "fsm.h"
#include "joystick.h"
#include "display.h"
#include "push_button.h"

void _hwInit(void);

//this function will stay in other files like fsm.h
void _hwInit(void)
{
    /* Halting WDT and disabling master interrupts */
    WDT_A_holdTimer();
    Interrupt_disableMaster();

    /* Set the core voltage level to VCORE1 */
    PCM_setCoreVoltageLevel(PCM_VCORE1);

    /* Set 2 flash wait states for Flash bank 0 and 1*/
    FlashCtl_setWaitState(FLASH_BANK0, 2);
    FlashCtl_setWaitState(FLASH_BANK1, 2);

    /* Initializes Clock System */
    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_48);
    CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    CS_initClockSignal(CS_HSMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    CS_initClockSignal(CS_ACLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);

}

int main(void)
{

    _hwInit();

    bool first_screen = 1;

    //display
    _graphicsInit();
    //draw_grid();
    draw_admin_menu(first_screen); //draw first screen

    //joystick
    _adcInit();
    _timerInit();

    //buttons
    _pushButtonsInit();

    uint16_t* current_results;

    bool move_on_menu = 0;
    bool move_on_grid = 1;

    while(1){
        PCM_gotoLPM0();

        //cosi funziona ma non sfrutto la LPM0
        current_results = get_results_buffer();

        if(data_aquired()){
            move_rectangle_on_display(current_results[0], current_results[1], move_on_menu);

        }

        if(buttonA_pressed){
            buttonA_pressed=0;
            //printf("A\n");

            function_selected();

        }
        if(buttonB_pressed){
            buttonB_pressed=0;
            //printf("B\n");

            //si potrebbe far si che se torno indietro dalla seconda pagina
            //torni nella seconda pagina
            draw_admin_menu(first_screen);

        }

    }
}

