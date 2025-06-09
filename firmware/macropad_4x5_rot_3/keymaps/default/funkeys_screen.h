#pragma once
#include "GUI_helper.h"
#include QMK_KEYBOARD_H


#define FUNKEYS_KEY_0     S(KC_F6)        /* Rename Shortcut */
#define FUNKEYS_KEY_1     S(KC_F10)       /* Properties Shortcut */
#define FUNKEYS_KEY_2     S(KC_F4)        /* New Text File Shortcut */
#define FUNKEYS_KEY_3     LCTL(KC_BSLS)   /* Jump to Root Shortcut */
#define FUNKEYS_KEY_4     LCTL(KC_UP)     /* New Tab Shortcut */
#define FUNKEYS_KEY_5     LCTL(KC_W)      /* Close Tab Shortcut */
#define FUNKEYS_KEY_6     LCTL(KC_TAB)    /* Tab Change Shortcut */
#define FUNKEYS_KEY_7     KC_TAB          /* Switch Tab Shortcut */
#define FUNKEYS_KEY_8     LCTL(KC_F3)     /* Sort by Name Shortcut */
#define FUNKEYS_KEY_9     LCTL(KC_F4)     /* Sort by Ext Shortcut */
#define FUNKEYS_KEY_10    LCTL(KC_F5)     /* Sort by Time Shortcut */
#define FUNKEYS_KEY_11    LCTL(KC_F6)     /* Sort by Size Shortcut */
#define FUNKEYS_KEY_12    KC_ESC          /* Cancel Shortcut */
#define FUNKEYS_KEY_13    KC_NO           /* Unused */
#define FUNKEYS_KEY_14    KC_NO           /* Unused */
#define FUNKEYS_KEY_15    KC_BACKSPACE    /* Back Shortcut */
#define FUNKEYS_KEY_16    KC_NO           /* Unused */
#define FUNKEYS_KEY_17    KC_NO           /* Unused */
#define FUNKEYS_KEY_18    KC_NO           /* Unused */
#define FUNKEYS_KEY_19    KC_NO           /* Unused */

#ifdef __FUNKEYS_SCREEN_C

struct FUNKEYS_stBtnInfo
{
    lv_obj_t * m_spBtn;
	const uint16_t m_u16KeyCode;
    const char * m_cpBtnName;
};

struct FUNKEYS_stBtnInfo FUNKEYS_staBtnInfo [20] =
{
    { NULL, FUNKEYS_KEY_0  , "Rename"},
    { NULL, FUNKEYS_KEY_1  , "Prop"},
    { NULL, FUNKEYS_KEY_2  , "NewTxt"},
    { NULL, FUNKEYS_KEY_3  , "Root"},
    { NULL, FUNKEYS_KEY_4  , "NewTab"},
    { NULL, FUNKEYS_KEY_5  , "ClseTab"},
    { NULL, FUNKEYS_KEY_6  , "ChngTab"},
    { NULL, FUNKEYS_KEY_7  , "Switch"},
    { NULL, FUNKEYS_KEY_8  , "SName"},
    { NULL, FUNKEYS_KEY_9  , "SExtion"},
    { NULL, FUNKEYS_KEY_10 , "STime"},
    { NULL, FUNKEYS_KEY_11 , "SSize"},
    { NULL, FUNKEYS_KEY_12 , "Esc"},
    { NULL, FUNKEYS_KEY_13 , "    "},
    { NULL, FUNKEYS_KEY_14 , "    "},
    { NULL, FUNKEYS_KEY_15 , LV_SYMBOL_BACKSPACE},
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
