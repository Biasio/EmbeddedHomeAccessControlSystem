#include "msp.h"
#include <stdio.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>


typedef enum{
    STATE_BOOT,
    STATE_DOOR_LOCKED,
    STATE_INSERT_PIN,
    STATE_OPEN_DOOR,
    STATE_WAIT_RFID, //after the admin insert the pin, wait for the RFID to access menu
                     //we should consider the case in which the RFID doesn't arrive (maybe a timer)
    STATE_ADMIN_MENU, //there must be other states for each functionality
    STATE_WRONG_PIN,
    STATE_LAST_PIN,
    STATE_BLOCK_ACCESS,
    STATE_WAIT_RESET_DOOR, //after this return to STATE_DOOR_LOCKED o STATE_INSERT_PIN
}State_t;

typedef struct{
    State_t state;
    void (*state_function)(void);
} StateMachine_t;

void fn_BOOT(void);
void fn_DOOR_LOCKED(void);
void fn_INSERT_PIN(void);
void fn_OPEN_DOOR(void);
void fn_WAIT_RFID(void);
void fn_ADMIN_MENU(void);
void fn_WRONG_PIN(void);
void fn_LAST_PIN(void);
void fn_BLOCK_ACCESS(void);
void fn_WAIT_RESET_DOOR(void);


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

void fn_BOOT(void){
    printf("Boot \n");
    boot();
    cur_state = STATE_DOOR_LOCKED;
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
    block_access();
    //if telegram or RFID
    //  cur_state = STATE_INSERT_PIN;
}


State_t cur_state = STATE_BOOT;

int main(void)
{

    while(1){
        PCM_gotoLPM0();
        if(cur_state < NUM_STATES){
            (*fsm[cur_state].state_function)();
        }
        else{
            //error
        }
    }
}

