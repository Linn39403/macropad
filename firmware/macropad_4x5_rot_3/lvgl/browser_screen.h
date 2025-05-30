#pragma once
#include "GUI_helper.h"
#include QMK_KEYBOARD_H

#define BWSER_KEY_0     KC_NO           /* Rename Shortcut */
#define BWSER_KEY_1     KC_NO           /* Properties Shortcut */
#define BWSER_KEY_2     KC_NO           /* New Text File Shortcut */
#define BWSER_KEY_3     KC_NO           /* Jump to Root Shortcut */
#define BWSER_KEY_4     KC_NO           /* New Tab Shortcut */
#define BWSER_KEY_5     KC_NO           /* Close Tab Shortcut */
#define BWSER_KEY_6     KC_NO           /* Tab Change Shortcut */
#define BWSER_KEY_7     KC_NO           /* Switch Tab Shortcut */
#define BWSER_KEY_8     KC_NO           /* Sort by Name Shortcut */
#define BWSER_KEY_9     KC_NO           /* Sort by Ext Shortcut */
#define BWSER_KEY_10    KC_NO           /* Sort by Time Shortcut */
#define BWSER_KEY_11    KC_NO           /* Sort by Size Shortcut */
#define BWSER_KEY_12    LCTL(KC_PAGE_UP)    /* Jump to left tab */
#define BWSER_KEY_13    LCTL(KC_PAGE_DOWN)  /* Jump to right tab */
#define BWSER_KEY_14    KC_NO           /* Unused */
#define BWSER_KEY_15    KC_NO           /* Back Shortcut */
#define BWSER_KEY_16    KC_NO           /* Unused */
#define BWSER_KEY_17    KC_NO           /* Unused */
#define BWSER_KEY_18    KC_NO           /* Unused */
#define BWSER_KEY_19    KC_NO           /* Unused */

#ifdef __BROWSER_SCREEN_C

/* This macro is private macro for browser_screen.c only.
 * true -> QMK will handle the key event.
 * false -> QMK will not handle the key event.
*/
#define BWSER_LET_QMK_HANDLE_KEYBOARD_EVENT  true

struct BWSER_stBtnInfo
{
    lv_obj_t * m_spBtn;
	const uint16_t m_u16KeyCode;
    const char * m_cpBtnName;
};

struct BWSER_stBtnInfo BWSER_staBtnInfo [20] =
{
    { NULL, BWSER_KEY_0  , "    "},
    { NULL, BWSER_KEY_1  , "    "},
    { NULL, BWSER_KEY_2  , "    "},
    { NULL, BWSER_KEY_3  , "    "},
    { NULL, BWSER_KEY_4  , "    "},
    { NULL, BWSER_KEY_5  , "    "},
    { NULL, BWSER_KEY_6  , "    "},
    { NULL, BWSER_KEY_7  , "    "},
    { NULL, BWSER_KEY_8  , "    "},
    { NULL, BWSER_KEY_9  , "    "},
    { NULL, BWSER_KEY_10 , "    "},
    { NULL, BWSER_KEY_11 , "    "},
    { NULL, BWSER_KEY_12 , LV_SYMBOL_LEFT},
    { NULL, BWSER_KEY_13 , LV_SYMBOL_RIGHT},
    { NULL, BWSER_KEY_14 , "    "},
    { NULL, BWSER_KEY_15 , "    "},
    { NULL, BWSER_KEY_16 , "    "},
    { NULL, BWSER_KEY_17 , "    "},
    { NULL, BWSER_KEY_18 , "    "},
    { NULL, BWSER_KEY_19 , "    "},
};



#define BWSER_BUTTON_SIZE_X 70
#define BWSER_BUTTON_SIZE_Y 30
#define BWSER_BUTTON_SPACE_X 5
#define BWSER_BUTTON_SPACE_Y 5
#define BWSER_X_OFFSET_FROM_LEFT 10
#define BWSER_Y_OFFSET_FROM_TOP 10

typedef void (*BWSER_tpfnvGuiStateFunc)(lv_obj_t *);

#endif /* end #ifdef __TOTAL_COMMANDER_SCREEN_C */

void BWSER_vScreenCreate(lv_obj_t *);
bool BROWSER_boKeyPressedCallBackFunction(uint16_t );
bool BROWSER_boKeyReleasedCallBackFunction(uint16_t );
