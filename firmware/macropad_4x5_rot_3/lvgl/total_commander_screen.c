#define __TOTAL_COMMANDER_SCREEN_C
#include "total_commander_screen.h"
#include "print.h"

static lv_obj_t * TTCMD__spButtonCreate(lv_obj_t* spParentScreen, const char * pcText, GUI_tsBtnLocation * spBtnInfo )
{
    lv_obj_t *spBtn = lv_btn_create(spParentScreen);
    lv_obj_set_size(spBtn, spBtnInfo->m_u8BtnSizeX, spBtnInfo->m_u8BtnSizeY);
    lv_obj_align(spBtn, TC_BUTTON_ALIGN_STYLE, spBtnInfo->m_u8BtnLocX, spBtnInfo->m_u8BtnLocY);

    /* Keypad Button Color */
    lv_obj_set_style_bg_color(spBtn, lv_color_hex(0x4CCF35), 0);

    lv_obj_t* spBtnLabel = lv_label_create(spBtn);
    lv_label_set_text(spBtnLabel, pcText);
    lv_obj_center(spBtnLabel);

    /* Keypad Text Color */
    lv_obj_set_style_text_color(spBtnLabel, lv_color_hex(0xffffff), 0);
    return spBtn;
}

void TTCMD_vScreenCreate(lv_obj_t * spParentScreen)
{
    uint8_t u8RowCnt = 4; /* 4 buttons per row */
    uint8_t u8ColCnt = TC_BUTTON_COUNT / u8RowCnt;

    /* 4 buttons per role, 5 rows in total */
    GUI_tsBtnLocation stBtnLoc;
    stBtnLoc.m_u8BtnSizeX = TC_BUTTON_SIZE_X;
    stBtnLoc.m_u8BtnSizeY = TC_BUTTON_SIZE_Y;

    for(uint8_t u8Col = 0; u8Col < u8ColCnt; u8Col++)
    {
        for(uint8_t u8Row = 0; u8Row < u8RowCnt; u8Row++)
        {
            stBtnLoc.m_u8BtnLocX = TC_X_OFFSET_FROM_LEFT + (u8Row * TC_BUTTON_SPACE_X) + (u8Row * TC_BUTTON_SIZE_X);
            stBtnLoc.m_u8BtnLocY = TC_Y_OFFSET_FROM_TOP + (u8Col * TC_BUTTON_SPACE_Y) + (u8Col * TC_BUTTON_SIZE_Y);
            TC_staBtnInfo[u8Row+(u8RowCnt*u8Col)].m_spBtn = TTCMD__spButtonCreate(
                                              spParentScreen,
                                              TC_staBtnInfo[u8Row+(u8RowCnt*u8Col)].m_cpBtnName ,
                                              &stBtnLoc);
        }
    }
}

static void TTCMD__vLayerGUIStateChange(uint16_t u16KeyCode, TTCMD_tpfnvGuiStateFunc pfnStateCb)
{
    switch(u16KeyCode)
    {
        case S(KC_F6):
            pfnStateCb(TC_staBtnInfo[TC_BUTTON_RENAME].m_spBtn);
        break;
        case S(KC_F10):
            pfnStateCb(TC_staBtnInfo[TC_BUTTON_PROPERTIES].m_spBtn);
        break;
        case S(KC_F4):
            pfnStateCb(TC_staBtnInfo[TC_BUTTON_NEW_TXT_FILE].m_spBtn);
        break;
        case LCTL(KC_BSLS):
            pfnStateCb(TC_staBtnInfo[TC_BUTTON_JUMP_TO_ROOT].m_spBtn);
        break;
        case LCTL(KC_UP):
            pfnStateCb(TC_staBtnInfo[TC_BUTTON_NEW_TAB].m_spBtn);
        break;
        case LCTL(KC_W):
            pfnStateCb(TC_staBtnInfo[TC_BUTTON_CLOSE_TAB].m_spBtn);
        break;
        case LCTL(KC_TAB):
            pfnStateCb(TC_staBtnInfo[TC_BUTTON_TAB_CHANGE].m_spBtn);
        break;
        case KC_TAB:
            pfnStateCb(TC_staBtnInfo[TC_BUTTON_SWITCH_TAB].m_spBtn);
        break;
        case LCTL(KC_F3):
            pfnStateCb(TC_staBtnInfo[TC_BUTTON_SORT_BY_NAME].m_spBtn);
        break;
        case LCTL(KC_F4):
            pfnStateCb(TC_staBtnInfo[TC_BUTTON_SORT_BY_EXT].m_spBtn);
        break;
        case LCTL(KC_F5):
            pfnStateCb(TC_staBtnInfo[TC_BUTTON_SORT_BY_TIME].m_spBtn);
        break;
        case LCTL(KC_F6):
            pfnStateCb(TC_staBtnInfo[TC_BUTTON_SORT_BY_SIZE].m_spBtn);
        break;
        case KC_BACKSPACE:
            pfnStateCb(TC_staBtnInfo[TC_BUTTON_BACK].m_spBtn);
        break;
        case KC_NO:
            /* Do nothing because these keys are not used*/
        break;
        default:
        break;
    }
}

static inline void TTCMD__vButtonPress(lv_obj_t * spButton)
{
    lv_obj_add_state(spButton, LV_STATE_PRESSED);
}

static inline void TTCMD__vButtonRelease(lv_obj_t * spButton)
{
    lv_obj_clear_state(spButton, LV_STATE_PRESSED);
}

/* to change the button pressed animation for the keypad screen */
void TTCMD_vKeyPressedCallBackFunction(uint16_t u16KeyCode)
{
    TTCMD__vLayerGUIStateChange(u16KeyCode, TTCMD__vButtonPress);
}

/* to change the button released animation for the keypad screen */
void TTCMD_vKeyReleasedCallBackFunction(uint16_t u16KeyCode)
{
    TTCMD__vLayerGUIStateChange(u16KeyCode, TTCMD__vButtonRelease);
}


