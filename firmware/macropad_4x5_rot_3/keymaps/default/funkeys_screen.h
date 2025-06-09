#pragma once
#include "GUI_helper.h"
#include QMK_KEYBOARD_H


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
    const char * m_cpBtnName;
};

struct FUNKEYS_stBtnInfo FUNKEYS_staBtnInfo [20] =
{
    { NULL, FUNKEYS_KEY_0  , "FN13"},
    { NULL, FUNKEYS_KEY_1  , "FN14"},
    { NULL, FUNKEYS_KEY_2  , "FN15"},
    { NULL, FUNKEYS_KEY_3  , "FN16"},
    { NULL, FUNKEYS_KEY_4  , "FN17"},
    { NULL, FUNKEYS_KEY_5  , "FN18"},
    { NULL, FUNKEYS_KEY_6  , "FN19"},
    { NULL, FUNKEYS_KEY_7  , "FN20"},
    { NULL, FUNKEYS_KEY_8  , "FN21"},
    { NULL, FUNKEYS_KEY_9  , "FN22"},
    { NULL, FUNKEYS_KEY_10 , "FN23"},
    { NULL, FUNKEYS_KEY_11 , "FN24"},
    { NULL, FUNKEYS_KEY_12 , "    "},
    { NULL, FUNKEYS_KEY_13 , "    "},
    { NULL, FUNKEYS_KEY_14 , "    "},
    { NULL, FUNKEYS_KEY_15 , "    "},
    { NULL, FUNKEYS_KEY_16 , "    "},
    { NULL, FUNKEYS_KEY_17 , "    "},
    { NULL, FUNKEYS_KEY_18 , "    "},
    { NULL, FUNKEYS_KEY_19 , "    "},
};



#define FUNKEYS_BUTTON_SIZE_X 70
#define FUNKEYS_BUTTON_SIZE_Y 30
#define FUNKEYS_BUTTON_SPACE_X 5
#define FUNKEYS_BUTTON_SPACE_Y 5
#define FUNKEYS_X_OFFSET_FROM_LEFT 10
#define FUNKEYS_Y_OFFSET_FROM_TOP 10

typedef void (*FUNKEYS_tpfnvGuiStateFunc)(lv_obj_t *);

#endif /* end #ifdef __FUNKEYS_SCREEN_C */

void FUNKEYS_vScreenCreate(lv_obj_t *);
bool FUNKEYS_boKeyPressedCallBackFunction(uint16_t );
bool FUNKEYS_boKeyReleasedCallBackFunction(uint16_t );
void FUNKEYS_vRotaryCallBackFunction(bool boClockwise);
