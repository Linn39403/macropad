#define __KEYPAD_SCREEN_C
#include "keypad_screen.h"

static lv_obj_t * lv_keypad_button_create(lv_obj_t* parent_screen, const char * text, struct lv_keypad_btn_location * btn_loc_st )
{
    lv_obj_t *btn = lv_btn_create(parent_screen);
    lv_obj_set_size(btn, btn_loc_st->btn_size_x, btn_loc_st->btn_size_y);
    lv_obj_align(btn, BUTTON_ALIGN_STYLE, btn_loc_st->btn_align_x, btn_loc_st->btn_align_y);

    /* Keypad Button Color */
    lv_obj_set_style_bg_color(btn, lv_color_hex(0x3498db), 0);

    lv_obj_t* label_btn = lv_label_create(btn);
    lv_label_set_text(label_btn, text);
    lv_obj_center(label_btn);

    /* Keypad Text Color */
    lv_obj_set_style_text_color(label_btn, lv_color_hex(0xffffff), 0);
    return btn;
}

void lv_keypad_screen_create(lv_obj_t *parent_screen)
{
    struct lv_keypad_btn_location btn_loc_st;
    btn_loc_st.btn_size_x = NUM_PAD_BUTTON_SIZE_X;
    btn_loc_st.btn_size_y = NUM_PAD_BUTTON_SIZE_Y;
    /*************** FIRST ROW *******************/
    //BackSpace Button
    btn_loc_st.btn_align_x = NUM_PAD_X_OFFSET_FROM_LEFT;
    btn_loc_st.btn_align_y = NUM_PAD_Y_OFFSET_FROM_TOP;
    btn_bks = lv_keypad_button_create(parent_screen, LV_SYMBOL_BACKSPACE, &btn_loc_st);

    //Divide Button
    btn_loc_st.btn_align_x = (NUM_PAD_X_OFFSET_FROM_LEFT + NUM_PAD_BUTTON_SPACE_X + NUM_PAD_BUTTON_SIZE_X);
    btn_loc_st.btn_align_y = (NUM_PAD_Y_OFFSET_FROM_TOP);
    btn_div = lv_keypad_button_create(parent_screen, "/", &btn_loc_st);

    //Multiply Button
    btn_loc_st.btn_align_x = (NUM_PAD_X_OFFSET_FROM_LEFT + NUM_PAD_BUTTON_SPACE_X * 2 + NUM_PAD_BUTTON_SIZE_X * 2);
    btn_loc_st.btn_align_y = (NUM_PAD_Y_OFFSET_FROM_TOP);
    btn_mul = lv_keypad_button_create(parent_screen, "*", &btn_loc_st);

    //Minus Button
    btn_loc_st.btn_align_x = (NUM_PAD_X_OFFSET_FROM_LEFT + NUM_PAD_BUTTON_SPACE_X * 3 + NUM_PAD_BUTTON_SIZE_X * 3);
    btn_loc_st.btn_align_y = (NUM_PAD_Y_OFFSET_FROM_TOP);
    btn_min = lv_keypad_button_create(parent_screen, "-", &btn_loc_st);

    /*************** SECOND ROW *******************/
    //7 Button
    btn_loc_st.btn_align_x = (NUM_PAD_X_OFFSET_FROM_LEFT);
    btn_loc_st.btn_align_y = (NUM_PAD_Y_OFFSET_FROM_TOP + NUM_PAD_BUTTON_SPACE_Y + NUM_PAD_BUTTON_SIZE_Y);
    btn_7 = lv_keypad_button_create(parent_screen, "7  A", &btn_loc_st);

    //8 Button
    btn_loc_st.btn_align_x = (NUM_PAD_X_OFFSET_FROM_LEFT + NUM_PAD_BUTTON_SPACE_X + NUM_PAD_BUTTON_SIZE_X);
    btn_loc_st.btn_align_y = (NUM_PAD_Y_OFFSET_FROM_TOP + NUM_PAD_BUTTON_SPACE_Y + NUM_PAD_BUTTON_SIZE_Y);
    btn_8 = lv_keypad_button_create(parent_screen, "8  B", &btn_loc_st);

    //9 Button
    btn_loc_st.btn_align_x = (NUM_PAD_X_OFFSET_FROM_LEFT + NUM_PAD_BUTTON_SPACE_X * 2 + NUM_PAD_BUTTON_SIZE_X * 2);
    btn_loc_st.btn_align_y = (NUM_PAD_Y_OFFSET_FROM_TOP + NUM_PAD_BUTTON_SPACE_Y + NUM_PAD_BUTTON_SIZE_Y);
    btn_9 = lv_keypad_button_create(parent_screen, "9  C", &btn_loc_st);

    //+ Button
    btn_loc_st.btn_size_x = NUM_PAD_BUTTON_SIZE_X;
    btn_loc_st.btn_size_y = NUM_PAD_BUTTON_SIZE_Y * 2 + NUM_PAD_BUTTON_SPACE_Y;
    btn_loc_st.btn_align_x = (NUM_PAD_X_OFFSET_FROM_LEFT + NUM_PAD_BUTTON_SPACE_X * 3 + NUM_PAD_BUTTON_SIZE_X * 3);
    btn_loc_st.btn_align_y = (NUM_PAD_Y_OFFSET_FROM_TOP + NUM_PAD_BUTTON_SPACE_Y + NUM_PAD_BUTTON_SIZE_Y);
    btn_plus = lv_keypad_button_create(parent_screen, "+", &btn_loc_st);

    /*************** THRID ROW *******************/
    //4 Button
    btn_loc_st.btn_size_x = NUM_PAD_BUTTON_SIZE_X;
    btn_loc_st.btn_size_y = NUM_PAD_BUTTON_SIZE_Y;
    btn_loc_st.btn_align_x = (NUM_PAD_X_OFFSET_FROM_LEFT);
    btn_loc_st.btn_align_y = (NUM_PAD_Y_OFFSET_FROM_TOP + NUM_PAD_BUTTON_SPACE_Y * 2 + NUM_PAD_BUTTON_SIZE_Y * 2);
    btn_4 = lv_keypad_button_create(parent_screen, "4  D", &btn_loc_st);

    //5 Button
    btn_loc_st.btn_align_x = (NUM_PAD_X_OFFSET_FROM_LEFT + NUM_PAD_BUTTON_SPACE_X + NUM_PAD_BUTTON_SIZE_X);
    btn_loc_st.btn_align_y = (NUM_PAD_Y_OFFSET_FROM_TOP + NUM_PAD_BUTTON_SPACE_Y * 2 + NUM_PAD_BUTTON_SIZE_Y * 2);
    btn_5 = lv_keypad_button_create(parent_screen, "5  E", &btn_loc_st);

    //6 Button
    btn_loc_st.btn_align_x = (NUM_PAD_X_OFFSET_FROM_LEFT + NUM_PAD_BUTTON_SPACE_X * 2 + NUM_PAD_BUTTON_SIZE_X * 2);
    btn_loc_st.btn_align_y = (NUM_PAD_Y_OFFSET_FROM_TOP + NUM_PAD_BUTTON_SPACE_Y * 2 + NUM_PAD_BUTTON_SIZE_Y * 2);
    btn_6 = lv_keypad_button_create(parent_screen, "6  F", &btn_loc_st);

    /*************** FOURTH ROW *******************/
    //1 Button
    btn_loc_st.btn_align_x = (NUM_PAD_X_OFFSET_FROM_LEFT);
    btn_loc_st.btn_align_y = (NUM_PAD_Y_OFFSET_FROM_TOP + NUM_PAD_BUTTON_SPACE_Y * 3 + NUM_PAD_BUTTON_SIZE_Y * 3);
    btn_1 = lv_keypad_button_create(parent_screen, "1", &btn_loc_st);

    //2 Button
    btn_loc_st.btn_align_x = (NUM_PAD_X_OFFSET_FROM_LEFT + NUM_PAD_BUTTON_SPACE_X + NUM_PAD_BUTTON_SIZE_X);
    btn_loc_st.btn_align_y = (NUM_PAD_Y_OFFSET_FROM_TOP + NUM_PAD_BUTTON_SPACE_Y * 3 + NUM_PAD_BUTTON_SIZE_Y * 3);
    btn_2 = lv_keypad_button_create(parent_screen, "2", &btn_loc_st);

    //3 Button
    btn_loc_st.btn_align_x = (NUM_PAD_X_OFFSET_FROM_LEFT + NUM_PAD_BUTTON_SPACE_X * 2 + NUM_PAD_BUTTON_SIZE_X * 2);
    btn_loc_st.btn_align_y = (NUM_PAD_Y_OFFSET_FROM_TOP + NUM_PAD_BUTTON_SPACE_Y * 3 + NUM_PAD_BUTTON_SIZE_Y * 3);
    btn_3 = lv_keypad_button_create(parent_screen, "3", &btn_loc_st);

    //Enter Button
    btn_loc_st.btn_size_x = NUM_PAD_BUTTON_SIZE_X;
    btn_loc_st.btn_size_y = NUM_PAD_BUTTON_SIZE_Y * 2 + NUM_PAD_BUTTON_SPACE_Y;
    btn_loc_st.btn_align_x = (NUM_PAD_X_OFFSET_FROM_LEFT + NUM_PAD_BUTTON_SPACE_X * 3 + NUM_PAD_BUTTON_SIZE_X * 3);
    btn_loc_st.btn_align_y = (NUM_PAD_Y_OFFSET_FROM_TOP + NUM_PAD_BUTTON_SPACE_Y * 3 + NUM_PAD_BUTTON_SIZE_Y * 3);
    btn_ent = lv_keypad_button_create(parent_screen, LV_SYMBOL_NEW_LINE, &btn_loc_st);

    /*************** FIFTH ROW *******************/
    //ZERO Button
    btn_loc_st.btn_size_x = NUM_PAD_BUTTON_SIZE_X * 2 + NUM_PAD_BUTTON_SPACE_X;
    btn_loc_st.btn_size_y = NUM_PAD_BUTTON_SIZE_Y;
    btn_loc_st.btn_align_x = (NUM_PAD_X_OFFSET_FROM_LEFT);
    btn_loc_st.btn_align_y = (NUM_PAD_Y_OFFSET_FROM_TOP + NUM_PAD_BUTTON_SPACE_Y * 4 + NUM_PAD_BUTTON_SIZE_Y * 4);
    btn_0 = lv_keypad_button_create(parent_screen, "0", &btn_loc_st);

    //dot Button
    btn_loc_st.btn_size_x = NUM_PAD_BUTTON_SIZE_X;
    btn_loc_st.btn_size_y = NUM_PAD_BUTTON_SIZE_Y;
    btn_loc_st.btn_align_x = (NUM_PAD_X_OFFSET_FROM_LEFT + NUM_PAD_BUTTON_SPACE_X * 2+ NUM_PAD_BUTTON_SIZE_X * 2);
    btn_loc_st.btn_align_y = (NUM_PAD_Y_OFFSET_FROM_TOP + NUM_PAD_BUTTON_SPACE_Y * 4 + NUM_PAD_BUTTON_SIZE_Y * 4);
    btn_dot = lv_keypad_button_create(parent_screen, ".", &btn_loc_st);
}

