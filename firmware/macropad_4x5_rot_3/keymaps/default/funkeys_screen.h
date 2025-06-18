#pragma once
#include "GUI_helper.h"
#include QMK_KEYBOARD_H
#include "fonts/fa_font_list.h"

#define FUNKEYS_KEY_0     KC_F13   /* */
#define FUNKEYS_KEY_1     KC_F14   /* */
#define FUNKEYS_KEY_2     KC_F15   /* */
#define FUNKEYS_KEY_3     KC_F16   /* */
#define FUNKEYS_KEY_4     KC_F17   /* */
#define FUNKEYS_KEY_5     KC_F18   /* */
#define FUNKEYS_KEY_6     KC_F19   /* */
#define FUNKEYS_KEY_7     KC_F20   /* */
#define FUNKEYS_KEY_8     KC_F21   /* */
#define FUNKEYS_KEY_9     KC_F22   /* */
#define FUNKEYS_KEY_10    KC_F23   /* */
#define FUNKEYS_KEY_11    KC_F24   /* */
#define FUNKEYS_KEY_12    KC_NO    /* */
#define FUNKEYS_KEY_13    KC_NO    /* */
#define FUNKEYS_KEY_14    KC_NO    /* */
#define FUNKEYS_KEY_15    KC_NO    /* */
#define FUNKEYS_KEY_16    KC_NO    /* */
#define FUNKEYS_KEY_17    KC_NO    /* */
#define FUNKEYS_KEY_18    KC_NO    /* */
#define FUNKEYS_KEY_19    KC_NO    /* */

#ifdef __FUNKEYS_SCREEN_C

struct FUNKEYS_stBtnInfo
{
    lv_obj_t * m_spBtn;
	const uint16_t m_u16KeyCode;
    const lv_font_t * m_spFontName;
    const char * m_cpBtnName;
};

struct FUNKEYS_stBtnInfo FUNKEYS_staBtnInfo [20] =
{
    { NULL, FUNKEYS_KEY_0  , &lv_font_montserrat_14, "FN13"},
    { NULL, FUNKEYS_KEY_1  , &lv_font_montserrat_14, "FN14"},
    { NULL, FUNKEYS_KEY_2  , &lv_font_montserrat_14, "FN15"},
    { NULL, FUNKEYS_KEY_3  , &lv_font_montserrat_14, "FN16"},
    { NULL, FUNKEYS_KEY_4  , &lv_font_montserrat_14, "FN17"},
    { NULL, FUNKEYS_KEY_5  , &lv_font_montserrat_14, "FN18"},
    { NULL, FUNKEYS_KEY_6  , &lv_font_montserrat_14, "FN19"},
    { NULL, FUNKEYS_KEY_7  , &lv_font_montserrat_14, "FN20"},
    { NULL, FUNKEYS_KEY_8  , &lv_font_montserrat_14, "FN21"},
    { NULL, FUNKEYS_KEY_9  , &lv_font_montserrat_14, "FN22"},
    { NULL, FUNKEYS_KEY_10 , &lv_font_montserrat_14, "FN23"},
    { NULL, FUNKEYS_KEY_11 , &lv_font_montserrat_14, "FN24"},
    { NULL, FUNKEYS_KEY_12 , &lv_font_montserrat_14, "    "},
    { NULL, FUNKEYS_KEY_13 , &lv_font_montserrat_14, "    "},
    { NULL, FUNKEYS_KEY_14 , &lv_font_montserrat_14, "    "},
    { NULL, FUNKEYS_KEY_15 , &lv_font_montserrat_14, "    "},
    { NULL, FUNKEYS_KEY_16 , &lv_font_montserrat_14, "    "},
    { NULL, FUNKEYS_KEY_17 , &lv_font_montserrat_14, "    "},
    { NULL, FUNKEYS_KEY_18 , &lv_font_montserrat_14, "    "},
    { NULL, FUNKEYS_KEY_19 , &lv_font_montserrat_14, "    "},
};



#define FUNKEYS_BUTTON_SIZE_X 70
#define FUNKEYS_BUTTON_SIZE_Y 25
#define FUNKEYS_BUTTON_SPACE_X 5
#define FUNKEYS_BUTTON_SPACE_Y 5
#define FUNKEYS_X_OFFSET_FROM_LEFT 10
#define FUNKEYS_Y_OFFSET_FROM_TOP 10

typedef void (*FUNKEYS_tpfnvGuiStateFunc)(lv_obj_t *);

#endif /* end #ifdef __FUNKEYS_SCREEN_C */

void FUNKEYS_vScreenCreate(lv_obj_t *);
bool FUNKEYS_boKeyPressedCallBackFunction(uint16_t );
bool FUNKEYS_boKeyReleasedCallBackFunction(uint16_t );
void FUNKEYS_vRotaryCallBackFunction(bool , bool );
void FUNKEYS_vRotaryButtonPressedCallBackFunction(void);
void FUNKEYS_vHouseKeeping(void);
