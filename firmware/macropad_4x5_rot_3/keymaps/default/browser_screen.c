#define __BROWSER_SCREEN_C
#include "browser_screen.h"
#include "print.h"

static lv_obj_t* BROWSER_spKnobText;
static uint16_t BROWSER__u16ScreenTimer = 0;
#define BROWSER_DEFAULT_KNOB_TEXT    "Vol-                  Vol+"
#define BROWSER_BTN_PRESS_KNOB_TEXT  "Up                    Down"
#define BROWSER_EMPTY_KNOB_TEXT      "                          "
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
    lv_obj_t* BROWSER_spScreen = lv_label_create(spParentScreen);
    lv_label_set_text(BROWSER_spScreen , "Edge Browser");
    lv_obj_set_style_text_font(BROWSER_spScreen , &lv_font_montserrat_24, LV_PART_MAIN);
    lv_obj_align(BROWSER_spScreen ,LV_ALIGN_BOTTOM_MID, 0, -10);
    lv_obj_set_style_text_align(BROWSER_spScreen ,LV_ALIGN_CENTER, 0);
    lv_obj_update_layout(BROWSER_spScreen);


    /* Knob Text */
    BROWSER_spKnobText = lv_label_create(spParentScreen);
    lv_label_set_text(BROWSER_spKnobText, BROWSER_EMPTY_KNOB_TEXT);
    lv_obj_set_style_text_font(BROWSER_spKnobText , &lv_font_montserrat_24, LV_PART_MAIN);
    lv_obj_set_style_text_color(BROWSER_spKnobText, lv_color_hex(0xFC6703), 0);
    lv_obj_align(BROWSER_spKnobText ,LV_ALIGN_BOTTOM_MID, 0, -40);
    lv_obj_set_style_text_align(BROWSER_spKnobText ,LV_ALIGN_CENTER, 0);
    lv_obj_update_layout(BROWSER_spKnobText);
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

void BROWSER_vRotaryCallBackFunction(bool boClockwise, bool boRotaryButtonPressed, bool boModeButtonPressed)
{
    if(boRotaryButtonPressed == false)
    {

    }
    if(boModeButtonPressed == true)
    {
        /* Button Not Pressed */
        BROWSER__u16ScreenTimer = timer_read();
        lv_label_set_text(BROWSER_spKnobText, BROWSER_BTN_PRESS_KNOB_TEXT);
        if(boClockwise == true){
            tap_code(KC_MS_WH_DOWN);
        }
        else{
            tap_code(KC_MS_WH_UP);
        }
    }
    else
    {
        /* Button Pressed */
        BROWSER__u16ScreenTimer = timer_read();
        lv_label_set_text(BROWSER_spKnobText, BROWSER_DEFAULT_KNOB_TEXT);
        if(boClockwise == true)
            tap_code(KC_VOLU);
        else
            tap_code(KC_VOLD);
    }
}

void BROWSER_vHouseKeeping(void)
{
    if(BROWSER__u16ScreenTimer && timer_elapsed(BROWSER__u16ScreenTimer) > 3000)
    {
        BROWSER__u16ScreenTimer = 0;
        lv_label_set_text(BROWSER_spKnobText, BROWSER_EMPTY_KNOB_TEXT);
    }
}
