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
    GUI_tsBtnLocation stBtnLoc;
    stBtnLoc.m_u8BtnSizeX = NUM_PAD_BUTTON_SIZE_X;
    stBtnLoc.m_u8BtnSizeY = NUM_PAD_BUTTON_SIZE_Y;
    /*************** FIRST ROW *******************/
    //BackSpace Button
    stBtnLoc.m_u8BtnLocX = NUM_PAD_X_OFFSET_FROM_LEFT;
    stBtnLoc.m_u8BtnLocY = NUM_PAD_Y_OFFSET_FROM_TOP;
    btn_bks = KPAD__spButtonCreate(spParentScreen, LV_SYMBOL_BACKSPACE, &stBtnLoc);

    //Divide Button
    stBtnLoc.m_u8BtnLocX = (NUM_PAD_X_OFFSET_FROM_LEFT + NUM_PAD_BUTTON_SPACE_X + NUM_PAD_BUTTON_SIZE_X);
    stBtnLoc.m_u8BtnLocY = (NUM_PAD_Y_OFFSET_FROM_TOP);
    btn_div = KPAD__spButtonCreate(spParentScreen, "/", &stBtnLoc);

    //Multiply Button
    stBtnLoc.m_u8BtnLocX = (NUM_PAD_X_OFFSET_FROM_LEFT + NUM_PAD_BUTTON_SPACE_X * 2 + NUM_PAD_BUTTON_SIZE_X * 2);
    stBtnLoc.m_u8BtnLocY = (NUM_PAD_Y_OFFSET_FROM_TOP);
    btn_mul = KPAD__spButtonCreate(spParentScreen, "*", &stBtnLoc);

    //Minus Button
    stBtnLoc.m_u8BtnLocX = (NUM_PAD_X_OFFSET_FROM_LEFT + NUM_PAD_BUTTON_SPACE_X * 3 + NUM_PAD_BUTTON_SIZE_X * 3);
    stBtnLoc.m_u8BtnLocY = (NUM_PAD_Y_OFFSET_FROM_TOP);
    btn_min = KPAD__spButtonCreate(spParentScreen, "-", &stBtnLoc);

    /*************** SECOND ROW *******************/
    //7 Button
    stBtnLoc.m_u8BtnLocX = (NUM_PAD_X_OFFSET_FROM_LEFT);
    stBtnLoc.m_u8BtnLocY = (NUM_PAD_Y_OFFSET_FROM_TOP + NUM_PAD_BUTTON_SPACE_Y + NUM_PAD_BUTTON_SIZE_Y);
    btn_7 = KPAD__spButtonCreate(spParentScreen, "7  A", &stBtnLoc);

    //8 Button
    stBtnLoc.m_u8BtnLocX = (NUM_PAD_X_OFFSET_FROM_LEFT + NUM_PAD_BUTTON_SPACE_X + NUM_PAD_BUTTON_SIZE_X);
    stBtnLoc.m_u8BtnLocY = (NUM_PAD_Y_OFFSET_FROM_TOP + NUM_PAD_BUTTON_SPACE_Y + NUM_PAD_BUTTON_SIZE_Y);
    btn_8 = KPAD__spButtonCreate(spParentScreen, "8  B", &stBtnLoc);

    //9 Button
    stBtnLoc.m_u8BtnLocX = (NUM_PAD_X_OFFSET_FROM_LEFT + NUM_PAD_BUTTON_SPACE_X * 2 + NUM_PAD_BUTTON_SIZE_X * 2);
    stBtnLoc.m_u8BtnLocY = (NUM_PAD_Y_OFFSET_FROM_TOP + NUM_PAD_BUTTON_SPACE_Y + NUM_PAD_BUTTON_SIZE_Y);
    btn_9 = KPAD__spButtonCreate(spParentScreen, "9  C", &stBtnLoc);

    //+ Button
    stBtnLoc.m_u8BtnSizeX = NUM_PAD_BUTTON_SIZE_X;
    stBtnLoc.m_u8BtnSizeY = NUM_PAD_BUTTON_SIZE_Y * 2 + NUM_PAD_BUTTON_SPACE_Y;
    stBtnLoc.m_u8BtnLocX = (NUM_PAD_X_OFFSET_FROM_LEFT + NUM_PAD_BUTTON_SPACE_X * 3 + NUM_PAD_BUTTON_SIZE_X * 3);
    stBtnLoc.m_u8BtnLocY = (NUM_PAD_Y_OFFSET_FROM_TOP + NUM_PAD_BUTTON_SPACE_Y + NUM_PAD_BUTTON_SIZE_Y);
    btn_plus = KPAD__spButtonCreate(spParentScreen, "+", &stBtnLoc);

    /*************** THRID ROW *******************/
    //4 Button
    stBtnLoc.m_u8BtnSizeX = NUM_PAD_BUTTON_SIZE_X;
    stBtnLoc.m_u8BtnSizeY = NUM_PAD_BUTTON_SIZE_Y;
    stBtnLoc.m_u8BtnLocX = (NUM_PAD_X_OFFSET_FROM_LEFT);
    stBtnLoc.m_u8BtnLocY = (NUM_PAD_Y_OFFSET_FROM_TOP + NUM_PAD_BUTTON_SPACE_Y * 2 + NUM_PAD_BUTTON_SIZE_Y * 2);
    btn_4 = KPAD__spButtonCreate(spParentScreen, "4  D", &stBtnLoc);

    //5 Button
    stBtnLoc.m_u8BtnLocX = (NUM_PAD_X_OFFSET_FROM_LEFT + NUM_PAD_BUTTON_SPACE_X + NUM_PAD_BUTTON_SIZE_X);
    stBtnLoc.m_u8BtnLocY = (NUM_PAD_Y_OFFSET_FROM_TOP + NUM_PAD_BUTTON_SPACE_Y * 2 + NUM_PAD_BUTTON_SIZE_Y * 2);
    btn_5 = KPAD__spButtonCreate(spParentScreen, "5  E", &stBtnLoc);

    //6 Button
    stBtnLoc.m_u8BtnLocX = (NUM_PAD_X_OFFSET_FROM_LEFT + NUM_PAD_BUTTON_SPACE_X * 2 + NUM_PAD_BUTTON_SIZE_X * 2);
    stBtnLoc.m_u8BtnLocY = (NUM_PAD_Y_OFFSET_FROM_TOP + NUM_PAD_BUTTON_SPACE_Y * 2 + NUM_PAD_BUTTON_SIZE_Y * 2);
    btn_6 = KPAD__spButtonCreate(spParentScreen, "6  F", &stBtnLoc);

    /*************** FOURTH ROW *******************/
    //1 Button
    stBtnLoc.m_u8BtnLocX = (NUM_PAD_X_OFFSET_FROM_LEFT);
    stBtnLoc.m_u8BtnLocY = (NUM_PAD_Y_OFFSET_FROM_TOP + NUM_PAD_BUTTON_SPACE_Y * 3 + NUM_PAD_BUTTON_SIZE_Y * 3);
    btn_1 = KPAD__spButtonCreate(spParentScreen, "1", &stBtnLoc);

    //2 Button
    stBtnLoc.m_u8BtnLocX = (NUM_PAD_X_OFFSET_FROM_LEFT + NUM_PAD_BUTTON_SPACE_X + NUM_PAD_BUTTON_SIZE_X);
    stBtnLoc.m_u8BtnLocY = (NUM_PAD_Y_OFFSET_FROM_TOP + NUM_PAD_BUTTON_SPACE_Y * 3 + NUM_PAD_BUTTON_SIZE_Y * 3);
    btn_2 = KPAD__spButtonCreate(spParentScreen, "2", &stBtnLoc);

    //3 Button
    stBtnLoc.m_u8BtnLocX = (NUM_PAD_X_OFFSET_FROM_LEFT + NUM_PAD_BUTTON_SPACE_X * 2 + NUM_PAD_BUTTON_SIZE_X * 2);
    stBtnLoc.m_u8BtnLocY = (NUM_PAD_Y_OFFSET_FROM_TOP + NUM_PAD_BUTTON_SPACE_Y * 3 + NUM_PAD_BUTTON_SIZE_Y * 3);
    btn_3 = KPAD__spButtonCreate(spParentScreen, "3", &stBtnLoc);

    //Enter Button
    stBtnLoc.m_u8BtnSizeX = NUM_PAD_BUTTON_SIZE_X;
    stBtnLoc.m_u8BtnSizeY = NUM_PAD_BUTTON_SIZE_Y * 2 + NUM_PAD_BUTTON_SPACE_Y;
    stBtnLoc.m_u8BtnLocX = (NUM_PAD_X_OFFSET_FROM_LEFT + NUM_PAD_BUTTON_SPACE_X * 3 + NUM_PAD_BUTTON_SIZE_X * 3);
    stBtnLoc.m_u8BtnLocY = (NUM_PAD_Y_OFFSET_FROM_TOP + NUM_PAD_BUTTON_SPACE_Y * 3 + NUM_PAD_BUTTON_SIZE_Y * 3);
    btn_ent = KPAD__spButtonCreate(spParentScreen, LV_SYMBOL_NEW_LINE, &stBtnLoc);

    /*************** FIFTH ROW *******************/
    //ZERO Button
    stBtnLoc.m_u8BtnSizeX = NUM_PAD_BUTTON_SIZE_X * 2 + NUM_PAD_BUTTON_SPACE_X;
    stBtnLoc.m_u8BtnSizeY = NUM_PAD_BUTTON_SIZE_Y;
    stBtnLoc.m_u8BtnLocX = (NUM_PAD_X_OFFSET_FROM_LEFT);
    stBtnLoc.m_u8BtnLocY = (NUM_PAD_Y_OFFSET_FROM_TOP + NUM_PAD_BUTTON_SPACE_Y * 4 + NUM_PAD_BUTTON_SIZE_Y * 4);
    btn_0 = KPAD__spButtonCreate(spParentScreen, "0", &stBtnLoc);

    //dot Button
    stBtnLoc.m_u8BtnSizeX = NUM_PAD_BUTTON_SIZE_X;
    stBtnLoc.m_u8BtnSizeY = NUM_PAD_BUTTON_SIZE_Y;
    stBtnLoc.m_u8BtnLocX = (NUM_PAD_X_OFFSET_FROM_LEFT + NUM_PAD_BUTTON_SPACE_X * 2+ NUM_PAD_BUTTON_SIZE_X * 2);
    stBtnLoc.m_u8BtnLocY = (NUM_PAD_Y_OFFSET_FROM_TOP + NUM_PAD_BUTTON_SPACE_Y * 4 + NUM_PAD_BUTTON_SIZE_Y * 4);
    btn_dot = KPAD__spButtonCreate(spParentScreen, ".", &stBtnLoc);

    /*************** LVGL Arc GUI *******************/
    KPAD__vArcCreate(spParentScreen, 110, 200, 20);
}

