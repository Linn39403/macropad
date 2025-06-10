#define __BROWSER_SCREEN_C
#include "browser_screen.h"
#include "print.h"

lv_obj_t* BROWSER_spVolumeTxt;
static lv_obj_t * BROWSER__spButtonCreate(lv_obj_t* spParentScreen, const char * pcText, GUI_tsBtnLocation * spBtnInfo )
{
    return GUI_spButtonCreate(spParentScreen,
                              pcText,
                              lv_color_hex(0x73FBFD),
                              lv_color_hex(0x000000),
                              spBtnInfo);
}

void BROWSER_vScreenCreate(lv_obj_t * spParentScreen)
{
    GUI_SCREEN_CREATE(BROWSER, spParentScreen);

    /* Browser Label */
    lv_obj_t* BROWSER_spVolumeTxt = lv_label_create(spParentScreen);
    lv_label_set_text(BROWSER_spVolumeTxt , "Edge Browser");
    lv_obj_set_style_text_font(BROWSER_spVolumeTxt , &lv_font_montserrat_24, LV_PART_MAIN);
    lv_obj_align(BROWSER_spVolumeTxt ,LV_ALIGN_BOTTOM_MID, 0, -10);
    lv_obj_set_style_text_align(BROWSER_spVolumeTxt ,LV_ALIGN_CENTER, 0);
    lv_obj_update_layout(BROWSER_spVolumeTxt);
}

static void BROWSER__vLayerGUIStateChange(uint16_t u16KeyCode, BROWSER_tpfnvGuiStateFunc pfnStateCb)
{
    for(uint8_t u8Idx = 0; u8Idx < 20; u8Idx++)
    {
        /* Do not call for the KC_NO buttons */
        if((KC_NO != u16KeyCode) && (BROWSER_staBtnInfo[u8Idx].m_u16KeyCode == u16KeyCode))
        {
            pfnStateCb(BROWSER_staBtnInfo[u8Idx].m_spBtn);
        }
    }
}

/* to change the button pressed animation */
bool BROWSER_boKeyPressedCallBackFunction(uint16_t u16KeyCode)
{
    BROWSER__vLayerGUIStateChange(u16KeyCode, GUI_vButtonPress);
    return BROWSER_LET_QMK_HANDLE_KEYBOARD_EVENT;
}

/* to change the button released animation */
bool BROWSER_boKeyReleasedCallBackFunction(uint16_t u16KeyCode)
{
    BROWSER__vLayerGUIStateChange(u16KeyCode, GUI_vButtonRelease);
    return BROWSER_LET_QMK_HANDLE_KEYBOARD_EVENT;
}

void BROWSER_vRotaryCallBackFunction(bool boClockwise)
{
    if(boClockwise == true)
    {
        tap_code(KC_VOLU);
    }
    else
    {
        tap_code(KC_VOLD);
    }
}
