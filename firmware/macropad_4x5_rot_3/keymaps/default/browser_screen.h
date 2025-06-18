#pragma once
#include "GUI_helper.h"
#include QMK_KEYBOARD_H
#include "fonts/fa_font_list.h"

#define BROWSER_KEY_0     KC_F5           /* Refresh */
#define BROWSER_KEY_1     LCTL(KC_W)      /* Close Tab */
#define BROWSER_KEY_2     LCTL(KC_J)      /* Open Download */
#define BROWSER_KEY_3     LCTL(KC_H)      /* Open History */
#define BROWSER_KEY_4     KC_NO           /* Unused */
#define BROWSER_KEY_5     KC_NO           /* Unused */
#define BROWSER_KEY_6     KC_NO           /* Unused */
#define BROWSER_KEY_7     KC_NO           /* Unused */
#define BROWSER_KEY_8     LCTL(KC_PLUS)   /* Zoom ++ */
#define BROWSER_KEY_9     LCTL(KC_MINUS)  /* Zoom -- */
#define BROWSER_KEY_10    LCTL(KC_0)      /* Reset Zoom */
#define BROWSER_KEY_11    LCTL(KC_M)      /* Mute */
#define BROWSER_KEY_12    LCTL(KC_PAGE_UP)    /* Jump to left tab */
#define BROWSER_KEY_13    LCTL(KC_PAGE_DOWN)  /* Jump to right tab */
#define BROWSER_KEY_14    KC_NO           /* Unused */
#define BROWSER_KEY_15    KC_NO           /* Unused */
#define BROWSER_KEY_16    LCTL(KC_C)      /* Copy Plain Text */
#define BROWSER_KEY_17    LCTL(KC_X)      /* Cut */
#define BROWSER_KEY_18    LCTL(KC_V)      /* Paste */
#define BROWSER_KEY_19    LGUI(LCTL(LALT(KC_V)))      /* Paste Plain */

#ifdef __BROWSER_SCREEN_C

/* This macro is private macro for browser_screen.c only.
 * true -> QMK will handle the key event.
 * false -> QMK will not handle the key event.
*/
#define BROWSER_LET_QMK_HANDLE_KEYBOARD_EVENT  true

struct BROWSER_stBtnInfo
{
    lv_obj_t * m_spBtn;
	const uint16_t m_u16KeyCode;
    const lv_font_t * m_spFontName;
    const char * m_cpBtnName;
};

struct BROWSER_stBtnInfo BROWSER_staBtnInfo [20] =
{
    { NULL, BROWSER_KEY_0  , &lv_font_montserrat_14, "Refresh"},
    { NULL, BROWSER_KEY_1  , &lv_font_montserrat_14, "ClTab"},
    { NULL, BROWSER_KEY_2  , &lv_font_montserrat_14, "Download"},
    { NULL, BROWSER_KEY_3  , &lv_font_montserrat_14, "History"},
    { NULL, BROWSER_KEY_4  , &lv_font_montserrat_14, "    "},
    { NULL, BROWSER_KEY_5  , &lv_font_montserrat_14, "    "},
    { NULL, BROWSER_KEY_6  , &lv_font_montserrat_14, "    "},
    { NULL, BROWSER_KEY_7  , &lv_font_montserrat_14, "    "},
    { NULL, BROWSER_KEY_8  , &lv_font_montserrat_14, "Zoom+"},
    { NULL, BROWSER_KEY_9  , &lv_font_montserrat_14, "Zoom-"},
    { NULL, BROWSER_KEY_10 , &lv_font_montserrat_14, "Zoom0"},
    { NULL, BROWSER_KEY_11 , &lv_font_montserrat_14, "Mute"},
    { NULL, BROWSER_KEY_12 , &lv_font_montserrat_14, LV_SYMBOL_LEFT},
    { NULL, BROWSER_KEY_13 , &lv_font_montserrat_14, LV_SYMBOL_RIGHT},
    { NULL, BROWSER_KEY_14 , &lv_font_montserrat_14, "    "},
    { NULL, BROWSER_KEY_15 , &lv_font_montserrat_14, "    "},
    { NULL, BROWSER_KEY_16 , &lv_font_montserrat_14, "CtlC"},
    { NULL, BROWSER_KEY_17 , &lv_font_montserrat_14, "CtlX"},
    { NULL, BROWSER_KEY_18 , &lv_font_montserrat_14, "CtlV"},
    { NULL, BROWSER_KEY_19 , &lv_font_montserrat_14, "CtlV+Plain"},
};



#define BROWSER_BUTTON_SIZE_X 70
#define BROWSER_BUTTON_SIZE_Y 25
#define BROWSER_BUTTON_SPACE_X 5
#define BROWSER_BUTTON_SPACE_Y 5
#define BROWSER_X_OFFSET_FROM_LEFT 10
#define BROWSER_Y_OFFSET_FROM_TOP 10

typedef void (*BROWSER_tpfnvGuiStateFunc)(lv_obj_t *);

#endif /* end #ifdef __TOTAL_COMMANDER_SCREEN_C */

void BROWSER_vScreenCreate(lv_obj_t *);
bool BROWSER_boKeyPressedCallBackFunction(uint16_t );
bool BROWSER_boKeyReleasedCallBackFunction(uint16_t );
void BROWSER_vRotaryCallBackFunction(bool boClockwise, bool boModeButtonPressed);
void BROWSER_vRotaryButtonPressedCallBackFunction(void);
void BROWSER_vHouseKeeping(void);
