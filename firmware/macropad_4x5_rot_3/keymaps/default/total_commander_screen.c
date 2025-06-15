#define __TOTAL_COMMANDER_SCREEN_C
#include "total_commander_screen.h"
#include "print.h"

static lv_obj_t * TOTAL_COMMANDER__spButtonCreate(lv_obj_t* spParentScreen, const char * pcText, GUI_tsBtnLocation * spBtnInfo )
{
    return GUI_spButtonCreate(spParentScreen,
                              pcText,
                              lv_color_hex(0x4CCF35),
                              lv_color_hex(0x000000),
                              spBtnInfo);
}

void TOTAL_COMMANDER_vScreenCreate(lv_obj_t * spParentScreen)
{
    GUI_SCREEN_CREATE(TOTAL_COMMANDER, spParentScreen);

    /* Total Commander Label */
    lv_obj_t* TOTAL_COMMANDER_spVolumeTxt = lv_label_create(spParentScreen);
    lv_label_set_text(TOTAL_COMMANDER_spVolumeTxt , "Total Commander");
    lv_obj_set_style_text_font(TOTAL_COMMANDER_spVolumeTxt , &lv_font_montserrat_24, LV_PART_MAIN);
    lv_obj_align(TOTAL_COMMANDER_spVolumeTxt ,LV_ALIGN_BOTTOM_MID, 0, -10);
    lv_obj_set_style_text_align(TOTAL_COMMANDER_spVolumeTxt ,LV_ALIGN_CENTER, 0);
    lv_obj_update_layout(TOTAL_COMMANDER_spVolumeTxt);
}

static void TOTAL_COMMANDER__vLayerGUIStateChange(uint16_t u16KeyCode, TOTAL_COMMANDER_tpfnvGuiStateFunc pfnStateCb)
{
    for(uint8_t u8Idx = 0; u8Idx < 20; u8Idx++)
    {
        /* Do not call for the KC_NO buttons */
        if((KC_NO != u16KeyCode) && (TOTAL_COMMANDER_staBtnInfo[u8Idx].m_u16KeyCode == u16KeyCode))
        {
            pfnStateCb(TOTAL_COMMANDER_staBtnInfo[u8Idx].m_spBtn);
        }
    }
}

/* to change the button pressed animation */
bool TOTAL_COMMANDER_boKeyPressedCallBackFunction(uint16_t u16KeyCode)
{
    TOTAL_COMMANDER__vLayerGUIStateChange(u16KeyCode, GUI_vButtonPress);
    return true;
}

/* to change the button released animation */
bool TOTAL_COMMANDER_boKeyReleasedCallBackFunction(uint16_t u16KeyCode)
{
    TOTAL_COMMANDER__vLayerGUIStateChange(u16KeyCode, GUI_vButtonRelease);
    return true;
}

void TOTAL_COMMANDER_vRotaryCallBackFunction(bool boClockwise, bool boRotaryButtonPressed, bool boModeButtonPressed)
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

void TOTAL_COMMANDER_vHouseKeeping(void)
{

}
