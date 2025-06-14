#pragma once
#include "keymap.h"
#include QMK_KEYBOARD_H
#include "GUI_helper.h"

#ifndef __KEPAD_SCREEN_C
    #define NUMPAD_SCREEN_EXTERN
#else
    #define NUMPAD_SCREEN_EXTERN extern
#endif

NUMPAD_SCREEN_EXTERN lv_obj_t* NUMPAD_spVolumeObj;
NUMPAD_SCREEN_EXTERN lv_obj_t* NUMPAD_spVolumeLbl;
NUMPAD_SCREEN_EXTERN lv_obj_t* NUMPAD_spVolumeTxt;

enum numpad_Keys{
    NUMPAD_KEY_7_AND_A = 0, NUMPAD_KEY_8_AND_B, NUMPAD_KEY_9_AND_C,
    NUMPAD_KEY_4_AND_D, NUMPAD_KEY_5_AND_E, NUMPAD_KEY_6_AND_F,
};

#ifdef __NUMPAD_SCREEN_C

/* This macro is private macro for NUMPAD_screen.c only.
 * true -> QMK will handle the key event.
 * false -> QMK will not handle the key event.
*/
#define NUMPAD_LET_QMK_HANDLE_KEYBOARD_EVENT  true

tap_dance_action_t tap_dance_actions[6] =
{
    [NUMPAD_KEY_7_AND_A] = ACTION_TAP_DANCE_DOUBLE(KC_KP_7, KC_A),
    [NUMPAD_KEY_8_AND_B] = ACTION_TAP_DANCE_DOUBLE(KC_KP_8, KC_B),
    [NUMPAD_KEY_9_AND_C] = ACTION_TAP_DANCE_DOUBLE(KC_KP_9, KC_C),
    [NUMPAD_KEY_4_AND_D] = ACTION_TAP_DANCE_DOUBLE(KC_KP_4, KC_D),
    [NUMPAD_KEY_5_AND_E] = ACTION_TAP_DANCE_DOUBLE(KC_KP_5, KC_E),
    [NUMPAD_KEY_6_AND_F] = ACTION_TAP_DANCE_DOUBLE(KC_KP_6, KC_F),
};
#else
    extern tap_dance_action_t tap_dance_actions[6];
#endif


#define NUMPAD_KEY_0   KC_BACKSPACE
#define NUMPAD_KEY_1   KC_KP_SLASH
#define NUMPAD_KEY_2   KC_KP_ASTERISK
#define NUMPAD_KEY_3   KC_KP_MINUS
#define NUMPAD_KEY_4   TD(NUMPAD_KEY_7_AND_A)
#define NUMPAD_KEY_5   TD(NUMPAD_KEY_8_AND_B)
#define NUMPAD_KEY_6   TD(NUMPAD_KEY_9_AND_C)
#define NUMPAD_KEY_7   KC_KP_PLUS
#define NUMPAD_KEY_8   TD(NUMPAD_KEY_4_AND_D)
#define NUMPAD_KEY_9   TD(NUMPAD_KEY_5_AND_E)
#define NUMPAD_KEY_10  TD(NUMPAD_KEY_6_AND_F)
#define NUMPAD_KEY_11  KC_KP_PLUS
#define NUMPAD_KEY_12  KC_KP_1
#define NUMPAD_KEY_13  KC_KP_2
#define NUMPAD_KEY_14  KC_KP_3
#define NUMPAD_KEY_15  KC_KP_ENTER
#define NUMPAD_KEY_16  KC_KP_0
#define NUMPAD_KEY_17  KC_KP_0
#define NUMPAD_KEY_18  KC_KP_DOT
#define NUMPAD_KEY_19  KC_KP_ENTER

#ifdef __NUMPAD_SCREEN_C

struct NUMPAD_stBtnInfo
{
    lv_obj_t * m_spBtn;
    const uint16_t m_u16KeyCode;
    const char * m_cpBtnName;
    const bool  m_boBtnXDouble;
    const bool  m_boBtnYDouble;
	const bool  m_boSkipBtn;
};

struct NUMPAD_stBtnInfo NUMPAD_staBtnInfo [20] =
{
/*  m_spBtn    m_u16KeyCode         m_cpBtnName       BtnXDouble BtnYDouble SkipBtn */
    { NULL, KC_BACKSPACE        , LV_SYMBOL_BACKSPACE , false, false, false},
    { NULL, KC_KP_SLASH         , "/"                 , false, false, false},
    { NULL, KC_KP_ASTERISK      , "*"                 , false, false, false},
    { NULL, KC_KP_MINUS         , "-"                 , false, false, false},

    { NULL, TD(NUMPAD_KEY_7_AND_A) , "7  A"              , false, false, false},
    { NULL, TD(NUMPAD_KEY_8_AND_B) , "8  B"              , false, false, false},
    { NULL, TD(NUMPAD_KEY_9_AND_C) , "9  C"              , false, false, false},
    { NULL, KC_KP_PLUS          , "+"                 , false, true , false},

    { NULL, TD(NUMPAD_KEY_4_AND_D) , "4  D"              , false, false, false},
    { NULL, TD(NUMPAD_KEY_5_AND_E) , "5  E"              , false, false, false},
    { NULL, TD(NUMPAD_KEY_6_AND_F) , "6  F"              , false, false, false},
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

#define NUMPAD_BUTTON_SIZE_X 40
#define NUMPAD_BUTTON_SIZE_Y 25
#define NUMPAD_BUTTON_SPACE_X 5
#define NUMPAD_BUTTON_SPACE_Y 5
#define NUMPAD_X_OFFSET_FROM_LEFT 10
#define NUMPAD_Y_OFFSET_FROM_TOP 10
#define BUTTON_ALIGN_STYLE LV_ALIGN_DEFAULT

typedef void (*lv_obj_state_fptr)(lv_obj_t *);

#endif /* end #ifdef __NUMPAD_SCREEN_C */

void NUMPAD_vScreenCreate(lv_obj_t *parent_screen);
bool NUMPAD_boKeyPressedCallBackFunction(uint16_t );
bool NUMPAD_boKeyReleasedCallBackFunction(uint16_t );
void NUMPAD_vRotaryCallBackFunction(bool boClockwise, bool boRotaryButtonPressed, bool boModeButtonPressed);
