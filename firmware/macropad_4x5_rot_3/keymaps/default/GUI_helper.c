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
                              const lv_font_t * fontName,
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
    lv_obj_set_style_text_font(spBtnLabel , fontName, LV_PART_MAIN);
    lv_obj_center(spBtnLabel);

    /* Keypad Text Color */
    lv_obj_set_style_text_color(spBtnLabel, stTextColor, 0);
    return spBtn;
}

lv_obj_t * GUI_spLayerNameCreate(lv_obj_t* spParentScreen,
                                 const char * pcText,
                                 const lv_font_t * fontName)
{
    lv_obj_t * spLabel = lv_label_create(spParentScreen);
    lv_label_set_text(spLabel, pcText);
    lv_obj_set_style_text_font(spLabel, fontName, LV_PART_MAIN);
    lv_obj_align(spLabel,LV_ALIGN_BOTTOM_MID, 0, -10);
    lv_obj_set_style_text_align(spLabel,LV_ALIGN_CENTER, 0);
    lv_obj_update_layout(spLabel);
    return spLabel;
}

lv_obj_t * GUI_spKnobTextCreate(lv_obj_t* spParentScreen,
                                const char * pcText,
                                lv_color_t color,
                                const lv_font_t * fontName)
{
    lv_obj_t * spLabel = lv_label_create(spParentScreen);
    lv_label_set_text(spLabel, pcText);
    lv_obj_set_style_text_font(spLabel , fontName, LV_PART_MAIN);
    lv_obj_set_style_text_color(spLabel, color, 0);
    lv_obj_align(spLabel ,LV_ALIGN_BOTTOM_MID, 0, -40);
    lv_obj_set_style_text_align(spLabel ,LV_ALIGN_CENTER, 0);
    lv_obj_update_layout(spLabel);
    return spLabel;
}
