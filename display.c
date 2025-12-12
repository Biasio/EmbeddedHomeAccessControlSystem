#include "display.h"

//define first position for the rectangle used to select the numbers
Rectangle sel_rectangle_on_grid = {22, 48, 32, 58};

//define rectangle for selection in admin menu
Rectangle sel_rectangle_on_admin_menu = {2, 126, 37, 67};

bool move_on_menu = 0; //used to decide the color of the rectangle in base of the type of screen (grid or menu)
bool first_screen = 1; //in the admin menu you are in the first screen (first 3 entries)

//these points are used to select the numbers on the grid
//at each point corresponds a number
const Point GRID_POINTS[] = {
     // P1 | P2 | P3
     { 35, 45 },
     { 55, 45 },
     { 85, 45 },
     // P4 | P5 | P6
     { 35, 75 },
     { 55, 75 },
     { 85, 75 },
     // P7 | P8 | P9
     { 35, 105 },
     { 55, 105 },
     { 85, 105 }
};

const Point MENU_POINTS[] = {
     // P1 | P2 | P3
     { 50, 50 },
     { 50, 80 },
     { 50, 110 },
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
    Graphics_clearDisplay(&g_sContext);
    GrContextFontSet(&g_sContext, &g_sFontCmss24);
    Graphics_setForegroundColor(&g_sContext, ClrBlack);

    int start_x = 20;
    int end_x = 110;

    int start_y = 30;
    int end_y = 120;

    int i;
    //the lines of the grid are shifted of the same as when the rectangle is shifted
    for(i=start_y; i<=end_y; i+=RECTANGLE_SHIFT_ON_GRID){
        Graphics_drawLineH(&g_sContext, start_x, end_x, i);
    }
    for(i=start_x; i<=end_x; i+=RECTANGLE_SHIFT_ON_GRID){
        Graphics_drawLineV(&g_sContext, i, start_y, end_y);
    }

    //draw the numbers on the grid
    char string[1];
    int x,y;
    i=1;

    for(y=start_y+15; y<=end_y-15; y+=RECTANGLE_SHIFT_ON_GRID){
        for(x=start_x+15; x<=end_x-15; x+=RECTANGLE_SHIFT_ON_GRID){
            sprintf(string, "%d", i++);
            Graphics_drawStringCentered(&g_sContext, (int8_t *) string,
                                        AUTO_STRING_LENGTH,
                                        x, y,
                                        OPAQUE_TEXT);
        }
    }
    //draw rectangle in his inital position (NUMBER 1)
    draw_rectangle(1, sel_rectangle_on_grid.pos_x1, sel_rectangle_on_grid.pos_y1, sel_rectangle_on_grid.pos_x2, sel_rectangle_on_grid.pos_y2);


    //draw number selected
    GrContextFontSet(&g_sContext, &g_sFontCmss16);
    Graphics_setForegroundColor(&g_sContext, ClrBlack);

    Graphics_drawLineH(&g_sContext, 30, 39, 25);
    Graphics_drawLineH(&g_sContext, 50, 59, 25);
    Graphics_drawLineH(&g_sContext, 70, 79, 25);
    Graphics_drawLineH(&g_sContext, 90, 99, 25);

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

         first_screen=1;

         start = 0;
         end = 3;

         Graphics_drawStringCentered(&g_sContext, (int8_t *) "Page 1/2",
                                        AUTO_STRING_LENGTH,
                                        23, 5,
                                        OPAQUE_TEXT);
     }
     else{   //second page

         first_screen=0;

         start = 3;
         end = 6;

         Graphics_drawStringCentered(&g_sContext, (int8_t *) "Page 2/2",
                                     AUTO_STRING_LENGTH,
                                     23, 5,
                                     OPAQUE_TEXT);
     }

    char* strings[] = {"LAST ACCESS LOG",
                       "SETUP PIN",
                       "SETUP WIFI",
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

    draw_rectangle(1, sel_rectangle_on_admin_menu.pos_x1, sel_rectangle_on_admin_menu.pos_y1, sel_rectangle_on_admin_menu.pos_x2, sel_rectangle_on_admin_menu.pos_y2);

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
           if(sel_rectangle_on_grid.pos_x1<UPPER_LIMIT) {
               move_rectangle_right(&sel_rectangle_on_grid, RECTANGLE_SHIFT_ON_GRID);
           }
       }
       if(x<LEFT) {
           if(sel_rectangle_on_grid.pos_x1>LOWER_LIMIT) {
               move_rectangle_left(&sel_rectangle_on_grid, RECTANGLE_SHIFT_ON_GRID);
           }
       }
       if(y>UP) {
           if(sel_rectangle_on_grid.pos_y1>LOWER_LIMIT){
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


int number_selected(void){
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

            GrContextFontSet(&g_sContext, &g_sFontCmss24);
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
                                        sel_rectangle_on_grid.pos_x1+13, sel_rectangle_on_grid.pos_y1+13,
                                        OPAQUE_TEXT);


            Graphics_setForegroundColor(&g_sContext, ClrRed);
            Graphics_drawRectangle(&g_sContext, &rect);

            // Stop at the right number
            return i+1;
        }
    }
    return 0;
}

