#pragma once
#include "GUI_helper.h"
#include QMK_KEYBOARD_H

enum TTCMD_BUTTONS_ENUM
{
    TTCMD_BUTTON_RENAME = 0,
    TTCMD_BUTTON_PROPERTIES,
    TTCMD_BUTTON_NEW_TXT_FILE,
    TTCMD_BUTTON_JUMP_TO_ROOT,
    TTCMD_BUTTON_NEW_TAB,
    TTCMD_BUTTON_CLOSE_TAB,
    TTCMD_BUTTON_TAB_CHANGE,
    TTCMD_BUTTON_SWITCH_TAB,
    TTCMD_BUTTON_SORT_BY_NAME,
    TTCMD_BUTTON_SORT_BY_EXT,
    TTCMD_BUTTON_SORT_BY_TIME,
    TTCMD_BUTTON_SORT_BY_SIZE,
    TTCMD_BUTTON_CANCEL,
    TTCMD_BUTTON_UNUSED_2,
    TTCMD_BUTTON_UNUSED_3,
    TTCMD_BUTTON_BACK,
    TTCMD_BUTTON_UNUSED_4,
    TTCMD_BUTTON_UNUSED_5,
    TTCMD_BUTTON_UNUSED_6,
    TTCMD_BUTTON_UNUSED_7,
    TTCMD_BUTTON_COUNT
};

#define TTCMD_KEY_0     S(KC_F6)        /* Rename Shortcut */
#define TTCMD_KEY_1     S(KC_F10)       /* Properties Shortcut */
#define TTCMD_KEY_2     S(KC_F4)        /* New Text File Shortcut */
#define TTCMD_KEY_3     LCTL(KC_BSLS)   /* Jump to Root Shortcut */
#define TTCMD_KEY_4     LCTL(KC_UP)     /* New Tab Shortcut */
#define TTCMD_KEY_5     LCTL(KC_W)      /* Close Tab Shortcut */
#define TTCMD_KEY_6     LCTL(KC_TAB)    /* Tab Change Shortcut */
#define TTCMD_KEY_7     KC_TAB          /* Switch Tab Shortcut */
#define TTCMD_KEY_8     LCTL(KC_F3)     /* Sort by Name Shortcut */
#define TTCMD_KEY_9     LCTL(KC_F4)     /* Sort by Ext Shortcut */
#define TTCMD_KEY_10    LCTL(KC_F5)     /* Sort by Time Shortcut */
#define TTCMD_KEY_11    LCTL(KC_F6)     /* Sort by Size Shortcut */
#define TTCMD_KEY_12    KC_ESC          /* Cancel Shortcut */
#define TTCMD_KEY_13    KC_NO           /* Unused */
#define TTCMD_KEY_14    KC_NO           /* Unused */
#define TTCMD_KEY_15    KC_BACKSPACE    /* Back Shortcut */
#define TTCMD_KEY_16    KC_NO           /* Unused */
#define TTCMD_KEY_17    KC_NO           /* Unused */
#define TTCMD_KEY_18    KC_NO           /* Unused */
#define TTCMD_KEY_19    KC_NO           /* Unused */

#ifdef __TOTAL_COMMANDER_SCREEN_C

struct TTCMD_stBtnInfo
{
    lv_obj_t * m_spBtn;
    const char * m_cpBtnName;
};

static struct TTCMD_stBtnInfo TTCMD_staBtnInfo [TTCMD_BUTTON_COUNT] =
{
    {NULL, "Rename"},
    {NULL, "Prop"},
    {NULL, "NewTxt"},
    {NULL, "Root"},
    {NULL, "NewTab"},
    {NULL, "ClTab"},
    {NULL, "CHngTb"},
    {NULL, "Swch"},
    {NULL, "SName"},
    {NULL, "SExt"},
    {NULL, "STim"},
    {NULL, "SSiz"},
    {NULL, "Esc"},
    {NULL, "    "},
    {NULL, "    "},
    {NULL, LV_SYMBOL_BACKSPACE},
    {NULL, "    "},
    {NULL, "    "},
    {NULL, "    "},
    {NULL, "    "},
};


#define TTCMD_BUTTON_SIZE_X 60
#define TTCMD_BUTTON_SIZE_Y 25
#define TTCMD_BUTTON_SPACE_X 5
#define TTCMD_BUTTON_SPACE_Y 5
#define TTCMD_X_OFFSET_FROM_LEFT 10
#define TTCMD_Y_OFFSET_FROM_TOP 10

typedef void (*TTCMD_tpfnvGuiStateFunc)(lv_obj_t *);

#endif /* end #ifdef __TOTAL_COMMANDER_SCREEN_C */

void TTCMD_vScreenCreate(lv_obj_t *);
