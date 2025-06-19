#define __NUMPAD_SCREEN_C
#include "numpad_screen.h"

int8_t NUMPAD_i8SoundVolume = -1;

#define NUMPAD__nButtonColor lv_palette_darken(LV_PALETTE_AMBER, 3)
#define NUMPAD__nArcColor  lv_palette_darken(LV_PALETTE_AMBER, 3)

static lv_obj_t * NUMPAD__spButtonCreate(lv_obj_t* spParentScreen,
                                         const char * text,
                                         const lv_font_t * font_name,
                                         GUI_tsBtnLocation * stBtnLoc )
{
    lv_obj_t *btn = lv_btn_create(spParentScreen);
    lv_obj_set_size(btn, stBtnLoc->m_u8BtnSizeX, stBtnLoc->m_u8BtnSizeY);
    lv_obj_align(btn, BUTTON_ALIGN_STYLE, stBtnLoc->m_u8BtnLocX, stBtnLoc->m_u8BtnLocY);

    /* Keypad Button Color */
    lv_obj_set_style_bg_color(btn, NUMPAD__nButtonColor, 0);

    lv_obj_t* label_btn = lv_label_create(btn);
    lv_label_set_text(label_btn, text);
    lv_obj_center(label_btn);

    /* Keypad Text Color */
    lv_obj_set_style_text_color(label_btn, lv_color_hex(0xffffff), 0);
    return btn;
}

