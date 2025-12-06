#include "fsm.h"

void boot(void);
void door_locked(void);
void insert_pin(void);
void open_door(void);
void wait_RFID(void);
void admin_menu(void);
void wrong_pin(void);
void last_pin(void);
void block_access(void);
void wait_reset_door(void);


// ------------------------------------------------------ //
//All these functions have to be implemented, they are like this just to compile
void boot(void){
    _hwInit();
    draw_grid();
}
void door_locked(void){
    printf("A");
}
void insert_pin(void){
    printf("A");
}
void open_door(void){
    printf("A");
}
void wait_RFID(void){
    printf("A");
}
void admin_menu(void){
    printf("A");
}
void wrong_pin(void){
    printf("A");
}
void last_pin(void){
    printf("A");
}
void block_access(void){
    printf("A");
}
void wait_reset_door(void){
    printf("A");
}

// ------------------------------------------------ //

State_t cur_state = STATE_BOOT;

StateMachine_t fsm[] = {
     {STATE_BOOT, fn_BOOT},
     {STATE_DOOR_LOCKED, fn_DOOR_LOCKED},
     {STATE_INSERT_PIN, fn_INSERT_PIN},
     {STATE_OPEN_DOOR, fn_OPEN_DOOR},
     {STATE_WAIT_RFID, fn_WAIT_RFID},
     {STATE_ADMIN_MENU, fn_ADMIN_MENU},
     {STATE_WRONG_PIN, fn_WRONG_PIN},
     {STATE_LAST_PIN, fn_LAST_PIN},
     {STATE_BLOCK_ACCESS, fn_BLOCK_ACCESS},
     {STATE_WAIT_RESET_DOOR, fn_WAIT_RESET_DOOR},
};

// -----------------------------------------------//
// Implementation of the state's functions

void fn_BOOT(void){
    printf("Boot \n");
    boot();
    //cur_state = STATE_DOOR_LOCKED;
}

void fn_DOOR_LOCKED(void){
    printf("Door Locked \n");
    door_locked();
    cur_state = STATE_INSERT_PIN;
}

void fn_INSERT_PIN(void){
    printf("Insert Pin \n");
    insert_pin();
    //if pin_user is correct
    //  cur_state = STATE_OPEN_DOOR;
    //else if pin_admin is correct
    //  cur_state = STATE_WAIT_RFID
    //else
    //  cur_state = STATE_WRONG_PIN
}

void fn_OPEN_DOOR(void){
    printf("Door open \n");
    open_door();
    cur_state = STATE_DOOR_LOCKED;
}

void fn_WAIT_RFID(void){
    printf("Wait for RFID \n");
    wait_RFID();
    cur_state = STATE_ADMIN_MENU;
}

void fn_ADMIN_MENU(void){
    printf("Show admin menu \n");
    admin_menu();
    //cur_state = other states for each function
}

void fn_WRONG_PIN(void){
    printf("Wrong pin \n");
    wrong_pin(); //show an error message on display
    //if error_counter<3
    //  cur_state = STATE_INSERT_PIN;
    //else if error_counter=3
    //  cur_state = STATE_LAST_PIN
}

void fn_LAST_PIN(void){
    printf("Last possibility for right pin \n");
    last_pin();
    //if pin_user is correct
    //  cur_state = STATE_OPEN_DOOR;
    //else
    //  cur_state = STATE_BLOCK_ACCESS
}

void fn_BLOCK_ACCESS(void){
    printf("Access blocked \n");
    block_access();
    cur_state = STATE_WAIT_RESET_DOOR;
}

void fn_WAIT_RESET_DOOR(void){
    printf("Wait door to be reset \n");
    wait_reset_door();
    //if telegram or RFID
    //  cur_state = STATE_INSERT_PIN;
}

// ---------------------------------------------//

void _hwInit()
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

    _graphicsInit();
    _adcInit();
    _timerInit();
}


// Function to run in the main
void FSM_Run(void)
{


    if(cur_state < NUM_STATES){
        (*fsm[cur_state].state_function)();
    }
    else{
        // Gestione errore stato non valido
    }
}
