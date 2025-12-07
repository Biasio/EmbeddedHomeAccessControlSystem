#include "display.h"

//define first position for the rectangle used to select the numbers
Rectangle sel_rectangle_on_grid = {6, 39, 6, 39};

//define rectangle for selection in admin menu
Rectangle sel_rectangle_on_admin_menu = {2, 126, 37, 67};

bool move_on_menu = 0; //used to decide the color of the rectangle in base of the type of screen (grid or menu)
bool first_screen = 1; //in the admin menu you are in the first screen (first 3 entries)

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
    for(i=2; i<=128; i+=RECTANGLE_SHIFT_ON_GRID){
        Graphics_drawLineH(&g_sContext, 2, 125, i);
        Graphics_drawLineV(&g_sContext, i, 2, 125);
    }

    //draw the numbers on the grid
    char string[1];
    int x,y;
    i=1;
    for(y=21; y<=106; y+=RECTANGLE_SHIFT_ON_GRID){
        for(x=24; x<=106; x+=RECTANGLE_SHIFT_ON_GRID){
            sprintf(string, "%d", i++);
            Graphics_drawStringCentered(&g_sContext, (int8_t *) string,
                                        AUTO_STRING_LENGTH,
                                        x, y,
                                        OPAQUE_TEXT);
        }
    }
    //draw rectangle in his inital position (NUMBER 1)
    draw_rectangle(1, sel_rectangle_on_grid.pos_x1, sel_rectangle_on_grid.pos_y1, sel_rectangle_on_grid.pos_x2, sel_rectangle_on_grid.pos_y2);

}


void draw_rectangle(bool new_pos, int16_t x1, int16_t y1, int16_t x2, int16_t y2)
{
    //if move_on_menu=1 and new_pos=0 cancel the old rectangle on menu
    //if move_on_menu=0 and new_pos=0 cancel the old rectangle on grid
    //if new_pos=1 draw the rectangle in the updated position
    if(move_on_menu & !new_pos) Graphics_setForegroundColor(&g_sContext, ClrBlack);
    else if(!move_on_menu & !new_pos) Graphics_setForegroundColor(&g_sContext, ClrWhite);
    else Graphics_setForegroundColor(&g_sContext, ClrRed);

    const Graphics_Rectangle rectangle = {x1, y1, x2, y2};
    Graphics_drawRectangle(&g_sContext, &rectangle);
}


//le seguenti funzioni di spostamento del rettangolo dovrebbero funzionare
//l'unica cosa da vedere sono i limiti (UPPER E LOWER), se mai li sposto in move_on_grid()

void move_rectangle_right(Rectangle* rectangle, int16_t shift){

        draw_rectangle(0, rectangle->pos_x1, rectangle->pos_y1, rectangle->pos_x2, rectangle->pos_y2);

        rectangle->pos_x1 += shift;
        rectangle->pos_x2 += shift;

        draw_rectangle(1, rectangle->pos_x1, rectangle->pos_y1, rectangle->pos_x2, rectangle->pos_y2);
}

void move_rectangle_left(Rectangle* rectangle, int16_t shift){

        draw_rectangle(0, rectangle->pos_x1, rectangle->pos_y1, rectangle->pos_x2, rectangle->pos_y2);

        rectangle->pos_x1 -= shift;
        rectangle->pos_x2 -= shift;

        draw_rectangle(1, rectangle->pos_x1, rectangle->pos_y1, rectangle->pos_x2, rectangle->pos_y2);
}

void move_rectangle_up(Rectangle* rectangle, int16_t shift){

        draw_rectangle(0, rectangle->pos_x1, rectangle->pos_y1, rectangle->pos_x2, rectangle->pos_y2);

        rectangle->pos_y1 -= shift;
        rectangle->pos_y2 -= shift;

        draw_rectangle(1, rectangle->pos_x1, rectangle->pos_y1, rectangle->pos_x2, rectangle->pos_y2);
}

void move_rectangle_down(Rectangle* rectangle, int16_t shift){

        draw_rectangle(0, rectangle->pos_x1, rectangle->pos_y1, rectangle->pos_x2, rectangle->pos_y2);

        rectangle->pos_y1 += shift;
        rectangle->pos_y2 += shift;

        draw_rectangle(1, rectangle->pos_x1, rectangle->pos_y1, rectangle->pos_x2, rectangle->pos_y2);
}

