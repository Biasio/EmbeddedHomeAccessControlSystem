#ifndef FSM_H
#define FSM_H

#include "msp.h"
#include <stdio.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/*
 * This header file defines the states of the system
 */

typedef enum{
    STATE_BOOT,
    STATE_DOOR_LOCKED,
    STATE_INSERT_PIN,
    STATE_OPEN_DOOR,
    STATE_WAIT_RFID, //after the admin insert the pin, wait for the RFID to access menu
                     //we should consider the case in which the RFID doesn't arrive (maybe a timer)
    STATE_ADMIN_MENU, //there must be other states for each functionality

    STATE_LAST_ACCESS_LOG,
    STATE_SETUP_PIN,
    STATE_SETUP_WIFI,
    STATE_FACTORY_RESET,
    STATE_UNLOCK_DOOR,
    STATE_BLOCK_PIN,

    STATE_WRONG_PIN,
    STATE_LAST_PIN,
    STATE_BLOCK_ACCESS,
    STATE_WAIT_RESET_DOOR, //after this return to STATE_DOOR_LOCKED o STATE_INSERT_PIN
    NUM_STATES
}State_t;

typedef struct{
    State_t state;
    void (*state_function)(void);
} StateMachine_t;

void fn_BOOT(void);
void fn_DOOR_LOCKED(void);

void fn_DRAW_GRID(void);

void fn_INSERT_PIN(void);
void fn_OPEN_DOOR(void);
void fn_WAIT_RFID(void);
void fn_ADMIN_MENU(void);
void fn_WRONG_PIN(void);
void fn_LAST_PIN(void);
void fn_BLOCK_ACCESS(void);
void fn_WAIT_RESET_DOOR(void);

void fn_menu_lal(void);
void fn_menu_setup_pin(void);
void fn_menu_wifi(void);
void fn_menu_fact_reset(void);
void fn_menu_unlock_door(void);
void fn_menu_block_pin(void);

// Function to run in the loop
void FSM_Run(void);

//initialize hardware
void _hwInit(); //maybe it will substitued by fn_boot()

#endif
