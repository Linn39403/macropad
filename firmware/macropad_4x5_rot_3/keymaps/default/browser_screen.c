#define __BROWSER_SCREEN_C
#include "browser_screen.h"
#include "print.h"

static lv_obj_t* BROWSER_spKnobText;
static uint16_t BROWSER__u16ScreenTimer = 0;
#define BROWSER_KNOB_UP_DOWN_TEXT        FA_ROTATE_LEFT_CODE "  " FA_ANGLE_DOWN_CODE         "                " FA_ROTATE_RIGHT_CODE "  " FA_ANGLE_UP_CODE
#define BROWSER_KNOB_2X_UP_DOWN_TEXT     FA_ROTATE_LEFT_CODE "  " FA_ANGLE_DOUBLE_DOWN_CODE  "                " FA_ROTATE_RIGHT_CODE "  " FA_ANGLE_DOUBLE_UP_CODE
#define BROWSER_KNOB_VOL_UP_DOWN_TEXT    FA_ROTATE_LEFT_CODE "  " FA_VOLUME_DOWN_CODE        "                " FA_ROTATE_RIGHT_CODE "  " FA_VOLUME_UP_CODE
#define BROWSER_KNOB_MUTE_TEXT           FA_VOLUME_MUTE_CODE
#define BROWSER_KNOB_EMPTY_TEXT          "                              "

enum BROWSER__enKNOB_State
{
    enKnobUpDown_State = 0,
    enKnobVolUpDown_State
};
enum BROWSER__enKNOB_State BROWSER__enKNOB_State = enKnobUpDown_State;

static lv_obj_t * BROWSER__spButtonCreate(lv_obj_t* spParentScreen,
                                          const char * pcText,
                                          const lv_font_t * font_name,
                                          GUI_tsBtnLocation * spBtnInfo )
{
    return GUI_spButtonCreate(spParentScreen,
                              pcText,
                              font_name,
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
    lv_label_set_text(BROWSER_spKnobText, BROWSER_KNOB_EMPTY_TEXT);
    lv_obj_set_style_text_font(BROWSER_spKnobText , &fa_angles_34pxl_collection, LV_PART_MAIN);
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

void BROWSER_vRotaryCallBackFunction(bool boClockwise, bool boModeButtonPressed)
{
    BROWSER__u16ScreenTimer = timer_read();
    const char * cp_text = NULL;
    uint16_t u16_keycode = 0;
    uint8_t u8_repeat = 1;

    switch(BROWSER__enKNOB_State)
    {
        case enKnobUpDown_State:
            cp_text = (boModeButtonPressed == false) ? BROWSER_KNOB_2X_UP_DOWN_TEXT : BROWSER_KNOB_UP_DOWN_TEXT;
            u16_keycode = boClockwise ? KC_MS_WH_UP : KC_MS_WH_DOWN;
            u8_repeat = (boModeButtonPressed == false) ? 2 : 1;
        break;

        case enKnobVolUpDown_State:
            if(boModeButtonPressed == false){
                cp_text = BROWSER_KNOB_MUTE_TEXT;
                u16_keycode = KC_VOLD;
                u8_repeat = 50;
            }else{
                cp_text = BROWSER_KNOB_VOL_UP_DOWN_TEXT;
                u16_keycode = boClockwise ? KC_VOLU : KC_VOLD;
                u8_repeat = (boModeButtonPressed == false) ? 2 : 1;
            }
        break;
    }
    lv_label_set_text(BROWSER_spKnobText, cp_text);
    do
    {
        tap_code(u16_keycode);
    }while(u8_repeat--);
}

void BROWSER_vRotaryButtonPressedCallBackFunction(void)
{
    switch(BROWSER__enKNOB_State)
    {
        case enKnobUpDown_State:
            BROWSER__enKNOB_State = enKnobVolUpDown_State;
        break;

        case enKnobVolUpDown_State:
            BROWSER__enKNOB_State = enKnobUpDown_State;
        break;
    }
}

void BROWSER_vHouseKeeping(void)
{
    if(BROWSER__u16ScreenTimer && timer_elapsed(BROWSER__u16ScreenTimer) > 3000)
    {
        BROWSER__u16ScreenTimer = 0;
        lv_label_set_text(BROWSER_spKnobText, BROWSER_KNOB_EMPTY_TEXT);
    }
}
