#pragma once
#include "GUI_helper.h"
#include QMK_KEYBOARD_H
#include "fonts/fa_font_list.h"


#define WIN_EXPLORER_KEY_0     KC_ESCAPE       /* Escape */
#define WIN_EXPLORER_KEY_1     LCTL(KC_N)      /* New Window */
#define WIN_EXPLORER_KEY_2     LCTL(KC_W)      /* Close */
#define WIN_EXPLORER_KEY_3     S(KC_F10)       /* Right Click Menu */
#define WIN_EXPLORER_KEY_4     LCTL(KC_L)      /* Copy Address Bar */
#define WIN_EXPLORER_KEY_5     LALT(KC_UP)     /* Jump to Parent Folder */
#define WIN_EXPLORER_KEY_6     LCTL(S(KC_N))   /* New Folder */
#define WIN_EXPLORER_KEY_7     KC_NO           /* */

#define WIN_EXPLORER_KEY_8     LCTL(KC_1)/* */
#define WIN_EXPLORER_KEY_9     LCTL(KC_2)/* */
#define WIN_EXPLORER_KEY_10    LCTL(KC_3)/* */
#define WIN_EXPLORER_KEY_11    LCTL(KC_4)/* */

#define WIN_EXPLORER_KEY_12    LCTL(KC_C)      /* Unused */
#define WIN_EXPLORER_KEY_13    LCTL(KC_X)      /* Unused */
#define WIN_EXPLORER_KEY_14    LGUI(LCTL(LALT(KC_V))) /* Unused */
#define WIN_EXPLORER_KEY_15    KC_DEL          /* Unused */

#define WIN_EXPLORER_KEY_16    LCTL(S(KC_2))      /* Large Icon View */
#define WIN_EXPLORER_KEY_17    LCTL(S(KC_6))      /* Detail View */
#define WIN_EXPLORER_KEY_18    KC_NO           /* Unused */
#define WIN_EXPLORER_KEY_19    KC_BACKSPACE    /* Back */

#ifdef __WIN_EXPLORER_SCREEN_C

struct WIN_EXPLORER_stBtnInfo
{
    lv_obj_t * m_spBtn;
	const uint16_t m_u16KeyCode;
    const lv_font_t * m_spFontName;
    const char * m_cpBtnName;
};

struct WIN_EXPLORER_stBtnInfo WIN_EXPLORER_staBtnInfo [20] =
{
    { NULL, WIN_EXPLORER_KEY_0  , &lv_font_montserrat_14, "Esc"},
    { NULL, WIN_EXPLORER_KEY_1  , &lv_font_montserrat_14, "NewWin"},
    { NULL, WIN_EXPLORER_KEY_2  , &lv_font_montserrat_14, "ClswWin"},
    { NULL, WIN_EXPLORER_KEY_3  , &lv_font_montserrat_14, "Menu"},
    { NULL, WIN_EXPLORER_KEY_4  , &lv_font_montserrat_14, "CpyAddr"},
    { NULL, WIN_EXPLORER_KEY_5  , &lv_font_montserrat_14, "Root"},
    { NULL, WIN_EXPLORER_KEY_6  , &fa_folder, FA_FOLDER},
    { NULL, WIN_EXPLORER_KEY_7  , &lv_font_montserrat_14, "    "},

    { NULL, WIN_EXPLORER_KEY_8  , &lv_font_montserrat_14, "1stExp"},
    { NULL, WIN_EXPLORER_KEY_9  , &lv_font_montserrat_14, "2ndExp"},
    { NULL, WIN_EXPLORER_KEY_10 , &lv_font_montserrat_14, "3rdExp"},
    { NULL, WIN_EXPLORER_KEY_11 , &lv_font_montserrat_14, "4thExp"},

    { NULL, WIN_EXPLORER_KEY_12 , &lv_font_montserrat_14, LV_SYMBOL_COPY},
    { NULL, WIN_EXPLORER_KEY_13 , &lv_font_montserrat_14, LV_SYMBOL_CUT},
    { NULL, WIN_EXPLORER_KEY_14 , &lv_font_montserrat_14, LV_SYMBOL_PASTE},
    { NULL, WIN_EXPLORER_KEY_15 , &lv_font_montserrat_14, LV_SYMBOL_TRASH},

    { NULL, WIN_EXPLORER_KEY_16 , &lv_font_montserrat_14, "LarView"},
    { NULL, WIN_EXPLORER_KEY_17 , &lv_font_montserrat_14, "DtlView"},
    { NULL, WIN_EXPLORER_KEY_18 , &lv_font_montserrat_14, "    "},
    { NULL, WIN_EXPLORER_KEY_19 , &lv_font_montserrat_14, LV_SYMBOL_BACKSPACE},
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
void WIN_EXPLORER_vRotaryCallBackFunction(bool , bool );
void WIN_EXPLORER_vRotaryButtonPressedCallBackFunction(void);
void WIN_EXPLORER_vHouseKeeping(void);
