#pragma once
#include "GUI_helper.h"
#include QMK_KEYBOARD_H

#define BROWSER_KEY_0     KC_NO           /* Rename Shortcut */
#define BROWSER_KEY_1     KC_NO           /* Properties Shortcut */
#define BROWSER_KEY_2     KC_NO           /* New Text File Shortcut */
#define BROWSER_KEY_3     KC_NO           /* Jump to Root Shortcut */
#define BROWSER_KEY_4     KC_NO           /* New Tab Shortcut */
#define BROWSER_KEY_5     KC_NO           /* Close Tab Shortcut */
#define BROWSER_KEY_6     KC_NO           /* Tab Change Shortcut */
#define BROWSER_KEY_7     KC_NO           /* Switch Tab Shortcut */
#define BROWSER_KEY_8     KC_NO           /* Sort by Name Shortcut */
#define BROWSER_KEY_9     KC_NO           /* Sort by Ext Shortcut */
#define BROWSER_KEY_10    KC_NO           /* Sort by Time Shortcut */
#define BROWSER_KEY_11    KC_NO           /* Sort by Size Shortcut */
#define BROWSER_KEY_12    LCTL(KC_PAGE_UP)    /* Jump to left tab */
#define BROWSER_KEY_13    LCTL(KC_PAGE_DOWN)  /* Jump to right tab */
#define BROWSER_KEY_14    KC_NO           /* Unused */
#define BROWSER_KEY_15    KC_NO           /* Back Shortcut */
#define BROWSER_KEY_16    KC_NO           /* Unused */
#define BROWSER_KEY_17    KC_NO           /* Unused */
#define BROWSER_KEY_18    KC_NO           /* Unused */
#define BROWSER_KEY_19    KC_NO           /* Unused */

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
    const char * m_cpBtnName;
};

struct BROWSER_stBtnInfo BROWSER_staBtnInfo [20] =
{
    { NULL, BROWSER_KEY_0  , "    "},
    { NULL, BROWSER_KEY_1  , "    "},
    { NULL, BROWSER_KEY_2  , "    "},
    { NULL, BROWSER_KEY_3  , "    "},
    { NULL, BROWSER_KEY_4  , "    "},
    { NULL, BROWSER_KEY_5  , "    "},
    { NULL, BROWSER_KEY_6  , "    "},
    { NULL, BROWSER_KEY_7  , "    "},
    { NULL, BROWSER_KEY_8  , "    "},
    { NULL, BROWSER_KEY_9  , "    "},
    { NULL, BROWSER_KEY_10 , "    "},
    { NULL, BROWSER_KEY_11 , "    "},
    { NULL, BROWSER_KEY_12 , LV_SYMBOL_LEFT},
    { NULL, BROWSER_KEY_13 , LV_SYMBOL_RIGHT},
    { NULL, BROWSER_KEY_14 , "    "},
    { NULL, BROWSER_KEY_15 , "    "},
    { NULL, BROWSER_KEY_16 , "    "},
    { NULL, BROWSER_KEY_17 , "    "},
    { NULL, BROWSER_KEY_18 , "    "},
    { NULL, BROWSER_KEY_19 , "    "},
};



#define BROWSER_BUTTON_SIZE_X 70
#define BROWSER_BUTTON_SIZE_Y 30
#define BROWSER_BUTTON_SPACE_X 5
#define BROWSER_BUTTON_SPACE_Y 5
#define BROWSER_X_OFFSET_FROM_LEFT 10
#define BROWSER_Y_OFFSET_FROM_TOP 10

typedef void (*BROWSER_tpfnvGuiStateFunc)(lv_obj_t *);

#endif /* end #ifdef __TOTAL_COMMANDER_SCREEN_C */

void BROWSER_vScreenCreate(lv_obj_t *);
bool BROWSER_boKeyPressedCallBackFunction(uint16_t );
bool BROWSER_boKeyReleasedCallBackFunction(uint16_t );
void BROWSER_vRotaryCallBackFunction(bool boClockwise);
