#include "display.h"

//define first position for the rectangle used to select the numbers
Rectangle sel_rectangle = {6, 39, 6, 39};

//these points are used to select the numbers on the grid
//at each point corresponds a number
const Point GRID_POINTS[] = {
     // P1 | P2 | P3
     { 10, 10 },
     { 50, 10 },
     { 90, 10 },
     // P4 | P5 | P6
     { 10, 50 },
     { 50, 50 },
     { 90, 50 },
     // P7 | P8 | P9
     { 10, 90 },
     { 50, 90 },
     { 90, 90 }
};

void _graphicsInit()
{
    /* Initializes display */
    Crystalfontz128x128_Init();

    /* Set default screen orientation */
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);

    /* Initializes graphics context */
    Graphics_initContext(&g_sContext, &g_sCrystalfontz128x128, &g_sCrystalfontz128x128_funcs);
    Graphics_setForegroundColor(&g_sContext, ClrBlack);
    Graphics_setBackgroundColor(&g_sContext, ClrWhite);
    GrContextFontSet(&g_sContext, &g_sFontCmss36);
    Graphics_clearDisplay(&g_sContext);
}


void draw_grid(void)
{
    Graphics_setForegroundColor(&g_sContext, ClrBlack);
    int i;
    //the lines of the grid are shifted of the same as when the rectangle is shifted
    for(i=2; i<=128; i+=RECTANGLE_SHIFT){
        Graphics_drawLineH(&g_sContext, 2, 125, i);
        Graphics_drawLineV(&g_sContext, i, 2, 125);
    }

    //draw the numbers on the grid
    char string[1];
    int x,y;
    i=1;
    for(y=21; y<=106; y+=RECTANGLE_SHIFT){
        for(x=24; x<=106; x+=RECTANGLE_SHIFT){
            sprintf(string, "%d", i++);
            Graphics_drawStringCentered(&g_sContext, (int8_t *) string,
                                        AUTO_STRING_LENGTH,
                                        x, y,
                                        OPAQUE_TEXT);
        }
    }
    //draw rectangle in his inital position (NUMBER 1)
    draw_rectangle(1);

}


void draw_rectangle(bool new_pos)
{
    //if new_pos=0 cancel the old rectangle
    //if new_pos=1 draw the rectangle in the updated position
    if(!new_pos) Graphics_setForegroundColor(&g_sContext, ClrWhite);
    else Graphics_setForegroundColor(&g_sContext, ClrRed);

    const Graphics_Rectangle rectangle = {sel_rectangle.pos_x1,
                                          sel_rectangle.pos_y1,
                                          sel_rectangle.pos_x2,
                                          sel_rectangle.pos_y2};
    Graphics_drawRectangle(&g_sContext, &rectangle);
}

void move_rectangle_right(void){
    if(sel_rectangle.pos_x1<UPPER_LIMIT)
    {
        draw_rectangle(0); 
        sel_rectangle.pos_x1 += RECTANGLE_SHIFT;
        sel_rectangle.pos_x2 += RECTANGLE_SHIFT;

        draw_rectangle(1); 
    }
}



void move_rectangle_left(void){
    if(sel_rectangle.pos_x1>LOWER_LIMIT)
    {
        draw_rectangle(0); 

        sel_rectangle.pos_x1 -= RECTANGLE_SHIFT;
        sel_rectangle.pos_x2 -= RECTANGLE_SHIFT;

        draw_rectangle(1); 
    }
}

void move_rectangle_up(void){
    if(sel_rectangle.pos_y1>LOWER_LIMIT)
    {
        draw_rectangle(0); 

        sel_rectangle.pos_y1 -= RECTANGLE_SHIFT;
        sel_rectangle.pos_y2 -= RECTANGLE_SHIFT;

        draw_rectangle(1); 
    }
}

void move_rectangle_down(void){
    if(sel_rectangle.pos_y1<UPPER_LIMIT)
    {
        draw_rectangle(0); 

        sel_rectangle.pos_y1 += RECTANGLE_SHIFT;
        sel_rectangle.pos_y2 += RECTANGLE_SHIFT;

        draw_rectangle(1); 
    }
}

void number_selected(void){
    const Graphics_Rectangle rect = {sel_rectangle.pos_x1,
                                     sel_rectangle.pos_y1,
                                     sel_rectangle.pos_x2,
                                     sel_rectangle.pos_y2};

    int i;
    for (i = NUM1; i < NUM_POINTS; i++)
    {
        // Verifica se il punto corrente (GRID_POINTS[i]) e' all'interno del rettangolo 'rect'
        if (Graphics_isPointWithinRectangle(
                &rect,
                GRID_POINTS[i].x,
                GRID_POINTS[i].y))
        {
            // Se il punto e' all'interno, stampa il suo numero (i + 1)
            printf("Number: %d\n", i + 1);

            Graphics_setForegroundColor(&g_sContext, ClrRed);
            Graphics_fillRectangle(&g_sContext, &rect);
            int j;
            for(j=0;j<100000;j++);
            Graphics_setForegroundColor(&g_sContext, ClrWhite);
            Graphics_fillRectangle(&g_sContext, &rect);


            char string[2];

            Graphics_setForegroundColor(&g_sContext, ClrBlack);

            sprintf(string, "%d", i+1);
            Graphics_drawStringCentered(&g_sContext, (int8_t *) string,
                                        AUTO_STRING_LENGTH,
                                        sel_rectangle.pos_x1+18, sel_rectangle.pos_y1+15,
                                        OPAQUE_TEXT);


            Graphics_setForegroundColor(&g_sContext, ClrRed);
            Graphics_drawRectangle(&g_sContext, &rect);

            // Se vuoi fermarti alla prima corrispondenza:
                break;
        }
    }
}


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

    _graphicsInit();

}




