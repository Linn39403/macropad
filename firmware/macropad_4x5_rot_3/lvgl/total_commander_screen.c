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

    /* Total Commander Label */
    lv_obj_t* TTCMD_spVolumeTxt = lv_label_create(spParentScreen);
    lv_label_set_text(TTCMD_spVolumeTxt , "Total Commander");
    lv_obj_set_style_text_font(TTCMD_spVolumeTxt , &lv_font_montserrat_24, LV_PART_MAIN);
    lv_obj_align(TTCMD_spVolumeTxt ,LV_ALIGN_DEFAULT, 40, 200);
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
bool TOTAL_COMMANDER_boKeyPressedCallBackFunction(uint16_t u16KeyCode)
{
    TTCMD__vLayerGUIStateChange(u16KeyCode, GUI_vButtonPress);
    return true;
}

/* to change the button released animation */
bool TOTAL_COMMANDER_boKeyReleasedCallBackFunction(uint16_t u16KeyCode)
{
    TTCMD__vLayerGUIStateChange(u16KeyCode, GUI_vButtonRelease);
    return true;
}