static void NUMPAD__vArcCreate(lv_obj_t * spParentScreen, uint8_t u8Size, uint8_t u8LocX, uint8_t u8LocY)
{
    NUMPAD_spVolumeObj = lv_arc_create(spParentScreen);
    lv_obj_set_size(NUMPAD_spVolumeObj, u8Size, u8Size);
    lv_obj_align(NUMPAD_spVolumeObj, LV_ALIGN_DEFAULT, u8LocX, u8LocY);
    lv_obj_set_style_arc_color(NUMPAD_spVolumeObj, NUMPAD__nArcColor, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(NUMPAD_spVolumeObj, NUMPAD__nArcColor, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(NUMPAD_spVolumeObj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(NUMPAD_spVolumeObj, 10, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_arc_set_value(NUMPAD_spVolumeObj, NUMPAD_i8SoundVolume);
    lv_arc_set_range(NUMPAD_spVolumeObj, 0, 100);

    /* Volume Value Label */
    NUMPAD_spVolumeLbl = lv_label_create(spParentScreen);
    lv_label_set_text(NUMPAD_spVolumeLbl, "000");
    lv_obj_set_style_text_font(NUMPAD_spVolumeLbl, &lv_font_montserrat_24, LV_PART_MAIN);
    lv_obj_align(NUMPAD_spVolumeLbl,LV_ALIGN_DEFAULT, u8LocX + 30, u8LocY + 40);

    /* Volume Text */
    NUMPAD_spVolumeTxt = lv_label_create(spParentScreen);
    lv_label_set_text(NUMPAD_spVolumeTxt, "Volume");
    lv_obj_set_style_text_font(NUMPAD_spVolumeTxt, &lv_font_montserrat_24, LV_PART_MAIN);
    lv_obj_align(NUMPAD_spVolumeTxt,LV_ALIGN_DEFAULT, u8LocX + 10, u8LocY + 110);
}

void NUMPAD_vScreenCreate(lv_obj_t *spParentScreen)
{
    uint8_t u8RowCnt = 4;
    uint8_t u8ColCnt = 5;
    GUI_tsBtnLocation stBtnLoc;
    for(uint8_t u8Col = 0; u8Col < u8ColCnt; u8Col++)
    {
        for(uint8_t u8Row = 0; u8Row < u8RowCnt; u8Row++)
        {
            uint8_t u8Index = u8Row + (u8RowCnt * u8Col);
            if(NUMPAD_staBtnInfo[u8Index].m_boSkipBtn == false)
            {
                stBtnLoc.m_u8BtnSizeX = (NUMPAD_staBtnInfo[u8Index].m_boBtnXDouble == true ) ? ((NUMPAD_BUTTON_SIZE_X * 2) + NUMPAD_BUTTON_SPACE_X) : NUMPAD_BUTTON_SIZE_X;
                stBtnLoc.m_u8BtnSizeY = (NUMPAD_staBtnInfo[u8Index].m_boBtnYDouble == true ) ? ((NUMPAD_BUTTON_SIZE_Y * 2) + NUMPAD_BUTTON_SPACE_Y) : NUMPAD_BUTTON_SIZE_Y;
                stBtnLoc.m_u8BtnLocX = NUMPAD_X_OFFSET_FROM_LEFT + (u8Row * NUMPAD_BUTTON_SPACE_X) + (u8Row * NUMPAD_BUTTON_SIZE_X);
                stBtnLoc.m_u8BtnLocY = NUMPAD_Y_OFFSET_FROM_TOP + (u8Col * NUMPAD_BUTTON_SPACE_Y) + (u8Col * NUMPAD_BUTTON_SIZE_Y);
                NUMPAD_staBtnInfo[u8Index].m_spBtn = NUMPAD__spButtonCreate(spParentScreen,
                                                     NUMPAD_staBtnInfo[u8Index].m_cpBtnName,
                                                     NUMPAD_staBtnInfo[u8Index].m_spFontName,
                                                     &stBtnLoc);
            }
        }
    }
    /*************** LVGL Arc GUI *******************/
    NUMPAD__vArcCreate(spParentScreen, 110, 200, 20);

    /* Numpad Label */
    lv_obj_t* NUMPAD_spVolumeTxt = lv_label_create(spParentScreen);
    lv_label_set_text(NUMPAD_spVolumeTxt , "Numpad");
    lv_obj_set_style_text_font(NUMPAD_spVolumeTxt , &lv_font_montserrat_24, LV_PART_MAIN);
    lv_obj_align(NUMPAD_spVolumeTxt ,LV_ALIGN_BOTTOM_MID, 0, -10);
    lv_obj_set_style_text_align(NUMPAD_spVolumeTxt ,LV_ALIGN_CENTER, 0);
    lv_obj_update_layout(NUMPAD_spVolumeTxt);
}

static void NUMPAD__vLayerGUIStateChange(uint16_t u16KeyCode, lv_obj_state_fptr pfnStateCb)
{
    for(uint8_t u8Idx = 0; u8Idx < 20; u8Idx++)
    {
        if(NUMPAD_staBtnInfo[u8Idx].m_u16KeyCode == u16KeyCode)
        {
            pfnStateCb(NUMPAD_staBtnInfo[u8Idx].m_spBtn);
        }
    }
}

/* to change the button pressed animation for the keypad screen */
bool NUMPAD_boKeyPressedCallBackFunction(uint16_t u16KeyCode)
{
    NUMPAD__vLayerGUIStateChange(u16KeyCode, GUI_vButtonPress);
    return NUMPAD_LET_QMK_HANDLE_KEYBOARD_EVENT;
}

/* to change the button released animation for the keypad screen */
bool NUMPAD_boKeyReleasedCallBackFunction(uint16_t u16KeyCode)
{
    NUMPAD__vLayerGUIStateChange(u16KeyCode, GUI_vButtonRelease);
    return NUMPAD_LET_QMK_HANDLE_KEYBOARD_EVENT;
}

void NUMPAD_vRotaryCallBackFunction(bool boClockwise, bool boModeButtonPressed)
{
    if(boModeButtonPressed == false)
    {

    }
    else
    {
        if(boClockwise == true)
            tap_code(KC_VOLU);
        else
            tap_code(KC_VOLD);
    }
}

void NUMPAD_vRotaryButtonPressedCallBackFunction(void)
{

}

void NUMPAD_vHouseKeeping(void)
{

}
