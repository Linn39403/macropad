#include <string.h>
#include <string.h>
#include "keymap.h"
#include "GUI_include.h"
#include QMK_KEYBOARD_H

enum TC_BUTTONS_ENUM
{
    TC_BUTTON_RENAME = 0,
    TC_BUTTON_PROPERTIES,
    TC_BUTTON_NEW_TXT_FILE,
    TC_BUTTON_JUMP_TO_ROOT,
    TC_BUTTON_NEW_TAB,
    TC_BUTTON_CLOSE_TAB,
    TC_BUTTON_TAB_CHANGE,
    TC_BUTTON_SWITCH_TAB,
    TC_BUTTON_SORT_BY_NAME,
    TC_BUTTON_SORT_BY_EXT,
    TC_BUTTON_SORT_BY_TIME,
    TC_BUTTON_SORT_BY_SIZE,
    TC_BUTTON_UNUSED_1,
    TC_BUTTON_UNUSED_2,
    TC_BUTTON_UNUSED_3,
    TC_BUTTON_BACK,
    TC_BUTTON_UNUSED_4,
    TC_BUTTON_UNUSED_5,
    TC_BUTTON_UNUSED_6,
    TC_BUTTON_UNUSED_7,
    TC_BUTTON_COUNT
};
#ifdef __TOTAL_COMMANDER_SCREEN_C

struct TC_stBtnInfo
{
    lv_obj_t * m_spBtn;
    const char * m_cpBtnName;
};

static struct TC_stBtnInfo TC_staBtnInfo [TC_BUTTON_COUNT] =
{
    {NULL, "RNme"},
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
    {NULL, "    "},
    {NULL, "    "},
    {NULL, "    "},
    {NULL, LV_SYMBOL_BACKSPACE},
    {NULL, "    "},
    {NULL, "    "},
    {NULL, "    "},
    {NULL, "    "},
};


#define TC_BUTTON_SIZE_X 60
#define TC_BUTTON_SIZE_Y 25
#define TC_BUTTON_SPACE_X 5
#define TC_BUTTON_SPACE_Y 5
#define TC_X_OFFSET_FROM_LEFT 10
#define TC_Y_OFFSET_FROM_TOP 10
#define TC_BUTTON_ALIGN_STYLE LV_ALIGN_DEFAULT


typedef void (*TTCMD_tpfnvGuiStateFunc)(lv_obj_t *);
#endif

void TTCMD_vScreenCreate(lv_obj_t *);
