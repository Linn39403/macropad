#define __VISUAL_STUDIO_CODE_SCREEN_C
#include "vsc_screen.h"

static lv_obj_t * VSC__spButtonCreate(lv_obj_t* spParentScreen, const char * pcText, GUI_tsBtnLocation * spBtnInfo )
{
    return GUI_spButtonCreate(spParentScreen,
                          pcText,
                          lv_color_hex(0x1177CF),
                          lv_color_hex(0xC7C7C7),
                          spBtnInfo);
}

void VSC_vScreenCreate(lv_obj_t * spParentScreen)
{
    GUI_SCREEN_CREATE(VSC, spParentScreen);

    /* Visual Studio Code Label */
    lv_obj_t* VSC_spVolumeTxt = lv_label_create(spParentScreen);
    lv_label_set_text(VSC_spVolumeTxt , "Visual Studio Code");
    lv_obj_set_style_text_font(VSC_spVolumeTxt , &lv_font_montserrat_24, LV_PART_MAIN);
    lv_obj_align(VSC_spVolumeTxt ,LV_ALIGN_BOTTOM_MID, 0, -10);
    lv_obj_set_style_text_align(VSC_spVolumeTxt ,LV_ALIGN_CENTER, 0);
    lv_obj_update_layout(VSC_spVolumeTxt);
}

static void VSC__executeKeys(uint16_t u16Index, bool boKeyPressed)
{
    for(uint8_t u8Cnt = 0; u8Cnt < VSC_KEYCOMBINATION_COUNT; u8Cnt++)
    {
        if(boKeyPressed && (VSC_staBtnInfo[u16Index].m_stKey[u8Cnt].m_boPress == true))
        {
            register_code(VSC_staBtnInfo[u16Index].m_stKey[u8Cnt].m_u16KeyCode);
        }
        else
        {
            unregister_code(VSC_staBtnInfo[u16Index].m_stKey[u8Cnt].m_u16KeyCode);
        }
    }
}

static bool VSC__boLayerGUIStateChange(uint16_t u16KeyCode, bool boKeyPressed, VSC_tpfnvGuiStateFunc pfnStateCb)
{
    //want to optimize this function
    uint8_t u8Index = u16KeyCode - SAFE_RANGE;
    if(u16KeyCode >= VSC_KEY_0 && u16KeyCode <= VSC_KEY_19)
    {
        VSC__executeKeys(u8Index, boKeyPressed);
        pfnStateCb(VSC_staBtnInfo[u8Index].m_spBtn);
        return false;
    }

    /* Return True -> Let QMK Handle Key Event */
    /* Return False -> User Handle Key Event */
    return true;
}

/* to change the button pressed animation for the keypad screen */
bool VSC_boKeyPressedCallBackFunction(uint16_t u16KeyCode)
{
    return VSC__boLayerGUIStateChange(u16KeyCode, true, GUI_vButtonPress);
}

/* to change the button released animation for the keypad screen */
bool VSC_boKeyReleasedCallBackFunction(uint16_t u16KeyCode)
{
    return VSC__boLayerGUIStateChange(u16KeyCode, false, GUI_vButtonRelease);
}

void VSC_vRotaryCallBackFunction(bool boClockwise, bool boRotaryButtonPressed, bool boModeButtonPressed)
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