//select function on menu RETURN FUNCTION
int display_function_selected(void){
    const Graphics_Rectangle rect = {sel_rectangle_on_admin_menu.pos_x1,
                                     sel_rectangle_on_admin_menu.pos_y1,
                                     sel_rectangle_on_admin_menu.pos_x2,
                                     sel_rectangle_on_admin_menu.pos_y2};

    int selected_function;

    if(first_screen){ //FIRST SCREEN
        int i;
            for (i = 0; i <= 2; i++) //only 3 points for screen
            {
                // Verifica se il punto corrente (MENU_POINTS[i]) e' all'interno del rettangolo 'rect'
                if (Graphics_isPointWithinRectangle(
                        &rect,
                        MENU_POINTS[i].x,
                        MENU_POINTS[i].y))
                {

                    switch(i){
                    case 0:
                        printf("Last access log \n", i);
                        selected_function = LAST_ACCESS_LOG;
                        break;
                    case 1:
                        printf("pin_setup \n", i);
                        selected_function = SETUP_PIN;
                        break;
                    case 2:
                        printf("wifi_setup \n", i);
                        selected_function = WIFI_SETUP;
                        break;
                    default:
                        printf("Nothing \n", i);
                    }
                }
            }

    }else{ //SECOND SCREEN
        int i;
            for (i = 0; i <= 2; i++)
            {
                // Verifica se il punto corrente (MENU_POINTS[i]) e' all'interno del rettangolo 'rect'
                if (Graphics_isPointWithinRectangle(
                        &rect,
                        MENU_POINTS[i].x,
                        MENU_POINTS[i].y))
                {

                    switch(i){
                    case 0:
                        printf("factory_reset \n", i);
                        selected_function = FACTORY_RESET;
                        break;
                    case 1:
                        printf("unnlock_door \n", i);
                        selected_function = UNLOCK_DOOR;
                        break;
                    case 2:
                        printf("block_pin \n", i);
                        selected_function = BLOCK_PIN;
                        break;
                    default:
                        printf("Nothing \n", i);
                    }

                }
            }
    }

    return selected_function;
}



void display_menu_last_access_log(void){
    int32_t x_string = 64;
    int32_t y_string = 20;

    Graphics_clearDisplay(&g_sContext);

    GrContextFontSet(&g_sContext, &g_sFontCmss16);
    Graphics_setForegroundColor(&g_sContext, ClrRed);

    Graphics_drawStringCentered(&g_sContext, (int8_t *) "LAST ACCESS LOG",
                                AUTO_STRING_LENGTH,
                                x_string, y_string,
                                OPAQUE_TEXT);
    Graphics_setForegroundColor(&g_sContext, ClrBlack);
}

void display_menu_setup_pin(void){
    display_string("SETUP PIN");
    draw_grid();
}

void display_menu_setup_wifi(void){
    int32_t x_string = 64;
    int32_t y_string = 20;

    Graphics_clearDisplay(&g_sContext);

    GrContextFontSet(&g_sContext, &g_sFontCmss16);
    Graphics_setForegroundColor(&g_sContext, ClrRed);

    Graphics_drawStringCentered(&g_sContext, (int8_t *) "SETUP WIFI",
                                AUTO_STRING_LENGTH,
                                x_string, y_string,
                                OPAQUE_TEXT);
    Graphics_setForegroundColor(&g_sContext, ClrBlack);
}

void display_menu_factory_reset(void){
    int32_t x_string = 64;
    int32_t y_string = 20;

    Graphics_clearDisplay(&g_sContext);

    GrContextFontSet(&g_sContext, &g_sFontCmss16);
    Graphics_setForegroundColor(&g_sContext, ClrRed);

    Graphics_drawStringCentered(&g_sContext, (int8_t *) "FACTORY RESET",
                                AUTO_STRING_LENGTH,
                                x_string, y_string,
                                OPAQUE_TEXT);
    Graphics_setForegroundColor(&g_sContext, ClrBlack);
}

