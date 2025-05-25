#define __KEYPAD_SCREEN_C
#include "keypad_screen.h"

int8_t KPAD_i8SoundVolume = -1;

#define KPAD__nButtonColor lv_palette_darken(LV_PALETTE_AMBER, 3)
#define KPAD__nArcColor  lv_palette_darken(LV_PALETTE_AMBER, 3)

static lv_obj_t * KPAD__spButtonCreate(lv_obj_t* spParentScreen, const char * text, GUI_tsBtnLocation * stBtnLoc )
{
    lv_obj_t *btn = lv_btn_create(spParentScreen);
    lv_obj_set_size(btn, stBtnLoc->m_u8BtnSizeX, stBtnLoc->m_u8BtnSizeY);
    lv_obj_align(btn, BUTTON_ALIGN_STYLE, stBtnLoc->m_u8BtnLocX, stBtnLoc->m_u8BtnLocY);

    /* Keypad Button Color */
    lv_obj_set_style_bg_color(btn, KPAD__nButtonColor, 0);

    lv_obj_t* label_btn = lv_label_create(btn);
    lv_label_set_text(label_btn, text);
    lv_obj_center(label_btn);

    /* Keypad Text Color */
    lv_obj_set_style_text_color(label_btn, lv_color_hex(0xffffff), 0);
    return btn;
}

static void KPAD__vArcCreate(lv_obj_t * spParentScreen, uint8_t u8Size, uint8_t u8LocX, uint8_t u8LocY)
{
    KPAD_spVolumeObj = lv_arc_create(spParentScreen);
    lv_obj_set_size(KPAD_spVolumeObj, u8Size, u8Size);
    lv_obj_align(KPAD_spVolumeObj, LV_ALIGN_DEFAULT, u8LocX, u8LocY);
    lv_obj_set_style_arc_color(KPAD_spVolumeObj, KPAD__nArcColor, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(KPAD_spVolumeObj, KPAD__nArcColor, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(KPAD_spVolumeObj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(KPAD_spVolumeObj, 10, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_arc_set_value(KPAD_spVolumeObj, KPAD_i8SoundVolume);
    lv_arc_set_range(KPAD_spVolumeObj, 0, 100);

    /* Volume Value Label */
    KPAD_spVolumeLbl = lv_label_create(spParentScreen);
    lv_label_set_text(KPAD_spVolumeLbl, "000");
    lv_obj_set_style_text_font(KPAD_spVolumeLbl, &lv_font_montserrat_24, LV_PART_MAIN);
    lv_obj_align(KPAD_spVolumeLbl,LV_ALIGN_DEFAULT, u8LocX + 30, u8LocY + 40);

    /* Volume Text */
    KPAD_spVolumeTxt = lv_label_create(spParentScreen);
    lv_label_set_text(KPAD_spVolumeTxt, "Volume");
    lv_obj_set_style_text_font(KPAD_spVolumeTxt, &lv_font_montserrat_24, LV_PART_MAIN);
    lv_obj_align(KPAD_spVolumeTxt,LV_ALIGN_DEFAULT, u8LocX + 10, u8LocY + 110);
}

void KPAD_vScreenCreate(lv_obj_t *spParentScreen)
{
    uint8_t u8RowCnt = 4;
    uint8_t u8ColCnt = 5;
    GUI_tsBtnLocation stBtnLoc;
    for(uint8_t u8Col = 0; u8Col < u8ColCnt; u8Col++)
    {
        for(uint8_t u8Row = 0; u8Row < u8RowCnt; u8Row++)
        {
            uint8_t u8Index = u8Row + (u8RowCnt * u8Col);
            if(KPAD_staBtnInfo[u8Index].m_boSkipBtn == false)
            {
                stBtnLoc.m_u8BtnSizeX = (KPAD_staBtnInfo[u8Index].m_boBtnXDouble == true ) ? ((KPAD_BUTTON_SIZE_X * 2) + KPAD_BUTTON_SPACE_X) : KPAD_BUTTON_SIZE_X;
                stBtnLoc.m_u8BtnSizeY = (KPAD_staBtnInfo[u8Index].m_boBtnYDouble == true ) ? ((KPAD_BUTTON_SIZE_Y * 2) + KPAD_BUTTON_SPACE_Y) : KPAD_BUTTON_SIZE_Y;
                stBtnLoc.m_u8BtnLocX = KPAD_X_OFFSET_FROM_LEFT + (u8Row * KPAD_BUTTON_SPACE_X) + (u8Row * KPAD_BUTTON_SIZE_X);
                stBtnLoc.m_u8BtnLocY = KPAD_Y_OFFSET_FROM_TOP + (u8Col * KPAD_BUTTON_SPACE_Y) + (u8Col * KPAD_BUTTON_SIZE_Y);
                KPAD_staBtnInfo[u8Index].m_spBtn = KPAD__spButtonCreate(spParentScreen, KPAD_staBtnInfo[u8Index].m_cpBtnName, &stBtnLoc);
            }
        }
    }
    /*************** LVGL Arc GUI *******************/
    KPAD__vArcCreate(spParentScreen, 110, 200, 20);
}

static void KPAD__vLayerGUIStateChange(uint16_t u16KeyCode, lv_obj_state_fptr pfnStateCb)
{
    for(uint8_t u8Idx = 0; u8Idx < 20; u8Idx++)
    {
        if(KPAD_staBtnInfo[u8Idx].m_u16KeyCode == u16KeyCode)
        {
            pfnStateCb(KPAD_staBtnInfo[u8Idx].m_spBtn);
        }
    }
}

/* to change the button pressed animation for the keypad screen */
void KPAD_vKeyPressedCallBackFunction(uint16_t u16KeyCode)
{
    KPAD__vLayerGUIStateChange(u16KeyCode, GUI_vButtonPress);
}

/* to change the button released animation for the keypad screen */
void KPAD_vKeyReleasedCallBackFunction(uint16_t u16KeyCode)
{
    KPAD__vLayerGUIStateChange(u16KeyCode, GUI_vButtonRelease);
}