static void KPAD__vLayerGUIStateChange(uint16_t u16KeyCode, lv_obj_state_fptr pfnStateCb)
{
    switch(u16KeyCode)
    {
        case KC_BACKSPACE:
            pfnStateCb(btn_bks);
        break;
        case KC_KP_SLASH:
            pfnStateCb(btn_div);
        break;
        case KC_KP_ASTERISK:
            pfnStateCb(btn_mul);
        break;
        case KC_KP_MINUS:
            pfnStateCb(btn_min);
        break;
        case TD(NUM_KEY_7_AND_A):
            pfnStateCb(btn_7);
        break;
        case TD(NUM_KEY_8_AND_B):
            pfnStateCb(btn_8);
        break;
        case TD(NUM_KEY_9_AND_C):
            pfnStateCb(btn_9);
        break;
        case KC_KP_PLUS:
            pfnStateCb(btn_plus);
        break;
        case TD(NUM_KEY_4_AND_D):
            pfnStateCb(btn_4);
        break;
        case TD(NUM_KEY_5_AND_E):
            pfnStateCb(btn_5);
        break;
        case TD(NUM_KEY_6_AND_F):
            pfnStateCb(btn_6);
        break;
        case KC_KP_1:
            pfnStateCb(btn_1);
        break;
        case KC_KP_2:
            pfnStateCb(btn_2);
        break;
        case KC_KP_3:
            pfnStateCb(btn_3);
        break;
        case KC_KP_ENTER:
            pfnStateCb(btn_ent);
        break;
        case KC_KP_0:
            pfnStateCb(btn_0);
        break;
        case KC_KP_DOT:
            pfnStateCb(btn_dot);
        break;
        default:
        break;
    }
}

static inline void KPAD__vButtonPress(lv_obj_t * spButton)
{
    lv_obj_add_state(spButton, LV_STATE_PRESSED);
}

static inline void KPAD__vButtonRelease(lv_obj_t * spButton)
{
    lv_obj_clear_state(spButton, LV_STATE_PRESSED);
}

/* to change the button pressed animation for the keypad screen */
void KPAD_vKeyPressedCallBackFunction(uint16_t u16KeyCode)
{
    KPAD__vLayerGUIStateChange(u16KeyCode, KPAD__vButtonPress);
}

/* to change the button released animation for the keypad screen */
void KPAD_vKeyReleasedCallBackFunction(uint16_t u16KeyCode)
{
    KPAD__vLayerGUIStateChange(u16KeyCode, KPAD__vButtonRelease);
}
