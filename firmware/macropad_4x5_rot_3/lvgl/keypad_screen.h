#include "keymap.h"
#include QMK_KEYBOARD_H
#include "GUI_helper.h"

#ifndef __KEPAD_SCREEN_C
    #define KEYPAD_SCREEN_EXTERN
#else
    #define KEYPAD_SCREEN_EXTERN extern
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
KEYPAD_SCREEN_EXTERN lv_obj_t* KPAD_spVolumeObj;
KEYPAD_SCREEN_EXTERN lv_obj_t* KPAD_spVolumeLbl;
KEYPAD_SCREEN_EXTERN lv_obj_t* KPAD_spVolumeTxt;

#ifdef __KEYPAD_SCREEN_C

#define NUM_PAD_BUTTON_SIZE_X 40
#define NUM_PAD_BUTTON_SIZE_Y 25
#define NUM_PAD_BUTTON_SPACE_X 5
#define NUM_PAD_BUTTON_SPACE_Y 5
#define NUM_PAD_X_OFFSET_FROM_LEFT 10
#define NUM_PAD_Y_OFFSET_FROM_TOP 10
#define BUTTON_ALIGN_STYLE LV_ALIGN_DEFAULT

typedef void (*lv_obj_state_fptr)(lv_obj_t *);

#endif /* end #ifdef __KEYPAD_SCREEN_C */

void KPAD_vScreenCreate(lv_obj_t *parent_screen);