void move_rectangle_on_display( uint16_t x, uint16_t y, bool grid_on){

    const int RIGHT = 16000;
    const int LEFT = 300;
    const int UP = 16000;
    const int DOWN = 100;

    const int UPPER_LIMIT = 80;
    const int LOWER_LIMIT = 40;

    //move rectangle on grid
    if(grid_on){
       move_on_menu = 0;

       if(x>RIGHT) {
           if(sel_rectangle_on_grid.pos_x1>UPPER_LIMIT) {
               move_rectangle_right(&sel_rectangle_on_grid, RECTANGLE_SHIFT_ON_GRID);
           }
       }
       if(x<LEFT) {
           if(sel_rectangle_on_grid.pos_x1>LOWER_LIMIT) {
               move_rectangle_left(&sel_rectangle_on_grid, RECTANGLE_SHIFT_ON_GRID);
           }
       }
       if(y>UP) {
           if(sel_rectangle_on_grid.pos_x1>LOWER_LIMIT){
               move_rectangle_up(&sel_rectangle_on_grid, RECTANGLE_SHIFT_ON_GRID);
           }
       }
       if(y<DOWN) {
           if(sel_rectangle_on_grid.pos_y1<UPPER_LIMIT) {
               move_rectangle_down(&sel_rectangle_on_grid, RECTANGLE_SHIFT_ON_GRID);
           }
       }
    }
    else{ //move rectangle on menu
       move_on_menu = 1;
       if(y>UP) {
          if(sel_rectangle_on_admin_menu.pos_y1<LOWER_LIMIT && !first_screen) {
              first_screen = 1; //change page
              draw_admin_menu(first_screen);
          }
          if(sel_rectangle_on_admin_menu.pos_y1>LOWER_LIMIT) {
            move_rectangle_up(&sel_rectangle_on_admin_menu, RECTANGLE_SHIFT_ON_MENU);
          }
       }
       if(y<DOWN) {

           if(sel_rectangle_on_admin_menu.pos_y1>UPPER_LIMIT+10 && first_screen) {
               first_screen = 0; //change page
               draw_admin_menu(first_screen);
           }
           if(sel_rectangle_on_admin_menu.pos_y1<UPPER_LIMIT) {
              move_rectangle_down(&sel_rectangle_on_admin_menu, RECTANGLE_SHIFT_ON_MENU);
          }

       }
    }
}


void number_selected(void){
    const Graphics_Rectangle rect = {sel_rectangle_on_grid.pos_x1,
                                     sel_rectangle_on_grid.pos_y1,
                                     sel_rectangle_on_grid.pos_x2,
                                     sel_rectangle_on_grid.pos_y2};

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
                                        sel_rectangle_on_grid.pos_x1+18, sel_rectangle_on_grid.pos_y1+15,
                                        OPAQUE_TEXT);


            Graphics_setForegroundColor(&g_sContext, ClrRed);
            Graphics_drawRectangle(&g_sContext, &rect);

            // Stop at the right number
                break;
        }
    }
}

void draw_admin_menu(bool screen_number){

    Graphics_clearDisplay(&g_sContext);

    int32_t x_string = 64;
    int32_t y_string = 20;
    int32_t y_line = 37;
    int32_t start_v_line = y_line;
    int32_t start_x_line = 2;
    int32_t end_x_line = 126;

    int start, end;

    Graphics_setForegroundColor(&g_sContext, ClrBlack);
    GrContextFontSet(&g_sContext, &g_sFontCmss12);
     //in case of other pages, use an int to count the number of pages
     if(screen_number){ //first page
         start = 0;
         end = 3;

         Graphics_drawStringCentered(&g_sContext, (int8_t *) "Page 1/2",
                                        AUTO_STRING_LENGTH,
                                        23, 5,
                                        OPAQUE_TEXT);
     }
     else{   //second page
         start = 3;
         end = 6;

         Graphics_drawStringCentered(&g_sContext, (int8_t *) "Page 2/2",
                                     AUTO_STRING_LENGTH,
                                     23, 5,
                                     OPAQUE_TEXT);
     }

    char* strings[] = {"LAST ACCESS LOG",
                       "SETUP PIN",
                       "WIFI PIN",
                       "FACTORY RESET",
                       "UNLOCK DOOR",
                       "BLOCK PIN INSERT"};

    GrContextFontSet(&g_sContext, &g_sFontCmss16);
    Graphics_setForegroundColor(&g_sContext, ClrRed);

    Graphics_drawStringCentered(&g_sContext, (int8_t *) "ADMIN MENU",
                                        AUTO_STRING_LENGTH,
                                        x_string, y_string,
                                        OPAQUE_TEXT);
    y_string+=30;

    Graphics_setForegroundColor(&g_sContext, ClrBlack);



    int i;
    for(i=start; i<end; i++){
        Graphics_drawStringCentered(&g_sContext, (int8_t *) strings[i],
                                    AUTO_STRING_LENGTH,
                                    x_string, y_string,
                                    OPAQUE_TEXT);
        Graphics_drawLineH(&g_sContext, start_x_line, end_x_line, y_line);
        y_string+=30;
        y_line+=30;
    }

    Graphics_drawLineH(&g_sContext, start_x_line, end_x_line, y_line);

    Graphics_drawLineV(&g_sContext, start_x_line, start_v_line, y_line);
    Graphics_drawLineV(&g_sContext, end_x_line, start_v_line, y_line);

    sel_rectangle_on_admin_menu.pos_x1 = start_x_line;
    sel_rectangle_on_admin_menu.pos_y1 = start_v_line;
    sel_rectangle_on_admin_menu.pos_x2 = end_x_line;
    sel_rectangle_on_admin_menu.pos_y2 = start_v_line+30;

    draw_rectangle(1, start_x_line, start_v_line, end_x_line, start_v_line+30);
    //draw_rectangle(1, sel_rectangle_on_admin_menu.pos_x1, sel_rectangle_on_admin_menu.pos_y1, sel_rectangle_on_admin_menu.pos_x2, sel_rectangle_on_admin_menu.pos_y2);

}


