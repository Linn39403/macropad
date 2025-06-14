#define __FUNKEYS_SCREEN_C
#include "funkeys_screen.h"
#include "print.h"

static lv_obj_t * FUNKEYS__spButtonCreate(lv_obj_t* spParentScreen, const char * pcText, GUI_tsBtnLocation * spBtnInfo )
{
    return GUI_spButtonCreate(spParentScreen,
                              pcText,
                              lv_color_hex(0xbf15e6),
                              lv_color_hex(0xFFFFFF),
                              spBtnInfo);
}

void FUNKEYS_vScreenCreate(lv_obj_t * spParentScreen)
{
    GUI_SCREEN_CREATE(FUNKEYS, spParentScreen);

    /* Total Commander Label */
    lv_obj_t* FUNKEYS_spVolumeTxt = lv_label_create(spParentScreen);
    lv_label_set_text(FUNKEYS_spVolumeTxt , "FUN Keys");
    lv_obj_set_style_text_font(FUNKEYS_spVolumeTxt , &lv_font_montserrat_24, LV_PART_MAIN);
    lv_obj_align(FUNKEYS_spVolumeTxt ,LV_ALIGN_BOTTOM_MID, 0, -10);
    lv_obj_set_style_text_align(FUNKEYS_spVolumeTxt ,LV_ALIGN_CENTER, 0);
    lv_obj_update_layout(FUNKEYS_spVolumeTxt);
}

static void FUNKEYS__vLayerGUIStateChange(uint16_t u16KeyCode, FUNKEYS_tpfnvGuiStateFunc pfnStateCb)
{
    for(uint8_t u8Idx = 0; u8Idx < 20; u8Idx++)
    {
        /* Do not call for the KC_NO buttons */
        if((KC_NO != u16KeyCode) && (FUNKEYS_staBtnInfo[u8Idx].m_u16KeyCode == u16KeyCode))
        {
            pfnStateCb(FUNKEYS_staBtnInfo[u8Idx].m_spBtn);
        }
    }
}

/* to change the button pressed animation */
bool FUNKEYS_boKeyPressedCallBackFunction(uint16_t u16KeyCode)
{
    FUNKEYS__vLayerGUIStateChange(u16KeyCode, GUI_vButtonPress);
    return true;
}

/* to change the button released animation */
bool FUNKEYS_boKeyReleasedCallBackFunction(uint16_t u16KeyCode)
{
    FUNKEYS__vLayerGUIStateChange(u16KeyCode, GUI_vButtonRelease);
    return true;
}

void FUNKEYS_vRotaryCallBackFunction(bool boClockwise, bool boRotaryButtonPressed, bool boModeButtonPressed)
{
    if(boRotaryButtonPressed == false)
    {

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
