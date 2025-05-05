#include <string.h>
#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"
#include <string.h>
#include "keymap.h"
#include QMK_KEYBOARD_H

#ifndef __KEYPAD_SCREEN_C
    #define KEYPAD_SCREEN_EXTERN extern
#else
    #define KEYPAD_SCREEN_EXTERN
#endif

KEYPAD_SCREEN_EXTERN lv_obj_t* btn_bks;
KEYPAD_SCREEN_EXTERN lv_obj_t* btn_div;
KEYPAD_SCREEN_EXTERN lv_obj_t* btn_mul;
KEYPAD_SCREEN_EXTERN lv_obj_t* btn_min;
KEYPAD_SCREEN_EXTERN lv_obj_t* btn_7;
KEYPAD_SCREEN_EXTERN lv_obj_t* btn_8;
KEYPAD_SCREEN_EXTERN lv_obj_t* btn_9;
KEYPAD_SCREEN_EXTERN lv_obj_t* btn_plus;
KEYPAD_SCREEN_EXTERN lv_obj_t* btn_4;
KEYPAD_SCREEN_EXTERN lv_obj_t* btn_5;
KEYPAD_SCREEN_EXTERN lv_obj_t* btn_6;
KEYPAD_SCREEN_EXTERN lv_obj_t* btn_1;
KEYPAD_SCREEN_EXTERN lv_obj_t* btn_2;
KEYPAD_SCREEN_EXTERN lv_obj_t* btn_3;
KEYPAD_SCREEN_EXTERN lv_obj_t* btn_ent;
KEYPAD_SCREEN_EXTERN lv_obj_t* btn_0;
KEYPAD_SCREEN_EXTERN lv_obj_t* btn_dot;

#ifdef __KEYPAD_SCREEN_C
    #define NUM_PAD_BUTTON_SIZE_X 50
    #define NUM_PAD_BUTTON_SIZE_Y 25
    #define NUM_PAD_BUTTON_SPACE_X 6
    #define NUM_PAD_BUTTON_SPACE_Y 6
    #define NUM_PAD_X_OFFSET_FROM_LEFT 10
    #define NUM_PAD_Y_OFFSET_FROM_TOP 0
    #define BUTTON_ALIGN_STYLE LV_ALIGN_DEFAULT

    struct lv_keypad_btn_location
    {
        int32_t btn_size_x;
        int32_t btn_size_y;
        int32_t btn_align_x;
        int32_t btn_align_y;
    };

    typedef void (*lv_obj_state_fptr)(lv_obj_t *);
#endif

void lv_keypad_screen_create(lv_obj_t *parent_screen);
