#pragma once
#include "GUI_helper.h"
#include QMK_KEYBOARD_H

#define VSC_BUTTON_COUNT 20
#define VSC_KEYCOMBINATION_COUNT 6
#if 0
enum VSC__enButtons
{
    enVSC_Btn_FIND_IN_FILES = SAFE_RANGE,
    enVSC_Btn_CLOSE_FILE,
    enVSC_Btn_NEW_TXT_FILE,
    enVSC_Btn_JUMP_TO_ROOT,
    enVSC_Btn_NEW_TAB ,
    enVSC_Btn_CLOSE_TAB,
    enVSC_Btn_TAB_CHANGE,
    enVSC_Btn_SWIVSCH_TAB,
    enVSC_Btn_SORT_BY_NAME,
    enVSC_Btn_SORT_BY_EXT,
    enVSC_Btn_SORT_BY_TIME,
    enVSC_Btn_SORT_BY_SIZE,
    enVSC_Btn_UNUSED_1,
    enVSC_Btn_UNUSED_2,
    enVSC_Btn_LEFT,
    enVSC_Btn_RIGHT,
    enVSC_Btn_UNUSED_4,
    enVSC_Btn_UNUSED_5,
    enVSC_Btn_UNUSED_6,
    enVSC_Btn_UNUSED_7,
    enVSC_Btn_COUNT
};
#endif

#define VSC_KEY_0   SAFE_RANGE
#define VSC_KEY_1   SAFE_RANGE + 1
#define VSC_KEY_2   SAFE_RANGE + 2
#define VSC_KEY_3   SAFE_RANGE + 3
#define VSC_KEY_4   SAFE_RANGE + 4
#define VSC_KEY_5   SAFE_RANGE + 5
#define VSC_KEY_6   SAFE_RANGE + 6
#define VSC_KEY_7   SAFE_RANGE + 7
#define VSC_KEY_8   SAFE_RANGE + 8
#define VSC_KEY_9   SAFE_RANGE + 9
#define VSC_KEY_10  SAFE_RANGE + 10
#define VSC_KEY_11  SAFE_RANGE + 11
#define VSC_KEY_12  SAFE_RANGE + 12
#define VSC_KEY_13  SAFE_RANGE + 13
#define VSC_KEY_14  SAFE_RANGE + 14
#define VSC_KEY_15  SAFE_RANGE + 15
#define VSC_KEY_16  SAFE_RANGE + 16
#define VSC_KEY_17  SAFE_RANGE + 17
#define VSC_KEY_18  SAFE_RANGE + 18
#define VSC_KEY_19  SAFE_RANGE + 19

#ifdef __VISUAL_STUDIO_CODE_SCREEN_C

struct VSC__stKeyCombination
{
    /* true means, press and false means release */
    bool m_boPress;
    uint16_t m_u16KeyCode;
};
struct VSC_stBtnInfo
{
    lv_obj_t * m_spBtn;
    const char * m_cpBtnName;
    struct VSC__stKeyCombination m_stKey[VSC_KEYCOMBINATION_COUNT];
};

