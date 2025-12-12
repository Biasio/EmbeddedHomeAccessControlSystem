#include "fsm.h"
#include "joystick.h"
#include "display.h"
#include "push_button.h"


#define MOVE_ON_MENU 0  //rectangle on display move on admin menu
#define MOVE_ON_GRID 1  //rectangle on display move on grid numbers

int saved_pin_user[4] = {1,1,1,1};
int saved_pin_admin[4] = {9,9,9,9};
int selected_pin_user[4] = {0,0,0,0};

int error_pin = 0; //variable to count the number of wrong pin, when is equal to 3, block access

//bool first_screen = 1; //use to select the page in the admin menu

uint16_t* current_results;

int32_t displayX = 64;
int32_t displayY = 64;

void _hwInit(void);
void boot(void);
void door_locked(void);

void draw_grid_numbers();

void insert_pin(void);
void open_door(void);
void wait_RFID(void);
int admin_menu(void);

void menu_last_access_log(void);
void menu_setup_pin(void);
void menu_setup_wifi(void);
void menu_factory_reset(void);
void menu_unlock_door(void);
void menu_block_pin(void);

void wrong_pin(void);
void last_pin(void);
void block_access(void);
void wait_reset_door(void);


// ------------------------------------------------------ //

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

    //display
    _graphicsInit();

    //joystick
    _adcInit();
    _timerInit();

    //buttons
    _pushButtonsInit();
}

void boot(void){
    _hwInit();
}
void door_locked(void){
    display_string("10 : 00");
}

void insert_pin(void){ //MAYBE WE CAN ADD LMPO HERE

    bool number_pin_aquired = 0;

    int i;
    for(i=0;i<4;i++){
        number_pin_aquired=0;
        do{
            //get results from joystick
            current_results = get_results_buffer();

            //if timer of joystick finished, move rectangle
            if(data_aquired()){
                move_rectangle_on_display(current_results[0], current_results[1], MOVE_ON_GRID);
            }

            //detect pressure of button A (S1)
            if(buttonA_pressed){
                buttonA_pressed=0;
                number_pin_aquired=1;
                selected_pin_user[i]=number_selected();
            }

            // Add BUTTON B to deselect a number
            if(buttonB_pressed){
                buttonB_pressed=0;

            }

        } while(number_pin_aquired==0); //when the digit is selected, exit from loop

    }


}
void open_door(void){
    // - show on display that door is opening
    // - turn on servo
    // - turn on LED
    // ? make a sound to signal that the code is correct

    display_door_open();

    int i;
    for(i=0;i<1000000;i++); //simulate opening of the door, IS BETTER TO USE A TIMER

}
void wait_RFID(void){
    display_string("PLEASE, USE RFID");
    int i;
    for(i=0;i<1000000;i++); //simulate opening of the door, IS BETTER TO USE A TIMER
}
int admin_menu(void){
    draw_admin_menu(1); // 1 = FIRST_SCREEN

    bool admin_menu_active = 1;

    while(admin_menu_active){   //put a LMP0 ?
        //get results from joystick
        current_results = get_results_buffer();

        //if timer of joystick finished, move rectangle
        if(data_aquired()){
            move_rectangle_on_display(current_results[0], current_results[1], MOVE_ON_MENU);

            if(buttonA_pressed){
                buttonA_pressed=0;
                return display_function_selected();
            }
        }
        if(buttonB_pressed){
            buttonB_pressed=0;
            admin_menu_active=0;
        }
    }
    return 6; //return to INSERT PIN
}


void menu_last_access_log(void){
    display_menu_last_access_log();
}

void menu_setup_pin(void){      //WHAT HAPPENS IF INSERT THE SAME PIN AS ADMIN PIN?
                                //DISPLAY A MESSAGE THAT THE PIN IS ALREADY OF THE ADMIN

    display_menu_setup_pin();

    bool number_pin_aquired = 0;

    int i;
    for(i=0;i<4;i++){
        number_pin_aquired=0;
        do{
            //get results from joystick
            current_results = get_results_buffer();

            //if timer of joystick finished, move rectangle
            if(data_aquired()){
                move_rectangle_on_display(current_results[0], current_results[1], MOVE_ON_GRID);
            }

            //detect pressure of button A (S1)
            if(buttonA_pressed){
                buttonA_pressed=0;
                number_pin_aquired=1;
                saved_pin_user[i]=number_selected();
            }

            // Add BUTTON B to deselect a number
            if(buttonB_pressed){
                buttonB_pressed=0;
            }

        } while(number_pin_aquired==0); //when the digit is selected, exit from loop
   }


}

void menu_setup_wifi(void){
    display_menu_setup_wifi();
}

void menu_factory_reset(void){
    display_menu_factory_reset();
}

void menu_unlock_door(void){
    display_menu_unlock_door();
}

void menu_block_pin(void){
    display_menu_block_pin();
}


void wrong_pin(void){
    error_pin++;

    display_wrong_pin(error_pin);

}
void last_pin(void){

}
void block_access(void){
    display_block_access();

    int i;
    for(i=0;i<1000000;i++);
}
void wait_reset_door(void){

}

// ------------------------------------------------ //


State_t cur_state = STATE_DOOR_LOCKED;

