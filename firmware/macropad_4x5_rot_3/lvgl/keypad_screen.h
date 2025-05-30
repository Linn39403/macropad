#pragma once
#include "keymap.h"
#include QMK_KEYBOARD_H
#include "GUI_helper.h"

#ifndef __KEPAD_SCREEN_C
    #define KEYPAD_SCREEN_EXTERN
#else
    #define KEYPAD_SCREEN_EXTERN extern
#endif

KEYPAD_SCREEN_EXTERN lv_obj_t* KPAD_spVolumeObj;
KEYPAD_SCREEN_EXTERN lv_obj_t* KPAD_spVolumeLbl;
KEYPAD_SCREEN_EXTERN lv_obj_t* KPAD_spVolumeTxt;

enum numpad_Keys{
    NUM_KEY_7_AND_A = 0, NUM_KEY_8_AND_B, NUM_KEY_9_AND_C,
    NUM_KEY_4_AND_D, NUM_KEY_5_AND_E, NUM_KEY_6_AND_F,
};

#ifdef __KEYPAD_SCREEN_C

/* This macro is private macro for keypad_screen.c only.
 * true -> QMK will handle the key event.
 * false -> QMK will not handle the key event.
*/
#define KPAD_LET_QMK_HANDLE_KEYBOARD_EVENT  true

tap_dance_action_t tap_dance_actions[6] =
{
    [NUM_KEY_7_AND_A] = ACTION_TAP_DANCE_DOUBLE(KC_KP_7, KC_A),
    [NUM_KEY_8_AND_B] = ACTION_TAP_DANCE_DOUBLE(KC_KP_8, KC_B),
    [NUM_KEY_9_AND_C] = ACTION_TAP_DANCE_DOUBLE(KC_KP_9, KC_C),
    [NUM_KEY_4_AND_D] = ACTION_TAP_DANCE_DOUBLE(KC_KP_4, KC_D),
    [NUM_KEY_5_AND_E] = ACTION_TAP_DANCE_DOUBLE(KC_KP_5, KC_E),
    [NUM_KEY_6_AND_F] = ACTION_TAP_DANCE_DOUBLE(KC_KP_6, KC_F),
};
#else
    extern tap_dance_action_t tap_dance_actions[6];
#endif


#define KPAD_KEY_0   KC_BACKSPACE
#define KPAD_KEY_1   KC_KP_SLASH
#define KPAD_KEY_2   KC_KP_ASTERISK
#define KPAD_KEY_3   KC_KP_MINUS
#define KPAD_KEY_4   TD(NUM_KEY_7_AND_A)
#define KPAD_KEY_5   TD(NUM_KEY_8_AND_B)
#define KPAD_KEY_6   TD(NUM_KEY_9_AND_C)
#define KPAD_KEY_7   KC_KP_PLUS
#define KPAD_KEY_8   TD(NUM_KEY_4_AND_D)
#define KPAD_KEY_9   TD(NUM_KEY_5_AND_E)
#define KPAD_KEY_10  TD(NUM_KEY_6_AND_F)
#define KPAD_KEY_11  KC_KP_PLUS
#define KPAD_KEY_12  KC_KP_1
#define KPAD_KEY_13  KC_KP_2
#define KPAD_KEY_14  KC_KP_3
#define KPAD_KEY_15  KC_KP_ENTER
#define KPAD_KEY_16  KC_KP_0
#define KPAD_KEY_17  KC_KP_0
#define KPAD_KEY_18  KC_KP_DOT
#define KPAD_KEY_19  KC_KP_ENTER

#ifdef __KEYPAD_SCREEN_C

struct KPAD_stBtnInfo
{
    lv_obj_t * m_spBtn;
    const uint16_t m_u16KeyCode;
    const char * m_cpBtnName;
    const bool  m_boBtnXDouble;
    const bool  m_boBtnYDouble;
	const bool  m_boSkipBtn;
};

struct KPAD_stBtnInfo KPAD_staBtnInfo [20] =
{
/*  m_spBtn    m_u16KeyCode         m_cpBtnName       BtnXDouble BtnYDouble SkipBtn */
    { NULL, KC_BACKSPACE        , LV_SYMBOL_BACKSPACE , false, false, false},
    { NULL, KC_KP_SLASH         , "/"                 , false, false, false},
    { NULL, KC_KP_ASTERISK      , "*"                 , false, false, false},
    { NULL, KC_KP_MINUS         , "-"                 , false, false, false},

    { NULL, TD(NUM_KEY_7_AND_A) , "7  A"              , false, false, false},
    { NULL, TD(NUM_KEY_8_AND_B) , "8  B"              , false, false, false},
    { NULL, TD(NUM_KEY_9_AND_C) , "9  C"              , false, false, false},
    { NULL, KC_KP_PLUS          , "+"                 , false, true , false},

    { NULL, TD(NUM_KEY_4_AND_D) , "4  D"              , false, false, false},
    { NULL, TD(NUM_KEY_5_AND_E) , "5  E"              , false, false, false},
    { NULL, TD(NUM_KEY_6_AND_F) , "6  F"              , false, false, false},
    { NULL, KC_KP_PLUS          , "+"                 , false, false, true }, /**/

    { NULL, KC_KP_1             , "1"                 , false, false, false},
    { NULL, KC_KP_2             , "2"                 , false, false, false},
    { NULL, KC_KP_3             , "3"                 , false, false, false},
    { NULL, KC_KP_ENTER         , LV_SYMBOL_NEW_LINE  , false, true , false},

    { NULL, KC_KP_0             , "0"                 , true , false, false},
	{ NULL, KC_KP_0             , "0"                 , false, false, true }, /**/
    { NULL, KC_KP_DOT           , "."                 , false, false, false},
	{ NULL, KC_KP_ENTER         , LV_SYMBOL_NEW_LINE  , false, false, true }, /**/
};

#define KPAD_BUTTON_SIZE_X 40
#define KPAD_BUTTON_SIZE_Y 25
#define KPAD_BUTTON_SPACE_X 5
#define KPAD_BUTTON_SPACE_Y 5
#define KPAD_X_OFFSET_FROM_LEFT 10
#define KPAD_Y_OFFSET_FROM_TOP 10
#define BUTTON_ALIGN_STYLE LV_ALIGN_DEFAULT

typedef void (*lv_obj_state_fptr)(lv_obj_t *);

#endif /* end #ifdef __KEYPAD_SCREEN_C */

void KPAD_vScreenCreate(lv_obj_t *parent_screen);
bool NUMPAD_boKeyPressedCallBackFunction(uint16_t );
bool NUMPAD_boKeyReleasedCallBackFunction(uint16_t );
