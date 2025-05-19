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
    for(uint8_t u8Idx = 0; u8Idx < 20; u8Idx++)
    {
        /* Do not call for the KC_NO buttons */
        if((KC_NO != u16KeyCode) && (TTCMD_staBtnInfo[u8Idx].m_u16KeyCode == u16KeyCode))
        {
            pfnStateCb(TTCMD_staBtnInfo[u8Idx].m_spBtn);
        }
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


