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
    lv_obj_t* VSC_spVolumeTxt = lv_label_create(spParentScreen);
    lv_label_set_text(VSC_spVolumeTxt , "Visual Studio Code");
    lv_obj_set_style_text_font(VSC_spVolumeTxt , &lv_font_montserrat_24, LV_PART_MAIN);
    lv_obj_align(VSC_spVolumeTxt ,LV_ALIGN_BOTTOM_MID, 0, -10);
    lv_obj_set_style_text_align(VSC_spVolumeTxt ,LV_ALIGN_CENTER, 0);
    lv_obj_update_layout(VSC_spVolumeTxt);

    /* Knob Text */
    VSC_spKnobText = lv_label_create(spParentScreen);
    lv_label_set_text(VSC_spKnobText, VSC_KNOB_EMPTY_TEXT);
    lv_obj_set_style_text_font(VSC_spKnobText , &fa_angles_34pxl_collection, LV_PART_MAIN);
    lv_obj_set_style_text_color(VSC_spKnobText, lv_color_hex(0xE9B316), 0);
    lv_obj_align(VSC_spKnobText ,LV_ALIGN_BOTTOM_MID, 0, -40);
    lv_obj_set_style_text_align(VSC_spKnobText ,LV_ALIGN_CENTER, 0);
    lv_obj_update_layout(VSC_spKnobText);
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
    if(boModeButtonPressed == false)
    {
        /* Button Pressed */
        VSC__u16ScreenTimer = timer_read();
        switch(VSC__enKNOB_State)
        {
            case enKnobUpDown_State :
                lv_label_set_text(VSC_spKnobText, VSC_KNOB_2X_UP_DOWN_TEXT );
                if(boClockwise == true){
                    tap_code(KC_UP);
                    tap_code(KC_UP);
                }
                else{
                    tap_code(KC_DOWN);
                    tap_code(KC_DOWN);
                }
            break;

            case enKnobLeftRight_State :
                lv_label_set_text(VSC_spKnobText, VSC_KNOB_2X_LEFT_RIGHT_TEXT );
                if(boClockwise == true){
                    tap_code(KC_RIGHT);
                    tap_code(KC_RIGHT);
                }
                else{
                    tap_code(KC_LEFT);
                    tap_code(KC_LEFT);
                }
            break;
        }
    }
    else
    {
        /* Button Not Pressed */
        VSC__u16ScreenTimer = timer_read();
        switch(VSC__enKNOB_State)
        {
            case enKnobUpDown_State :
                lv_label_set_text(VSC_spKnobText, VSC_KNOB_UP_DOWN_TEXT );
                if(boClockwise == true)
                    tap_code(KC_UP);
                else
                    tap_code(KC_DOWN);
            break;

            case enKnobLeftRight_State :
                lv_label_set_text(VSC_spKnobText, VSC_KNOB_LEFT_RIGHT_TEXT );
                if(boClockwise == true)
                    tap_code(KC_RIGHT);
                else
                    tap_code(KC_LEFT);
            break;
        }
    }
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
