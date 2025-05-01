#include "keymap.h"
#include QMK_KEYBOARD_H
#include "../../lvgl/keypad_screen.h"

#define KEYPAD_BUTTON_PRESS_IMG(button) lv_obj_add_state(button, LV_STATE_PRESSED)
#define KEYPAD_BUTTON_RELEASE_IMG(button) lv_obj_clear_state(button, LV_STATE_PRESSED)

bool keypad_layer_function_key_pressed(uint16_t keycode) {
    switch(keycode)
    {
        case KC_BACKSPACE:
            KEYPAD_BUTTON_PRESS_IMG(btn_bks);
        break;
        case KC_KP_SLASH:
            KEYPAD_BUTTON_PRESS_IMG(btn_div);
        break;
        case KC_KP_ASTERISK:
            KEYPAD_BUTTON_PRESS_IMG(btn_mul);
        break;
        case KC_KP_MINUS:
            KEYPAD_BUTTON_PRESS_IMG(btn_min);
        break;
        case TD(NUM_KEY_7_AND_A):
            KEYPAD_BUTTON_PRESS_IMG(btn_7);
        break;
        case TD(NUM_KEY_8_AND_B):
            KEYPAD_BUTTON_PRESS_IMG(btn_8);
        break;
        case TD(NUM_KEY_9_AND_C):
            KEYPAD_BUTTON_PRESS_IMG(btn_9);
        break;
        case KC_KP_PLUS:
            KEYPAD_BUTTON_PRESS_IMG(btn_plus);
        break;
        case TD(NUM_KEY_4_AND_D):
            KEYPAD_BUTTON_PRESS_IMG(btn_4);
        break;
        case TD(NUM_KEY_5_AND_E):
            KEYPAD_BUTTON_PRESS_IMG(btn_5);
        break;
        case TD(NUM_KEY_6_AND_F):
            KEYPAD_BUTTON_PRESS_IMG(btn_6);
        break;
        case KC_KP_1:
            KEYPAD_BUTTON_PRESS_IMG(btn_1);
        break;
        case KC_KP_2:
            KEYPAD_BUTTON_PRESS_IMG(btn_2);
        break;
        case KC_KP_3:
            KEYPAD_BUTTON_PRESS_IMG(btn_3);
        break;
        case KC_KP_ENTER:
            KEYPAD_BUTTON_PRESS_IMG(btn_ent);
        break;
        case KC_KP_0:
            KEYPAD_BUTTON_PRESS_IMG(btn_0);
        break;
        case KC_KP_DOT:
            KEYPAD_BUTTON_PRESS_IMG(btn_dot);
        break;
        default:
        break;
    }
    return true;
}


bool keypad_layer_function_key_released(uint16_t keycode)
{
    switch(keycode)
    {
        case KC_BACKSPACE:
            KEYPAD_BUTTON_RELEASE_IMG(btn_bks);
        break;
        case KC_KP_SLASH:
            KEYPAD_BUTTON_RELEASE_IMG(btn_div);
        break;
        case KC_KP_ASTERISK:
            KEYPAD_BUTTON_RELEASE_IMG(btn_mul);
        break;
        case KC_KP_MINUS:
            KEYPAD_BUTTON_RELEASE_IMG(btn_min);
        break;
        case TD(NUM_KEY_7_AND_A):
            KEYPAD_BUTTON_RELEASE_IMG(btn_7);
        break;
        case TD(NUM_KEY_8_AND_B):
            KEYPAD_BUTTON_RELEASE_IMG(btn_8);
        break;
        case TD(NUM_KEY_9_AND_C):
            KEYPAD_BUTTON_RELEASE_IMG(btn_9);
        break;
        case KC_KP_PLUS:
            KEYPAD_BUTTON_RELEASE_IMG(btn_plus);
        break;
        case TD(NUM_KEY_4_AND_D):
            KEYPAD_BUTTON_RELEASE_IMG(btn_4);
        break;
        case TD(NUM_KEY_5_AND_E):
            KEYPAD_BUTTON_RELEASE_IMG(btn_5);
        break;
        case TD(NUM_KEY_6_AND_F):
            KEYPAD_BUTTON_RELEASE_IMG(btn_6);
        break;
        case KC_KP_1:
            KEYPAD_BUTTON_RELEASE_IMG(btn_1);
        break;
        case KC_KP_2:
            KEYPAD_BUTTON_RELEASE_IMG(btn_2);
        break;
        case KC_KP_3:
            KEYPAD_BUTTON_RELEASE_IMG(btn_3);
        break;
        case KC_KP_ENTER:
            KEYPAD_BUTTON_RELEASE_IMG(btn_ent);
        break;
        case KC_KP_0:
            KEYPAD_BUTTON_RELEASE_IMG(btn_0);
        break;
        case KC_KP_DOT:
            KEYPAD_BUTTON_RELEASE_IMG(btn_dot);
        break;
        default:
        break;
    }
    return true;
}
