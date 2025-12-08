#ifndef DISPLAY_H
#define DISPLAY_H

#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"
#include <stdio.h>

#define RECTANGLE_SHIFT_ON_GRID 41
#define RECTANGLE_SHIFT_ON_MENU 30

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    int pos_x1;
    int pos_x2;
    int pos_y1;
    int pos_y2;
}Rectangle;

//Functions raggruppa le funzioni del menu admin
//quando si preme su una di esse si attiva un solo valore
typedef struct {
    bool last_access_log;
    bool pin_setup;
    bool wifi_setup;
    bool factory_reset;
    bool unnlock_door;
    bool block_pin;
}Functions;


//used to access the array GRID_POINTS easily
typedef enum {
    NUM1, NUM2, NUM3, NUM4, NUM5, NUM6, NUM7, NUM8, NUM9, NUM_POINTS
} PointIndex;

//functions inside admin menu
typedef enum {
    FUNCTION_NONE, LAST_ACCESS_LOG, SETUP_PIN, WIFI_SETUP, FACTORY_RESET, UNLOCK_DOOR, BLOCK_PIN, NUM_FUNCTION
} enum_menu_functions;


//variable used to define the display
Graphics_Context g_sContext;

void _graphicsInit();

void draw_grid(void);
void draw_admin_menu(bool screen_number);

void number_selected(void);
void function_selected(void);

void move_rectangle_on_display( uint16_t x, uint16_t y, bool grid_on);

void menu_last_access_log(void);
void menu_setup_pin(void);
void menu_setup_wifi(void);
void menu_factory_reset(void);
void menu_unlock_door(void);
void menu_block_pin(void);

#endif
