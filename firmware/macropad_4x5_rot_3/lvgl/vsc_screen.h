#pragma once
#include "GUI_helper.h"
#include QMK_KEYBOARD_H

enum VSC_BUTTONS_ENUM
{
    VSC_BUTTON_FIND_IN_FILES = 0,
    VSC_BUTTON_CLOSE_FILE,
    VSC_BUTTON_NEW_TXT_FILE,
    VSC_BUTTON_JUMP_TO_ROOT,

    VSC_BUTTON_NEW_TAB,
    VSC_BUTTON_CLOSE_TAB,
    VSC_BUTTON_TAB_CHANGE,
    VSC_BUTTON_SWIVSCH_TAB,

    VSC_BUTTON_SORT_BY_NAME,
    VSC_BUTTON_SORT_BY_EXT,
    VSC_BUTTON_SORT_BY_TIME,
    VSC_BUTTON_SORT_BY_SIZE,

    VSC_BUTTON_UNUSED_1,
    VSC_BUTTON_UNUSED_2,
    VSC_BUTTON_LEFT,
    VSC_BUTTON_RIGHT,

    VSC_BUTTON_UNUSED_4,
    VSC_BUTTON_UNUSED_5,
    VSC_BUTTON_UNUSED_6,
    VSC_BUTTON_UNUSED_7,
    VSC_BUTTON_COUNT
};
#ifdef __VISUAL_STUDIO_CODE_SCREEN_C

struct VSC_stBtnInfo
{
    lv_obj_t * m_spBtn;
    /* True -> let QMK handle the key event.
     *  False -> Custom Key handling.
    */
    bool m_boQMKKeyHandle;
    const char * m_cpBtnName;
};

static struct VSC_stBtnInfo VSC_staBtnInfo [VSC_BUTTON_COUNT] =
{
    {NULL, false, "FindInF"},
    {NULL, false, "CloseF"},
    {NULL, true, "    "},
    {NULL, true, "    "},

    {NULL, true, "    "},
    {NULL, true, "    "},
    {NULL, true, "    "},
    {NULL, true, "    "},

    {NULL, true, "    "},
    {NULL, true, "    "},
    {NULL, true, "    "},
    {NULL, true, "    "},

    {NULL, true, "    "},
    {NULL, true, "    "},
    {NULL, false, LV_SYMBOL_LEFT},
    {NULL, false, LV_SYMBOL_RIGHT},

    {NULL, true, "    "},
    {NULL, true, "    "},
    {NULL, true, "    "},
    {NULL, true, "    "},
};


#define VSC_BUTTON_SIZE_X 60
#define VSC_BUTTON_SIZE_Y 25
#define VSC_BUTTON_SPACE_X 5
#define VSC_BUTTON_SPACE_Y 5
#define VSC_X_OFFSET_FROM_LEFT 10
#define VSC_Y_OFFSET_FROM_TOP 10

typedef void (*VSC_tpfnvGuiStateFunc)(lv_obj_t *);
#endif

void VSC_vScreenCreate(lv_obj_t *);
