#define __VISUAL_STUDIO_CODE_SCREEN_C
#include "vsc_screen.h"

static lv_obj_t* VSC_spKnobText;
static uint16_t VSC__u16ScreenTimer = 0;
#define VSC_KNOB_UP_DOWN_TEXT        FA_ROTATE_LEFT_CODE "  " FA_ANGLE_DOWN_CODE         "                " FA_ROTATE_RIGHT_CODE "  " FA_ANGLE_UP_CODE
#define VSC_KNOB_2X_UP_DOWN_TEXT     FA_ROTATE_LEFT_CODE "  " FA_ANGLE_DOUBLE_DOWN_CODE  "                " FA_ROTATE_RIGHT_CODE "  " FA_ANGLE_DOUBLE_UP_CODE
#define VSC_KNOB_LEFT_RIGHT_TEXT     FA_ROTATE_LEFT_CODE "  " FA_ANGLE_LEFT_CODE         "                " FA_ROTATE_RIGHT_CODE "  " FA_ANGLE_RIGHT_CODE
#define VSC_KNOB_2X_LEFT_RIGHT_TEXT  FA_ROTATE_LEFT_CODE "  " FA_ANGLE_DOUBLE_LEFT_CODE  "                " FA_ROTATE_RIGHT_CODE "  " FA_ANGLE_DOUBLE_RIGHT_CODE
#define VSC_KNOB_EMPTY_TEXT          "                              "

enum VSC__enKNOB_State
{
    enKnobUpDown_State = 0,
    enKnobLeftRight_State
};
enum VSC__enKNOB_State VSC__enKNOB_State = enKnobUpDown_State;

static lv_obj_t * VSC__spButtonCreate(lv_obj_t* spParentScreen,
                                      const char * pcText,
                                      const lv_font_t * font_name,
                                      GUI_tsBtnLocation * spBtnInfo )
{
    return GUI_spButtonCreate(spParentScreen,
                          pcText,
                          font_name,
                          lv_color_hex(0x1177CF),
                          lv_color_hex(0xC7C7C7),
                          spBtnInfo);
}

void VSC_vScreenCreate(lv_obj_t * spParentScreen)
{
    GUI_SCREEN_CREATE(VSC, spParentScreen);

    /* Visual Studio Code Label */
    GUI_spLayerNameCreate(spParentScreen,
                          "Visual Studio Code",
                          &lv_font_montserrat_24);

    /* Knob Text */
    VSC_spKnobText = GUI_spKnobTextCreate(spParentScreen,
                                          VSC_KNOB_EMPTY_TEXT,
                                          lv_color_hex(0xE9B316),
                                          &fa_angles_34pxl_collection);
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

void VSC_vRotaryCallBackFunction(bool boClockwise, bool boModeButtonPressed)
{
    VSC__u16ScreenTimer = timer_read();
    const char * cp_text = NULL;
    uint16_t u16_keycode = 0;
    uint8_t u8_repeat = 0;

    switch(VSC__enKNOB_State)
    {
        case enKnobUpDown_State :
            cp_text = (boModeButtonPressed == false) ? VSC_KNOB_2X_UP_DOWN_TEXT : VSC_KNOB_UP_DOWN_TEXT;
            u16_keycode = boClockwise ? KC_UP : KC_DOWN;
            break;

        case enKnobLeftRight_State :
            cp_text = (boModeButtonPressed == false) ? VSC_KNOB_2X_LEFT_RIGHT_TEXT : VSC_KNOB_LEFT_RIGHT_TEXT;
            u16_keycode = boClockwise ? KC_RIGHT : KC_LEFT;
            break;
        break;
    }
    lv_label_set_text(VSC_spKnobText, cp_text);
    u8_repeat = (boModeButtonPressed == false) ? 2 : 1;
    do
    {
        tap_code(u16_keycode);
    }while(u8_repeat--);
}

void VSC_vRotaryButtonPressedCallBackFunction(void)
{
    switch(VSC__enKNOB_State)
    {
        case enKnobUpDown_State :
            VSC__enKNOB_State = enKnobLeftRight_State;
        break;

        case enKnobLeftRight_State :
            VSC__enKNOB_State = enKnobUpDown_State;
        break;
    }
}

void VSC_vHouseKeeping(void)
{
    if(VSC__u16ScreenTimer && timer_elapsed(VSC__u16ScreenTimer) > 3000)
    {
        VSC__u16ScreenTimer = 0;
        lv_label_set_text(VSC_spKnobText, VSC_KNOB_EMPTY_TEXT);
    }
}