static void keypad_layer_lv_state_change(uint16_t keycode, lv_obj_state_fptr state_callback)
{
    switch(keycode)
    {
        case KC_BACKSPACE:
            state_callback(btn_bks);
        break;
        case KC_KP_SLASH:
            state_callback(btn_div);
        break;
        case KC_KP_ASTERISK:
            state_callback(btn_mul);
        break;
        case KC_KP_MINUS:
            state_callback(btn_min);
        break;
        case TD(NUM_KEY_7_AND_A):
            state_callback(btn_7);
        break;
        case TD(NUM_KEY_8_AND_B):
            state_callback(btn_8);
        break;
        case TD(NUM_KEY_9_AND_C):
            state_callback(btn_9);
        break;
        case KC_KP_PLUS:
            state_callback(btn_plus);
        break;
        case TD(NUM_KEY_4_AND_D):
            state_callback(btn_4);
        break;
        case TD(NUM_KEY_5_AND_E):
            state_callback(btn_5);
        break;
        case TD(NUM_KEY_6_AND_F):
            state_callback(btn_6);
        break;
        case KC_KP_1:
            state_callback(btn_1);
        break;
        case KC_KP_2:
            state_callback(btn_2);
        break;
        case KC_KP_3:
            state_callback(btn_3);
        break;
        case KC_KP_ENTER:
            state_callback(btn_ent);
        break;
        case KC_KP_0:
            state_callback(btn_0);
        break;
        case KC_KP_DOT:
            state_callback(btn_dot);
        break;
        default:
        break;
    }
}

static inline void keypad_button_press(lv_obj_t * button)
{
    lv_obj_add_state(button, LV_STATE_PRESSED);
}

static inline void keypad_button_release(lv_obj_t * button)
{
    lv_obj_clear_state(button, LV_STATE_PRESSED);
}

/* to change the button pressed animation for the keypad screen */
void keypad_layer_function_key_pressed(uint16_t keycode)
{
    keypad_layer_lv_state_change(keycode, keypad_button_press);
}

/* to change the button released animation for the keypad screen */
void keypad_layer_function_key_released(uint16_t keycode)
{
    keypad_layer_lv_state_change(keycode, keypad_button_release);
}
