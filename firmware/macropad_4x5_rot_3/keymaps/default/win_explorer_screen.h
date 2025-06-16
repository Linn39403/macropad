#pragma once
#include "GUI_helper.h"
#include QMK_KEYBOARD_H


#define WIN_EXPLORER_KEY_0     S(KC_F6)        /* Rename Shortcut */
#define WIN_EXPLORER_KEY_1     S(KC_F10)       /* Properties Shortcut */
#define WIN_EXPLORER_KEY_2     S(KC_F4)        /* New Text File Shortcut */
#define WIN_EXPLORER_KEY_3     LCTL(KC_BSLS)   /* Jump to Root Shortcut */
#define WIN_EXPLORER_KEY_4     LCTL(KC_UP)     /* New Tab Shortcut */
#define WIN_EXPLORER_KEY_5     LCTL(KC_W)      /* Close Tab Shortcut */
#define WIN_EXPLORER_KEY_6     LCTL(KC_TAB)    /* Tab Change Shortcut */
#define WIN_EXPLORER_KEY_7     KC_TAB          /* Switch Tab Shortcut */
#define WIN_EXPLORER_KEY_8     LCTL(KC_F3)     /* Sort by Name Shortcut */
#define WIN_EXPLORER_KEY_9     LCTL(KC_F4)     /* Sort by Ext Shortcut */
#define WIN_EXPLORER_KEY_10    LCTL(KC_F5)     /* Sort by Time Shortcut */
#define WIN_EXPLORER_KEY_11    LCTL(KC_F6)     /* Sort by Size Shortcut */
#define WIN_EXPLORER_KEY_12    KC_ESC          /* Cancel Shortcut */
#define WIN_EXPLORER_KEY_13    KC_NO           /* Unused */
#define WIN_EXPLORER_KEY_14    KC_NO           /* Unused */
#define WIN_EXPLORER_KEY_15    KC_BACKSPACE    /* Back Shortcut */
#define WIN_EXPLORER_KEY_16    KC_NO           /* Unused */
#define WIN_EXPLORER_KEY_17    KC_NO           /* Unused */
#define WIN_EXPLORER_KEY_18    KC_NO           /* Unused */
#define WIN_EXPLORER_KEY_19    KC_NO           /* Unused */

#ifdef __WIN_EXPLORER_SCREEN_C

struct WIN_EXPLORER_stBtnInfo
{
    lv_obj_t * m_spBtn;
	const uint16_t m_u16KeyCode;
    const char * m_cpBtnName;
};

struct WIN_EXPLORER_stBtnInfo WIN_EXPLORER_staBtnInfo [20] =
{
    { NULL, WIN_EXPLORER_KEY_0  , "NewWin"},
    { NULL, WIN_EXPLORER_KEY_1  , "ClseWin"},
    { NULL, WIN_EXPLORER_KEY_2  , "*Folder"},
    { NULL, WIN_EXPLORER_KEY_3  , "Root"},
    { NULL, WIN_EXPLORER_KEY_4  , "NewTab"},
    { NULL, WIN_EXPLORER_KEY_5  , "ClseTab"},
    { NULL, WIN_EXPLORER_KEY_6  , "ChngTab"},
    { NULL, WIN_EXPLORER_KEY_7  , "Switch"},
    { NULL, WIN_EXPLORER_KEY_8  , "SName"},
    { NULL, WIN_EXPLORER_KEY_9  , "SExtion"},
    { NULL, WIN_EXPLORER_KEY_10 , "STime"},
    { NULL, WIN_EXPLORER_KEY_11 , "SSize"},
    { NULL, WIN_EXPLORER_KEY_12 , "Esc"},
    { NULL, WIN_EXPLORER_KEY_13 , "    "},
    { NULL, WIN_EXPLORER_KEY_14 , "    "},
    { NULL, WIN_EXPLORER_KEY_15 , LV_SYMBOL_BACKSPACE},
    { NULL, WIN_EXPLORER_KEY_16 , "    "},
    { NULL, WIN_EXPLORER_KEY_17 , "    "},
    { NULL, WIN_EXPLORER_KEY_18 , "    "},
    { NULL, WIN_EXPLORER_KEY_19 , "    "},
};



#define WIN_EXPLORER_BUTTON_SIZE_X 70
#define WIN_EXPLORER_BUTTON_SIZE_Y 25
#define WIN_EXPLORER_BUTTON_SPACE_X 5
#define WIN_EXPLORER_BUTTON_SPACE_Y 5
#define WIN_EXPLORER_X_OFFSET_FROM_LEFT 10
#define WIN_EXPLORER_Y_OFFSET_FROM_TOP 10

typedef void (*WIN_EXPLORER_tpfnvGuiStateFunc)(lv_obj_t *);

#endif /* end #ifdef __WIN_EXPLORER_SCREEN_C */

void WIN_EXPLORER_vScreenCreate(lv_obj_t *);
bool WIN_EXPLORER_boKeyPressedCallBackFunction(uint16_t );
bool WIN_EXPLORER_boKeyReleasedCallBackFunction(uint16_t );
void WIN_EXPLORER_vRotaryCallBackFunction(bool boClockwise, bool boRotaryButtonPressed, bool boModeButtonPressed);
void WIN_EXPLORER_vHouseKeeping(void);
