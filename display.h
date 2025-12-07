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


//used to access the array GRID_POINTS easily
typedef enum {
    NUM1, NUM2, NUM3, NUM4, NUM5, NUM6, NUM7, NUM8, NUM9, NUM_POINTS
} PointIndex;


//variable used to define the display
Graphics_Context g_sContext;

void _graphicsInit();

void draw_grid(void);
void draw_rectangle(bool new_pos, int16_t x1, int16_t y1, int16_t x2, int16_t y2);

void draw_admin_menu(bool screen_number);

void move_rectangle_right(Rectangle* rectangle, int16_t shift);
void move_rectangle_left(Rectangle* rectangle, int16_t shift);
void move_rectangle_up(Rectangle* rectangle, int16_t shift);
void move_rectangle_down(Rectangle* rectangle, int16_t shift);
void number_selected(void);

void move_rectangle_on_display( uint16_t x, uint16_t y, bool grid_on);

#endif
