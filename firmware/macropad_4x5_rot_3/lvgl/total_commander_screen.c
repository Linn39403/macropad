#define __TOTAL_COMMANDER_SCREEN_C
#include "total_commander_screen.h"
#include "print.h"

static lv_obj_t * TTCMD__spButtonCreate(lv_obj_t* spParentScreen, const char * pcText, GUI_tsBtnLocation * spBtnInfo )
{
    return GUI_spButtonCreate(spParentScreen,
                              pcText,
                              lv_color_hex(0x4CCF35),
                              lv_color_hex(0x000000),
                              spBtnInfo);
}

void TTCMD_vScreenCreate(lv_obj_t * spParentScreen)
{
    GUI_SCREEN_CREATE(TTCMD, spParentScreen);
}

static void TTCMD__vLayerGUIStateChange(uint16_t u16KeyCode, TTCMD_tpfnvGuiStateFunc pfnStateCb)
{
    switch(u16KeyCode)
    {
        case TTCMD_KEY_0:
            pfnStateCb(TTCMD_staBtnInfo[TTCMD_BUTTON_RENAME].m_spBtn);
        break;
        case TTCMD_KEY_1:
            pfnStateCb(TTCMD_staBtnInfo[TTCMD_BUTTON_PROPERTIES].m_spBtn);
        break;
        case TTCMD_KEY_2:
            pfnStateCb(TTCMD_staBtnInfo[TTCMD_BUTTON_NEW_TXT_FILE].m_spBtn);
        break;
        case TTCMD_KEY_3:
            pfnStateCb(TTCMD_staBtnInfo[TTCMD_BUTTON_JUMP_TO_ROOT].m_spBtn);
        break;
        case TTCMD_KEY_4:
            pfnStateCb(TTCMD_staBtnInfo[TTCMD_BUTTON_NEW_TAB].m_spBtn);
        break;
        case TTCMD_KEY_5:
            pfnStateCb(TTCMD_staBtnInfo[TTCMD_BUTTON_CLOSE_TAB].m_spBtn);
        break;
        case TTCMD_KEY_6:
            pfnStateCb(TTCMD_staBtnInfo[TTCMD_BUTTON_TAB_CHANGE].m_spBtn);
        break;
        case TTCMD_KEY_7:
            pfnStateCb(TTCMD_staBtnInfo[TTCMD_BUTTON_SWITCH_TAB].m_spBtn);
        break;
        case TTCMD_KEY_8:
            pfnStateCb(TTCMD_staBtnInfo[TTCMD_BUTTON_SORT_BY_NAME].m_spBtn);
        break;
        case TTCMD_KEY_9:
            pfnStateCb(TTCMD_staBtnInfo[TTCMD_BUTTON_SORT_BY_EXT].m_spBtn);
        break;
        case TTCMD_KEY_10:
            pfnStateCb(TTCMD_staBtnInfo[TTCMD_BUTTON_SORT_BY_TIME].m_spBtn);
        break;
        case TTCMD_KEY_11:
            pfnStateCb(TTCMD_staBtnInfo[TTCMD_BUTTON_SORT_BY_SIZE].m_spBtn);
        break;
        case TTCMD_KEY_12:
            pfnStateCb(TTCMD_staBtnInfo[TTCMD_BUTTON_CANCEL].m_spBtn);
        break;
        case TTCMD_KEY_15:
            pfnStateCb(TTCMD_staBtnInfo[TTCMD_BUTTON_BACK].m_spBtn);
        break;
        case KC_NO:
            /* Do nothing because this key is not used*/
        break;
        default:
        break;
    }
}

/* to change the button pressed animation */
void TTCMD_vKeyPressedCallBackFunction(uint16_t u16KeyCode)
{
    TTCMD__vLayerGUIStateChange(u16KeyCode, GUI_vButtonPress);
}

/* to change the button released animation */
void TTCMD_vKeyReleasedCallBackFunction(uint16_t u16KeyCode)
{
    TTCMD__vLayerGUIStateChange(u16KeyCode, GUI_vButtonRelease);
}


