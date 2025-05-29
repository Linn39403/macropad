#pragma once
#include "GUI_helper.h"
#include QMK_KEYBOARD_H

#define VSC_BUTTON_COUNT 20
#define VSC_KEYCOMBINATION_COUNT 6
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
            {true,KC_LCTL},{true,KC_W},{true,KC_NO},
            {false,KC_LCTL},{false,KC_W},{false,KC_NO}
        }
    },
    /*[2]*/
    {
        NULL,
        "",
        {
            {true,KC_NO},{true,KC_NO},{true,KC_NO},
            {false,KC_NO},{false,KC_NO},{false,KC_NO},
        }
    },
    /*[3]*/
    {
        NULL,
        "",
        {
            {true,KC_NO},{true,KC_NO},{true,KC_NO},
            {false,KC_NO},{false,KC_NO},{false,KC_NO},
        }
    },
    /*[4]*/
    {
        NULL,
        "",
        {
            {true,KC_NO},{true,KC_NO},{true,KC_NO},
            {false,KC_NO},{false,KC_NO},{false,KC_NO},
        }
    },
    /*[5]*/
    {
        NULL,
        "",
        {
            {true,KC_NO},{true,KC_NO},{true,KC_NO},
            {false,KC_NO},{false,KC_NO},{false,KC_NO},
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
        "    ",
        {
            {true,KC_NO},{true,KC_NO},{true,KC_NO},
            {false,KC_NO},{false,KC_NO},{false,KC_NO},
        }
    },
    /*[17]*/
    {
        NULL,
        "    ",
        {
            {true,KC_NO},{true,KC_NO},{true,KC_NO},
            {false,KC_NO},{false,KC_NO},{false,KC_NO},
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
#define VSC_BUTTON_SIZE_Y 30
#define VSC_BUTTON_SPACE_X 5
#define VSC_BUTTON_SPACE_Y 5
#define VSC_X_OFFSET_FROM_LEFT 10
#define VSC_Y_OFFSET_FROM_TOP 10

typedef void (*VSC_tpfnvGuiStateFunc)(lv_obj_t *);
#endif

void VSC_vScreenCreate(lv_obj_t *);
bool VSC_boKeyPressedCallBackFunction(uint16_t );
bool VSC_boKeyReleasedCallBackFunction(uint16_t );
