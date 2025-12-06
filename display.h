#ifndef DISPLAY_H
#define DISPLAY_H

#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"
#include <stdio.h>

#define RECTANGLE_SHIFT 41
#define UPPER_LIMIT 80
#define LOWER_LIMIT 40

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

void _hwInit(void);

void draw_grid(void);
void draw_rectangle(bool new_pos);

void move_rectangle_right(void);
void move_rectangle_left(void);
void move_rectangle_up(void);
void move_rectangle_down(void);
void number_selected(void);

#endif
