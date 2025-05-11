#include <string.h>
#include <string.h>
#include "keymap.h"
#include QMK_KEYBOARD_H
#include "GUI_include.h"

lv_obj_t* btn_bks;
lv_obj_t* btn_div;
lv_obj_t* btn_mul;
lv_obj_t* btn_min;
lv_obj_t* btn_7;
lv_obj_t* btn_8;
lv_obj_t* btn_9;
lv_obj_t* btn_plus;
lv_obj_t* btn_4;
lv_obj_t* btn_5;
lv_obj_t* btn_6;
lv_obj_t* btn_1;
lv_obj_t* btn_2;
lv_obj_t* btn_3;
lv_obj_t* btn_ent;
lv_obj_t* btn_0;
lv_obj_t* btn_dot;

#ifdef __KEYPAD_SCREEN_C
    #define NUM_PAD_BUTTON_SIZE_X 40
    #define NUM_PAD_BUTTON_SIZE_Y 25
    #define NUM_PAD_BUTTON_SPACE_X 5
    #define NUM_PAD_BUTTON_SPACE_Y 5
    #define NUM_PAD_X_OFFSET_FROM_LEFT 10
    #define NUM_PAD_Y_OFFSET_FROM_TOP 10
    #define BUTTON_ALIGN_STYLE LV_ALIGN_DEFAULT

    typedef void (*lv_obj_state_fptr)(lv_obj_t *);
#endif

void KPAD_vScreenCreate(lv_obj_t *parent_screen);
