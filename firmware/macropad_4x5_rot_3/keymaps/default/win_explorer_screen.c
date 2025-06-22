#define __WIN_EXPLORER_SCREEN_C
#include "win_explorer_screen.h"
#include "print.h"

static lv_obj_t * WIN_EXPLORER__spButtonCreate(lv_obj_t* spParentScreen,
                                               const char * pcText,
                                               const lv_font_t * font_name,
                                               GUI_tsBtnLocation * spBtnInfo )
{
    return GUI_spButtonCreate(spParentScreen,
                              pcText,
                              font_name,
                              lv_color_hex(0xf3b51e),
                              lv_color_hex(0x000000),
                              spBtnInfo);
}

void WIN_EXPLORER_vScreenCreate(lv_obj_t * spParentScreen)
{
    GUI_SCREEN_CREATE(WIN_EXPLORER, spParentScreen);

    /* Total Commander Label */
    GUI_spLayerNameCreate(spParentScreen,
                          "Window Explorer",
                          &lv_font_montserrat_24);
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

void WIN_EXPLORER_vRotaryCallBackFunction(bool boClockwise, bool boModeButtonPressed)
{
    if(boModeButtonPressed == false)
    {
        register_code(KC_LSFT);
    }
    else
    {
        unregister_code(KC_LSFT);
    }
    if(boClockwise == false)
        tap_code(KC_UP);
    else
        tap_code(KC_DOWN);
}

void WIN_EXPLORER_vRotaryButtonPressedCallBackFunction(void)
{
    tap_code(KC_ENT);
}

void WIN_EXPLORER_vHouseKeeping(void)
{

}
