#pragma once
#include "GUI_helper.h"
#include QMK_KEYBOARD_H
#include "fonts/fa_font_list.h"


#define LOCK_KEY_0     KC_A          /* Unused */
#define LOCK_KEY_1     KC_B          /* Unused */
#define LOCK_KEY_2     KC_C          /* Unused */
#define LOCK_KEY_3     KC_D          /* Unused */
#define LOCK_KEY_4     KC_E          /* Unused */
#define LOCK_KEY_5     KC_F          /* Unused */
#define LOCK_KEY_6     KC_G          /* Unused */
#define LOCK_KEY_7     KC_H          /* Unused */
#define LOCK_KEY_8     KC_I          /* Unused */
#define LOCK_KEY_9     KC_J          /* Unused */
#define LOCK_KEY_10    KC_K          /* Unused */
#define LOCK_KEY_11    KC_L          /* Unused */
#define LOCK_KEY_12    KC_M          /* Unused */
#define LOCK_KEY_13    KC_O          /* Unused */
#define LOCK_KEY_14    KC_P          /* Unused */
#define LOCK_KEY_15    KC_Q          /* Unused */
#define LOCK_KEY_16    KC_R          /* Unused */
#define LOCK_KEY_17    KC_S          /* Unused */
#define LOCK_KEY_18    KC_T          /* Unused */
#define LOCK_KEY_19    KC_U          /* Unused */

#ifdef __LOCK_SCREEN_C

struct LOCK_stBtnInfo
{
    lv_obj_t * m_spBtn;
	const uint16_t m_u16KeyCode;
    const lv_font_t * m_spFontName;
    const char * m_cpBtnName;
};

struct LOCK_stBtnInfo LOCK_staBtnInfo [20] =
{
    { NULL, LOCK_KEY_0  , &lv_font_montserrat_14, "*"},
    { NULL, LOCK_KEY_1  , &lv_font_montserrat_14, "*"},
    { NULL, LOCK_KEY_2  , &lv_font_montserrat_14, "*"},
    { NULL, LOCK_KEY_3  , &lv_font_montserrat_14, "*"},
    { NULL, LOCK_KEY_4  , &lv_font_montserrat_14, "*"},
    { NULL, LOCK_KEY_5  , &lv_font_montserrat_14, "*"},
    { NULL, LOCK_KEY_6  , &lv_font_montserrat_14, "*"},
    { NULL, LOCK_KEY_7  , &lv_font_montserrat_14, "*"},
    { NULL, LOCK_KEY_8  , &lv_font_montserrat_14, "*"},
    { NULL, LOCK_KEY_9  , &lv_font_montserrat_14, "*"},
    { NULL, LOCK_KEY_10 , &lv_font_montserrat_14, "*"},
    { NULL, LOCK_KEY_11 , &lv_font_montserrat_14, "*"},
    { NULL, LOCK_KEY_12 , &lv_font_montserrat_14, "*"},
    { NULL, LOCK_KEY_13 , &lv_font_montserrat_14, "*"},
    { NULL, LOCK_KEY_14 , &lv_font_montserrat_14, "*"},
    { NULL, LOCK_KEY_15 , &lv_font_montserrat_14, "*"},
    { NULL, LOCK_KEY_16 , &lv_font_montserrat_14, "*"},
    { NULL, LOCK_KEY_17 , &lv_font_montserrat_14, "*"},
    { NULL, LOCK_KEY_18 , &lv_font_montserrat_14, "*"},
    { NULL, LOCK_KEY_19 , &lv_font_montserrat_14, "*"},
};



#define LOCK_BUTTON_SIZE_X 70
#define LOCK_BUTTON_SIZE_Y 25
#define LOCK_BUTTON_SPACE_X 5
#define LOCK_BUTTON_SPACE_Y 5
#define LOCK_X_OFFSET_FROM_LEFT 10
#define LOCK_Y_OFFSET_FROM_TOP 10

typedef void (*LOCK_tpfnvGuiStateFunc)(lv_obj_t *);

#endif /* end #ifdef __LOCK_SCREEN_C */

void LOCK_vScreenCreate(lv_obj_t *);
bool LOCK_boKeyPressedCallBackFunction(uint16_t );
bool LOCK_boKeyReleasedCallBackFunction(uint16_t );
void LOCK_vRotaryCallBackFunction(bool boClockwise, bool boModeButtonPressed);
void LOCK_vRotaryButtonPressedCallBackFunction(void);
void LOCK_vHouseKeeping(void);
