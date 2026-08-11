#pragma once
#include "GUI_helper.h"
#include QMK_KEYBOARD_H
#include "fonts/fa_font_list.h"

#define SPECIAL_BUTTON_COUNT 20
#define SPECIAL_KEYCOMBINATION_COUNT 6

#define SPECIAL_KEY_0   SAFE_RANGE
#define SPECIAL_KEY_1   SAFE_RANGE + 1
#define SPECIAL_KEY_2   SAFE_RANGE + 2
#define SPECIAL_KEY_3   SAFE_RANGE + 3
#define SPECIAL_KEY_4   SAFE_RANGE + 4
#define SPECIAL_KEY_5   SAFE_RANGE + 5
#define SPECIAL_KEY_6   SAFE_RANGE + 6
#define SPECIAL_KEY_7   SAFE_RANGE + 7
#define SPECIAL_KEY_8   SAFE_RANGE + 8
#define SPECIAL_KEY_9   SAFE_RANGE + 9
#define SPECIAL_KEY_10  SAFE_RANGE + 10
#define SPECIAL_KEY_11  SAFE_RANGE + 11
#define SPECIAL_KEY_12  SAFE_RANGE + 12
#define SPECIAL_KEY_13  SAFE_RANGE + 13
#define SPECIAL_KEY_14  SAFE_RANGE + 14
#define SPECIAL_KEY_15  SAFE_RANGE + 15
#define SPECIAL_KEY_16  SAFE_RANGE + 16
#define SPECIAL_KEY_17  SAFE_RANGE + 17
#define SPECIAL_KEY_18  SAFE_RANGE + 18
#define SPECIAL_KEY_19  SAFE_RANGE + 19

#ifdef __SPECIAL_SCREEN_C

struct SPECIAL_stBtnInfo
{
    lv_obj_t * m_spBtn;
    const char * m_cpBtnName;
    const lv_font_t * m_spFontName;
};


static struct SPECIAL_stBtnInfo SPECIAL_staBtnInfo [SPECIAL_BUTTON_COUNT] =
{
    /*[0]*/
    {
        NULL,
        "uie",
        &lv_font_montserrat_14,
    },
    /*[1]*/
    {
        NULL,
        "pwd",
        &lv_font_montserrat_14,
    },
    /*[6]*/
    {
        NULL,
        "",
        &lv_font_montserrat_14,
    },
    /*[7]*/
    {
        NULL,
        "",
        &lv_font_montserrat_14,
    },
    /*[8]*/
    {
        NULL,
        "",
        &lv_font_montserrat_14,
    },
    /*[9]*/
    {
        NULL,
        "",
        &lv_font_montserrat_14,
    },
    /*[10]*/
    {
        NULL,
        "",
        &lv_font_montserrat_14,
    },
    /*[11]*/
    {
        NULL,
        "",
        &lv_font_montserrat_14,
    },
    /*[12]*/
    {
        NULL,
        "",
        &lv_font_montserrat_14,
    },
    /*[13]*/
    {
        NULL,
        "",
        &lv_font_montserrat_14,
    },
    /*[14]*/
    {
        NULL,
        "",
        &lv_font_montserrat_14,
    },
    /*[15]*/
    {
        NULL,
        "",
        &lv_font_montserrat_14,
    },
    /*[16]*/
    {
        NULL,
        "",
        &lv_font_montserrat_14,
    },
    /*[17]*/
    {
        NULL,
        "",
        &lv_font_montserrat_14,
    },
    /*[18]*/
    {
        NULL,
        "",
        &lv_font_montserrat_14,
    },
    /*[19]*/
    {
        NULL,
        "",
        &lv_font_montserrat_14,
    },
};


#define SPECIAL_BUTTON_SIZE_X 70
#define SPECIAL_BUTTON_SIZE_Y 25
#define SPECIAL_BUTTON_SPACE_X 5
#define SPECIAL_BUTTON_SPACE_Y 5
#define SPECIAL_X_OFFSET_FROM_LEFT 10
#define SPECIAL_Y_OFFSET_FROM_TOP 10

typedef void (*SPECIAL_tpfnvGuiStateFunc)(lv_obj_t *);
#endif

void SPECIAL_vScreenCreate(lv_obj_t *);
bool SPECIAL_boKeyPressedCallBackFunction(uint16_t );
bool SPECIAL_boKeyReleasedCallBackFunction(uint16_t );
void SPECIAL_vRotaryCallBackFunction(bool);
void SPECIAL_vRotaryButtonPressedCallBackFunction(void);
void SPECIAL_vHouseKeeping(void);
