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
}

static bool VSC__boLayerGUIStateChange(uint16_t u16KeyCode, VSC_tpfnvGuiStateFunc pfnStateCb)
{
    switch(u16KeyCode)
    {
        case S(S(KC_F)):
            return(VSC_staBtnInfo[VSC_BUTTON_FIND_IN_FILES].m_boQMKKeyHandle);
        case LCTL(KC_F4):
            return(VSC_staBtnInfo[VSC_BUTTON_CLOSE_FILE].m_boQMKKeyHandle);
        case C(S(KC_PGUP)):
            return(VSC_staBtnInfo[VSC_BUTTON_LEFT].m_boQMKKeyHandle);
        case C(S(KC_PGDN)):
            return(VSC_staBtnInfo[VSC_BUTTON_RIGHT].m_boQMKKeyHandle);
        default:
            /* default: Custom Key Handling */
            return false;
    }

}

/* to change the button pressed animation for the keypad screen */
bool VSC_boKeyPressedCallBackFunction(uint16_t u16KeyCode)
{
    return VSC__boLayerGUIStateChange(u16KeyCode, GUI_vButtonPress);
}

/* to change the button released animation for the keypad screen */
bool VSC_boKeyReleasedCallBackFunction(uint16_t u16KeyCode)
{
    return VSC__boLayerGUIStateChange(u16KeyCode, GUI_vButtonRelease);
}


