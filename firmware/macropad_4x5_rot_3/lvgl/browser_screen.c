#define __BROWSER_SCREEN_C
#include "browser_screen.h"
#include "print.h"

lv_obj_t* BWSER_spVolumeTxt;
static lv_obj_t * BWSER__spButtonCreate(lv_obj_t* spParentScreen, const char * pcText, GUI_tsBtnLocation * spBtnInfo )
{
    return GUI_spButtonCreate(spParentScreen,
                              pcText,
                              lv_color_hex(0x73FBFD),
                              lv_color_hex(0x000000),
                              spBtnInfo);
}

void BWSER_vScreenCreate(lv_obj_t * spParentScreen)
{
    GUI_SCREEN_CREATE(BWSER, spParentScreen);

    /* Browser Label */
    lv_obj_t* BWSER_spVolumeTxt = lv_label_create(spParentScreen);
    lv_label_set_text(BWSER_spVolumeTxt , "Edge Browser");
    lv_obj_set_style_text_font(BWSER_spVolumeTxt , &lv_font_montserrat_24, LV_PART_MAIN);
    lv_obj_align(BWSER_spVolumeTxt ,LV_ALIGN_DEFAULT, 40, 200);
}

static void BWSER__vLayerGUIStateChange(uint16_t u16KeyCode, BWSER_tpfnvGuiStateFunc pfnStateCb)
{
    for(uint8_t u8Idx = 0; u8Idx < 20; u8Idx++)
    {
        /* Do not call for the KC_NO buttons */
        if((KC_NO != u16KeyCode) && (BWSER_staBtnInfo[u8Idx].m_u16KeyCode == u16KeyCode))
        {
            pfnStateCb(BWSER_staBtnInfo[u8Idx].m_spBtn);
        }
    }
}

/* to change the button pressed animation */
bool BROWSER_boKeyPressedCallBackFunction(uint16_t u16KeyCode)
{
    BWSER__vLayerGUIStateChange(u16KeyCode, GUI_vButtonPress);
    return BWSER_LET_QMK_HANDLE_KEYBOARD_EVENT;
}

/* to change the button released animation */
bool BROWSER_boKeyReleasedCallBackFunction(uint16_t u16KeyCode)
{
    BWSER__vLayerGUIStateChange(u16KeyCode, GUI_vButtonRelease);
    return BWSER_LET_QMK_HANDLE_KEYBOARD_EVENT;
}