void display_menu_unlock_door(void){
    int32_t x_string = 64;
    int32_t y_string = 20;

    Graphics_clearDisplay(&g_sContext);

    GrContextFontSet(&g_sContext, &g_sFontCmss16);
    Graphics_setForegroundColor(&g_sContext, ClrRed);

    Graphics_drawStringCentered(&g_sContext, (int8_t *) "UNLOCK DOOR",
                                AUTO_STRING_LENGTH,
                                x_string, y_string,
                                OPAQUE_TEXT);
    Graphics_setForegroundColor(&g_sContext, ClrBlack);
}

void display_menu_block_pin(void){
    int32_t x_string = 64;
    int32_t y_string = 20;

    Graphics_clearDisplay(&g_sContext);

    GrContextFontSet(&g_sContext, &g_sFontCmss16);
    Graphics_setForegroundColor(&g_sContext, ClrRed);

    Graphics_drawStringCentered(&g_sContext, (int8_t *) "BLOCK PIN",
                                AUTO_STRING_LENGTH,
                                x_string, y_string,
                                OPAQUE_TEXT);
    Graphics_setForegroundColor(&g_sContext, ClrBlack);
}


// -------------------------------------- //

//Maybe is better to build a function that displays the string that I pass

void display_door_open(void){
    Graphics_clearDisplay(&g_sContext);
    GrContextFontSet(&g_sContext, &g_sFontCmss16);
    Graphics_drawStringCentered(&g_sContext, (int8_t *) "CODE CORRECT",
                                    AUTO_STRING_LENGTH,
                                    64, 54,
                                    OPAQUE_TEXT);
    Graphics_drawStringCentered(&g_sContext, (int8_t *) "OPENING DOOR",
                                        AUTO_STRING_LENGTH,
                                        64, 74,
                                        OPAQUE_TEXT);
}

void display_wait_RFID(void){
    Graphics_clearDisplay(&g_sContext);
    GrContextFontSet(&g_sContext, &g_sFontCmss16);
    Graphics_drawStringCentered(&g_sContext, (int8_t *) "PLEASE, USE RFID",
                                    AUTO_STRING_LENGTH,
                                    64, 64,
                                    OPAQUE_TEXT);
}

void display_wrong_pin(int error_pin){
    Graphics_clearDisplay(&g_sContext);
    GrContextFontSet(&g_sContext, &g_sFontCmss16);
    Graphics_drawStringCentered(&g_sContext, (int8_t *) "WRONG PIN",
                                    AUTO_STRING_LENGTH,
                                    64, 64,
                                    OPAQUE_TEXT);
    char string[20];
    sprintf(string, "ERROR %d/3", error_pin);
    Graphics_drawStringCentered(&g_sContext, (int8_t *) string,
                                        AUTO_STRING_LENGTH,
                                        64, 84,
                                        OPAQUE_TEXT);
    int i;
    for(i=0;i<1000000;i++); //simulate opening of the door, IS BETTER TO USE A TIMER
}

void display_block_access(void){
    Graphics_clearDisplay(&g_sContext);
    GrContextFontSet(&g_sContext, &g_sFontCmss16);
    Graphics_drawStringCentered(&g_sContext, (int8_t *) "ACCESS BLOCKED",
                                    AUTO_STRING_LENGTH,
                                    64, 64,
                                    OPAQUE_TEXT);
}

void display_clock(int hour, int minute){
    Graphics_clearDisplay(&g_sContext);
    GrContextFontSet(&g_sContext, &g_sFontCmss16);

    char string[20];
    sprintf(string, "%d : %d", hour, minute);

    Graphics_drawStringCentered(&g_sContext, (int8_t *) string,
                                    AUTO_STRING_LENGTH,
                                    64, 64,
                                    OPAQUE_TEXT);
}

void display_string(const char* string){
    Graphics_clearDisplay(&g_sContext);
    GrContextFontSet(&g_sContext, &g_sFontCmss16);
    Graphics_drawStringCentered(&g_sContext, (int8_t *) string,
                                    AUTO_STRING_LENGTH,
                                    64, 64,
                                    OPAQUE_TEXT);
    int i;
    for(i=0;i<1000000;i++); //IS BETTER TO USE A TIMER FOR DELAY
}