static struct VSC_stBtnInfo VSC_staBtnInfo [VSC_BUTTON_COUNT] =
{
    /*[0]*/
    {
        NULL,
        "FindInF",
        {
            {true,KC_LCTL},{true,KC_LSFT},{true,KC_F},
            {false,KC_LCTL},{false,KC_LSFT},{false,KC_F}
        }
    },
    /*[1]*/
    {
        NULL,
        "CloseF",
        {
            {true,KC_LCTL},{true,KC_F4},{true,KC_NO},
            {false,KC_LCTL},{false,KC_F4},{false,KC_NO}
        }
    },
    /*[2]*/
    {
        NULL,
        "TglSbar",
        {
            {true,KC_LCTL},{true,KC_B},{true,KC_NO},
            {false,KC_LCTL},{false,KC_B},{false,KC_NO},
        }
    },
    /*[3]*/
    {
        NULL,
        "Split",
        {
            {true,KC_LCTL},{true,KC_BACKSLASH},{true,KC_NO},
            {false,KC_LCTL},{false,KC_BACKSLASH},{false,KC_NO},
        }
    },
    /*[4]*/
    {
        NULL,
        "//",
        {
            {true,KC_LCTL},{true,KC_SLASH},{true,KC_NO},
            {false,KC_LCTL},{false,KC_SLASH},{false,KC_NO},
        }
    },
    /*[5]*/
    {
        NULL,
        "TglTermal",
        {
            {true,KC_LCTL},{true,KC_GRAVE},{true,KC_NO},
            {false,KC_LCTL},{false,KC_GRAVE},{false,KC_NO},
        }
    },
    /*[6]*/
    {
        NULL,
        "",
        {
            {true,KC_NO},{true,KC_NO},{true,KC_NO},
            {false,KC_NO},{false,KC_NO},{false,KC_NO},
        }
    },
    /*[7]*/
    {
        NULL,
        "",
        {
            {true,KC_NO},{true,KC_NO},{true,KC_NO},
            {false,KC_NO},{false,KC_NO},{false,KC_NO},
        }
    },
    /*[8]*/
    {
        NULL,
        "",
        {
            {true,KC_NO},{true,KC_NO},{true,KC_NO},
            {false,KC_NO},{false,KC_NO},{false,KC_NO},
        }
    },
    /*[9]*/
    {
        NULL,
        "",
        {
            {true,KC_NO},{true,KC_NO},{true,KC_NO},
            {false,KC_NO},{false,KC_NO},{false,KC_NO},
        }
    },
    /*[10]*/
    {
        NULL,
        "",
        {
            {true,KC_NO},{true,KC_NO},{true,KC_NO},
            {false,KC_NO},{false,KC_NO},{false,KC_NO},
        }
    },
    /*[11]*/
    {
        NULL,
        "",
        {
            {true,KC_NO},{true,KC_NO},{true,KC_NO},
            {false,KC_NO},{false,KC_NO},{false,KC_NO},
        }
    },
    /*[12]*/
    {
        NULL,
        LV_SYMBOL_LEFT,
        {
            {true,KC_LCTL},{true,KC_NO},{true,KC_PAGE_UP},
            {false,KC_LCTL},{false,KC_NO},{false,KC_PAGE_UP},
        }
    },
    /*[13]*/
    {
        NULL,
        LV_SYMBOL_RIGHT,
        {
            {true,KC_LCTL},{true,KC_NO},{true,KC_PAGE_DOWN},
            {false,KC_LCTL},{false,KC_NO},{false,KC_PAGE_DOWN},
        }
    },
    /*[14]*/
    {
        NULL,
        LV_SYMBOL_PREV,
        {
            {true,KC_LCTL},{true,KC_PAGE_UP},{true,KC_NO},
            {false,KC_LCTL},{false,KC_PAGE_UP},{false,KC_NO},
        }
    },
    /*[15]*/
    {
        NULL,
        LV_SYMBOL_NEXT,
        {
            {true,KC_LCTL},{true,KC_LSFT},{true,KC_PAGE_DOWN},
            {false,KC_LCTL},{false,KC_LSFT},{false,KC_PAGE_DOWN},
        }
    },
    /*[16]*/
    {
        NULL,
        LV_SYMBOL_UP,
        {
            {true,KC_LEFT_ALT},{true,KC_UP},{true,KC_NO},
            {false,KC_LEFT_ALT},{false,KC_UP},{false,KC_NO},
        }
    },
    /*[17]*/
    {
        NULL,
        LV_SYMBOL_DOWN,
        {
            {true,KC_LEFT_ALT},{true,KC_DOWN},{true,KC_NO},
            {false,KC_LEFT_ALT},{false,KC_DOWN},{false,KC_NO},
        }
    },
    /*[18]*/
    {
        NULL,
        "    ",
        {
            {true,KC_NO},{true,KC_NO},{true,KC_NO},
            {false,KC_NO},{false,KC_NO},{false,KC_NO},
        }
    },
    /*[19]*/
    {
        NULL,
        "    ",
        {
            {true,KC_NO},{true,KC_NO},{true,KC_NO},
            {false,KC_NO},{false,KC_NO},{false,KC_NO},
        }
    },
};


#define VSC_BUTTON_SIZE_X 70
#define VSC_BUTTON_SIZE_Y 25
#define VSC_BUTTON_SPACE_X 5
#define VSC_BUTTON_SPACE_Y 5
#define VSC_X_OFFSET_FROM_LEFT 10
#define VSC_Y_OFFSET_FROM_TOP 10

typedef void (*VSC_tpfnvGuiStateFunc)(lv_obj_t *);
#endif

void VSC_vScreenCreate(lv_obj_t *);
bool VSC_boKeyPressedCallBackFunction(uint16_t );
bool VSC_boKeyReleasedCallBackFunction(uint16_t );
void VSC_vRotaryCallBackFunction(bool boClockwise, bool boRotaryButtonPressed, bool boModeButtonPressed);
