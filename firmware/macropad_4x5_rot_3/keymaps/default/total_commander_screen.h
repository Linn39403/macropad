#pragma once
#include "GUI_helper.h"
#include QMK_KEYBOARD_H


#define TOTAL_COMMANDER_KEY_0     S(KC_F6)        /* Rename Shortcut */
#define TOTAL_COMMANDER_KEY_1     S(KC_F10)       /* Properties Shortcut */
#define TOTAL_COMMANDER_KEY_2     S(KC_F4)        /* New Text File Shortcut */
#define TOTAL_COMMANDER_KEY_3     LCTL(KC_BSLS)   /* Jump to Root Shortcut */
#define TOTAL_COMMANDER_KEY_4     LCTL(KC_UP)     /* New Tab Shortcut */
#define TOTAL_COMMANDER_KEY_5     LCTL(KC_W)      /* Close Tab Shortcut */
#define TOTAL_COMMANDER_KEY_6     LCTL(KC_TAB)    /* Tab Change Shortcut */
#define TOTAL_COMMANDER_KEY_7     KC_TAB          /* Switch Tab Shortcut */
#define TOTAL_COMMANDER_KEY_8     LCTL(KC_F3)     /* Sort by Name Shortcut */
#define TOTAL_COMMANDER_KEY_9     LCTL(KC_F4)     /* Sort by Ext Shortcut */
#define TOTAL_COMMANDER_KEY_10    LCTL(KC_F5)     /* Sort by Time Shortcut */
#define TOTAL_COMMANDER_KEY_11    LCTL(KC_F6)     /* Sort by Size Shortcut */
#define TOTAL_COMMANDER_KEY_12    KC_ESC          /* Cancel Shortcut */
#define TOTAL_COMMANDER_KEY_13    KC_NO           /* Unused */
#define TOTAL_COMMANDER_KEY_14    KC_NO           /* Unused */
#define TOTAL_COMMANDER_KEY_15    KC_BACKSPACE    /* Back Shortcut */
#define TOTAL_COMMANDER_KEY_16    KC_NO           /* Unused */
#define TOTAL_COMMANDER_KEY_17    KC_NO           /* Unused */
#define TOTAL_COMMANDER_KEY_18    KC_NO           /* Unused */
#define TOTAL_COMMANDER_KEY_19    KC_NO           /* Unused */

#ifdef __TOTAL_COMMANDER_SCREEN_C

struct TOTAL_COMMANDER_stBtnInfo
{
    lv_obj_t * m_spBtn;
	const uint16_t m_u16KeyCode;
    const char * m_cpBtnName;
};

struct TOTAL_COMMANDER_stBtnInfo TOTAL_COMMANDER_staBtnInfo [20] =
{
    { NULL, TOTAL_COMMANDER_KEY_0  , "Rename"},
    { NULL, TOTAL_COMMANDER_KEY_1  , "Prop"},
    { NULL, TOTAL_COMMANDER_KEY_2  , "NewTxt"},
    { NULL, TOTAL_COMMANDER_KEY_3  , "Root"},
    { NULL, TOTAL_COMMANDER_KEY_4  , "NewTab"},
    { NULL, TOTAL_COMMANDER_KEY_5  , "ClseTab"},
    { NULL, TOTAL_COMMANDER_KEY_6  , "ChngTab"},
    { NULL, TOTAL_COMMANDER_KEY_7  , "Switch"},
    { NULL, TOTAL_COMMANDER_KEY_8  , "SName"},
    { NULL, TOTAL_COMMANDER_KEY_9  , "SExtion"},
    { NULL, TOTAL_COMMANDER_KEY_10 , "STime"},
    { NULL, TOTAL_COMMANDER_KEY_11 , "SSize"},
    { NULL, TOTAL_COMMANDER_KEY_12 , "Esc"},
    { NULL, TOTAL_COMMANDER_KEY_13 , "    "},
    { NULL, TOTAL_COMMANDER_KEY_14 , "    "},
    { NULL, TOTAL_COMMANDER_KEY_15 , LV_SYMBOL_BACKSPACE},
    { NULL, TOTAL_COMMANDER_KEY_16 , "    "},
    { NULL, TOTAL_COMMANDER_KEY_17 , "    "},
    { NULL, TOTAL_COMMANDER_KEY_18 , "    "},
    { NULL, TOTAL_COMMANDER_KEY_19 , "    "},
};



#define TOTAL_COMMANDER_BUTTON_SIZE_X 70
#define TOTAL_COMMANDER_BUTTON_SIZE_Y 25
#define TOTAL_COMMANDER_BUTTON_SPACE_X 5
#define TOTAL_COMMANDER_BUTTON_SPACE_Y 5
#define TOTAL_COMMANDER_X_OFFSET_FROM_LEFT 10
#define TOTAL_COMMANDER_Y_OFFSET_FROM_TOP 10

typedef void (*TOTAL_COMMANDER_tpfnvGuiStateFunc)(lv_obj_t *);

#endif /* end #ifdef __TOTAL_COMMANDER_SCREEN_C */

void TOTAL_COMMANDER_vScreenCreate(lv_obj_t *);
bool TOTAL_COMMANDER_boKeyPressedCallBackFunction(uint16_t );
bool TOTAL_COMMANDER_boKeyReleasedCallBackFunction(uint16_t );
void TOTAL_COMMANDER_vRotaryCallBackFunction(bool boClockwise, bool boRotaryButtonPressed, bool boModeButtonPressed);
