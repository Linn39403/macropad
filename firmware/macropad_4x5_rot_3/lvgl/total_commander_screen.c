#define __TOTAL_COMMANDER_SCREEN_C
#include "total_commander_screen.h"
#include "print.h"

static lv_obj_t * lv_tc_button_create(lv_obj_t* parent_screen, const char * text, struct lv_tc_btn_location * btn_loc_st )
{
    lv_obj_t *btn = lv_btn_create(parent_screen);
    lv_obj_set_size(btn, btn_loc_st->btn_size_x, btn_loc_st->btn_size_y);
    lv_obj_align(btn, TC_BUTTON_ALIGN_STYLE, btn_loc_st->btn_align_x, btn_loc_st->btn_align_y);

    /* Keypad Button Color */
    lv_obj_set_style_bg_color(btn, lv_color_hex(0x4CCF35), 0);

    lv_obj_t* label_btn = lv_label_create(btn);
    lv_label_set_text(label_btn, text);
    lv_obj_center(label_btn);

    /* Keypad Text Color */
    lv_obj_set_style_text_color(label_btn, lv_color_hex(0xffffff), 0);
    return btn;
}

void lv_tc_screen_create(lv_obj_t * parent_screen)
{
    uint16_t row_cnt = 4; /* 4 buttons per row */
    uint16_t col_cnt = TC_BUTTON_COUNT / row_cnt;

    /* 4 buttons per role, 5 rows in total */
    struct lv_tc_btn_location btn_loc_st;
    btn_loc_st.btn_size_x = TC_BUTTON_SIZE_X;
    btn_loc_st.btn_size_y = TC_BUTTON_SIZE_Y;

    for(uint16_t c = 0; c < col_cnt; c++)
    {
        for(uint16_t r = 0; r < row_cnt; r++)
        {
            btn_loc_st.btn_align_x = TC_X_OFFSET_FROM_LEFT + (r * TC_BUTTON_SPACE_X) + (r * TC_BUTTON_SIZE_X);
            btn_loc_st.btn_align_y = TC_Y_OFFSET_FROM_TOP + (c * TC_BUTTON_SPACE_Y) + (c * TC_BUTTON_SIZE_Y);
            btn_tc_array[r+(row_cnt*c)].btn = lv_tc_button_create(
                                              parent_screen,
                                              btn_tc_array[r+(row_cnt*c)].btn_name ,
                                              &btn_loc_st);
        }
    }
}

static void tc_layer_lv_state_change(uint16_t keycode, lv_obj_state_fptr state_callback)
{
    switch(keycode)
    {
        case S(KC_F6):
            state_callback(btn_tc_array[TC_BUTTON_RENAME].btn);
        break;
        case S(KC_F10):
            state_callback(btn_tc_array[TC_BUTTON_PROPERTIES].btn);
        break;
        case S(KC_F4):
            state_callback(btn_tc_array[TC_BUTTON_NEW_TXT_FILE].btn);
        break;
        case LCTL(KC_BSLS):
            state_callback(btn_tc_array[TC_BUTTON_JUMP_TO_ROOT].btn);
        break;
        case LCTL(KC_UP):
            state_callback(btn_tc_array[TC_BUTTON_NEW_TAB].btn);
        break;
        case LCTL(KC_W):
            state_callback(btn_tc_array[TC_BUTTON_CLOSE_TAB].btn);
        break;
        case LCTL(KC_TAB):
            state_callback(btn_tc_array[TC_BUTTON_TAB_CHANGE].btn);
        break;
        case KC_TAB:
            state_callback(btn_tc_array[TC_BUTTON_SWITCH_TAB].btn);
        break;
        case LCTL(KC_F3):
            state_callback(btn_tc_array[TC_BUTTON_SORT_BY_NAME].btn);
        break;
        case LCTL(KC_F4):
            state_callback(btn_tc_array[TC_BUTTON_SORT_BY_EXT].btn);
        break;
        case LCTL(KC_F5):
            state_callback(btn_tc_array[TC_BUTTON_SORT_BY_TIME].btn);
        break;
        case LCTL(KC_F6):
            state_callback(btn_tc_array[TC_BUTTON_SORT_BY_SIZE].btn);
        break;
        case KC_BACKSPACE:
            state_callback(btn_tc_array[TC_BUTTON_BACK].btn);
        break;
        case KC_NO:
            /* Do nothing because these keys are not used*/
        break;
        default:
        break;
    }
}

static inline void tc_button_press(lv_obj_t * button)
{
    lv_obj_add_state(button, LV_STATE_PRESSED);
}

static inline void tc_button_release(lv_obj_t * button)
{
    lv_obj_clear_state(button, LV_STATE_PRESSED);
}

/* to change the button pressed animation for the keypad screen */
void tc_layer_function_key_pressed(uint16_t keycode)
{
    uprintf("tc key press: %x\n",keycode);
    tc_layer_lv_state_change(keycode, tc_button_press);
}

/* to change the button released animation for the keypad screen */
void tc_layer_function_key_released(uint16_t keycode)
{
    uprintf("tc key release: %x\n",keycode);
    tc_layer_lv_state_change(keycode, tc_button_release);
}