StateMachine_t fsm[] = {
     {STATE_BOOT, fn_BOOT},
     {STATE_DOOR_LOCKED, fn_DOOR_LOCKED},
     {STATE_INSERT_PIN, fn_INSERT_PIN},
     {STATE_OPEN_DOOR, fn_OPEN_DOOR},
     {STATE_WAIT_RFID, fn_WAIT_RFID},
     {STATE_ADMIN_MENU, fn_ADMIN_MENU},

     {STATE_LAST_ACCESS_LOG, fn_menu_lal},
     {STATE_SETUP_PIN, fn_menu_setup_pin},
     {STATE_SETUP_WIFI, fn_menu_wifi},
     {STATE_FACTORY_RESET, fn_menu_fact_reset},
     {STATE_UNLOCK_DOOR, fn_menu_unlock_door},
     {STATE_BLOCK_PIN, fn_menu_block_pin},

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
    cur_state = STATE_DOOR_LOCKED;
}

void fn_DOOR_LOCKED(void){
    printf("Door Locked \n");
    door_locked();

    if(buttonA_pressed){    //will be changed with proximity sensor
        buttonA_pressed=0;
        cur_state = STATE_INSERT_PIN;
    }

}

void fn_INSERT_PIN(void){
    //printf("Insert Pin \n");
    display_string("INSERT PIN");
    draw_grid();
    insert_pin();

    bool user_pin_correct = 1;
    bool admin_pin_correct = 1;

    // --- 1. Check for USER PIN ---
    int i;
    for(i=0;i<4;i++){
        user_pin_correct = 1;
        if(selected_pin_user[i]!=saved_pin_user[i]){ //if pin_user is wrong
            user_pin_correct = 0;
            break;
        }
    }

    // --- 2. Check if the User PIN was Correct ---
    if(user_pin_correct){
        cur_state = STATE_OPEN_DOOR;
        error_pin = 0; //pin correct, reset counter of errors
    } else {
        // --- 3. If User PIN was wrong, Check for ADMIN PIN ---

        for(i=0;i<4;i++){
            if(selected_pin_user[i]!=saved_pin_admin[i]){ //if pin_admin is wrong
                admin_pin_correct = 0;
                break;
            }
        }
        // --- 4. Final State Decision ---
        if (admin_pin_correct) {
            cur_state = STATE_WAIT_RFID;
            error_pin = 0; //pin correct, reset counter of errors
        } else {
            cur_state = STATE_WRONG_PIN;
        }
    }



}

void fn_OPEN_DOOR(void){
    open_door();

    cur_state = STATE_DOOR_LOCKED;
}

void fn_WAIT_RFID(void){
    wait_RFID();

    //if RFID signal doesn't arrive after a certain amount of time, display a message and go back to INSERT_PIN

    cur_state = STATE_ADMIN_MENU;
}

void fn_ADMIN_MENU(void){
    int selected_function;
    selected_function = admin_menu();

    //switch case to decide to which state of menu go
    switch(selected_function){
    case 0:
        cur_state = STATE_LAST_ACCESS_LOG;
        break;
    case 1:
        cur_state = STATE_SETUP_PIN;
        break;
    case 2:
        cur_state = STATE_SETUP_WIFI;
        break;
    case 3:
        cur_state = STATE_FACTORY_RESET;
        break;
    case 4:
        cur_state = STATE_UNLOCK_DOOR;
        break;
    case 5:
        cur_state = STATE_BLOCK_PIN;
        break;
    case 6:
    default:
        cur_state = STATE_INSERT_PIN;
        break;
    }
}

void fn_menu_lal(void){
    menu_last_access_log();
    if(buttonB_pressed){
        buttonB_pressed=0;
        cur_state = STATE_ADMIN_MENU;
    }
}

void fn_menu_setup_pin(void){
    bool pins_equal = 0;

    do{
        menu_setup_pin();

        // verify if pin_admin = pin_user
        int i;
        for(i=0;i<4;i++){
            if(saved_pin_user[i]==saved_pin_admin[i]){
                pins_equal = 1;
            }else pins_equal = 0;
        }
        if(pins_equal){
            display_string("PIN ADMIN = PIN USER");
            display_string("CHOOSE ANOTHER PIN");
        }
    } while(pins_equal);

    display_string("PIN CHANGED");

    cur_state = STATE_ADMIN_MENU;
}

void fn_menu_wifi(void){
    menu_setup_wifi();
}
void fn_menu_fact_reset(void){
    menu_factory_reset();
}
void fn_menu_unlock_door(void){
    menu_unlock_door();
}
void fn_menu_block_pin(void){
    menu_block_pin();
}

void fn_WRONG_PIN(void){
    printf("Wrong pin \n");
    wrong_pin(); //show an error message on display

    if(error_pin<3){
        cur_state = STATE_INSERT_PIN;
    }else if(error_pin==3){
        cur_state = STATE_BLOCK_ACCESS; //we should remove STATE_LAST_PIN, is too much
    }
}

void fn_LAST_PIN(void){

}

void fn_BLOCK_ACCESS(void){
    printf("Access blocked \n");
    block_access();
    cur_state = STATE_WAIT_RESET_DOOR;
}

void fn_WAIT_RESET_DOOR(void){
    printf("Wait door to be reset \n");
    wait_reset_door();
    cur_state = STATE_INSERT_PIN;
    //if telegram or RFID
    //  cur_state = STATE_INSERT_PIN;
}

// ---------------------------------------------//

// Function to run in the main
void FSM_Run(void)
{
    //THE INIT STATE MUST STAY OUTSIDE OF THE FSM, BECAUSE IF NOT, IT WILL FOREVER STAY IN LPM0
    PCM_gotoLPM0();


    if(cur_state < NUM_STATES){
        (*fsm[cur_state].state_function)();
    }
    else{
        // Gestione errore stato non valido
    }
}
