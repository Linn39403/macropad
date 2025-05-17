#include "GUI_helper.h"

void GUI_vButtonPress(lv_obj_t * spButton)
{
    lv_obj_add_state(spButton, LV_STATE_PRESSED);
}

void GUI_vButtonRelease(lv_obj_t * spButton)
{
    lv_obj_clear_state(spButton, LV_STATE_PRESSED);
}

lv_obj_t * GUI_spButtonCreate(lv_obj_t* spParentScreen,
                              const char * pcText,
                              lv_color_t stButtonColor,
                              lv_color_t stTextColor,
                              GUI_tsBtnLocation * spBtnInfo )
{
    lv_obj_t *spBtn = lv_btn_create(spParentScreen);
    lv_obj_set_size(spBtn, spBtnInfo->m_u8BtnSizeX, spBtnInfo->m_u8BtnSizeY);
    lv_obj_align(spBtn, LV_ALIGN_DEFAULT, spBtnInfo->m_u8BtnLocX, spBtnInfo->m_u8BtnLocY);

    /* Keypad Button Color */
    lv_obj_set_style_bg_color(spBtn, stButtonColor, 0);

    lv_obj_t* spBtnLabel = lv_label_create(spBtn);
    lv_label_set_text(spBtnLabel, pcText);
    lv_obj_center(spBtnLabel);

    /* Keypad Text Color */
    lv_obj_set_style_text_color(spBtnLabel, stTextColor, 0);
    return spBtn;
}
