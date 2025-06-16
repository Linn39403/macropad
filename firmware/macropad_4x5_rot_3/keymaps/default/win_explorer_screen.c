#define __WIN_EXPLORER_SCREEN_C
#include "win_explorer_screen.h"
#include "print.h"

static lv_obj_t * WIN_EXPLORER__spButtonCreate(lv_obj_t* spParentScreen, const char * pcText, GUI_tsBtnLocation * spBtnInfo )
{
    return GUI_spButtonCreate(spParentScreen,
                              pcText,
                              lv_color_hex(0xf3b51e),
                              lv_color_hex(0x000000),
                              spBtnInfo);
}

void WIN_EXPLORER_vScreenCreate(lv_obj_t * spParentScreen)
{
    GUI_SCREEN_CREATE(WIN_EXPLORER, spParentScreen);

    /* Total Commander Label */
    lv_obj_t* WIN_EXPLORER_spVolumeTxt = lv_label_create(spParentScreen);
    lv_label_set_text(WIN_EXPLORER_spVolumeTxt , "Total Commander");
    lv_obj_set_style_text_font(WIN_EXPLORER_spVolumeTxt , &lv_font_montserrat_24, LV_PART_MAIN);
    lv_obj_align(WIN_EXPLORER_spVolumeTxt ,LV_ALIGN_BOTTOM_MID, 0, -10);
    lv_obj_set_style_text_align(WIN_EXPLORER_spVolumeTxt ,LV_ALIGN_CENTER, 0);
    lv_obj_update_layout(WIN_EXPLORER_spVolumeTxt);
}

static void WIN_EXPLORER__vLayerGUIStateChange(uint16_t u16KeyCode, WIN_EXPLORER_tpfnvGuiStateFunc pfnStateCb)
{
    for(uint8_t u8Idx = 0; u8Idx < 20; u8Idx++)
    {
        /* Do not call for the KC_NO buttons */
        if((KC_NO != u16KeyCode) && (WIN_EXPLORER_staBtnInfo[u8Idx].m_u16KeyCode == u16KeyCode))
        {
            pfnStateCb(WIN_EXPLORER_staBtnInfo[u8Idx].m_spBtn);
        }
    }
}

/* to change the button pressed animation */
bool WIN_EXPLORER_boKeyPressedCallBackFunction(uint16_t u16KeyCode)
{
    WIN_EXPLORER__vLayerGUIStateChange(u16KeyCode, GUI_vButtonPress);
    return true;
}

/* to change the button released animation */
bool WIN_EXPLORER_boKeyReleasedCallBackFunction(uint16_t u16KeyCode)
{
    WIN_EXPLORER__vLayerGUIStateChange(u16KeyCode, GUI_vButtonRelease);
    return true;
}

void WIN_EXPLORER_vRotaryCallBackFunction(bool boClockwise, bool boRotaryButtonPressed, bool boModeButtonPressed)
{
    if(boRotaryButtonPressed == false)
    {
        tap_code(KC_ENT);
    }
    if(boModeButtonPressed == false)
    {
    }
    else
    {
        if(boClockwise == true)
            tap_code(KC_UP);
        else
            tap_code(KC_DOWN);
    }
}

void WIN_EXPLORER_vHouseKeeping(void)
{

}
