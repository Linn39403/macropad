// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "keymap.h"

#include QMK_KEYBOARD_H

bool is_locked = false;

extern lv_obj_t *tab_view;

tap_dance_action_t tap_dance_actions[] =
{
    [NUM_KEY_7_AND_A] = ACTION_TAP_DANCE_DOUBLE(KC_KP_7, KC_A),
    [NUM_KEY_8_AND_B] = ACTION_TAP_DANCE_DOUBLE(KC_KP_8, KC_B),
    [NUM_KEY_9_AND_C] = ACTION_TAP_DANCE_DOUBLE(KC_KP_9, KC_C),
    [NUM_KEY_4_AND_D] = ACTION_TAP_DANCE_DOUBLE(KC_KP_4, KC_D),
    [NUM_KEY_5_AND_E] = ACTION_TAP_DANCE_DOUBLE(KC_KP_5, KC_E),
    [NUM_KEY_6_AND_F] = ACTION_TAP_DANCE_DOUBLE(KC_KP_6, KC_F),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Office Keys Layer Layout */
    [OFFICE_LAYER] = LAYOUT(
    UIE, OFFICE_PASSWORD, OFC_KEY_3, OFC_KEY_4,
    OFC_KEY_5, OFC_KEY_6, OFC_KEY_7, OFC_KEY_8,
    OFC_KEY_9, OFC_KEY_10, OFC_KEY_11, OFC_KEY_12,
    OFC_KEY_13, OFC_KEY_14, OFC_KEY_15, OFC_KEY_16,
    RESET_KEY1, RESET_KEY2, OFC_KEY_19, OFC_RELAY_CTRL),

    /* Total Commander Layer Layout */
    [TOTAL_COMMANDER_LAYER] = LAYOUT(
//  rename , properties, new text file, jump to root
    S(KC_F6), S(KC_F10), S(KC_F4), LCTL(KC_BSLS),
//  new tab    , close tab , tab change  , switch tab
    LCTL(KC_UP), LCTL(KC_W), LCTL(KC_TAB), KC_TAB,
//  Sort Name, Sort Ext, Sort Time, Sort Size
    LCTL(KC_F3), LCTL(KC_F4), LCTL(KC_F5), LCTL(KC_F6),
    PER_KEY12, PER_KEY13, PER_KEY14, PER_KEY15,
    PER_KEY16, PER_KEY17, PER_KEY18, PER_KEY19),

    /*NUMPAD Layer Layout */
    [NUMPAD_LAYER] = LAYOUT(
    KC_BACKSPACE, KC_KP_SLASH, KC_KP_ASTERISK, KC_KP_MINUS,
	TD(NUM_KEY_7_AND_A), TD(NUM_KEY_8_AND_B), TD(NUM_KEY_9_AND_C), KC_KP_PLUS ,
	TD(NUM_KEY_4_AND_D), TD(NUM_KEY_5_AND_E), TD(NUM_KEY_6_AND_F), KC_KP_PLUS,
	KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_ENTER,
	KC_KP_0, KC_KP_0, KC_KP_DOT, KC_KP_ENTER),

    /* cpp Layer Layout */
    [CPP_LAYER] = LAYOUT (
    CPP_KEY_for_loop, CPP_KEY_while_loop, CPP_KEY_struct, CPP_KEY_class,
    CPP_KEY_switch, CPP_KEY_D, CPP_KEY_E, CPP_KEY_F,
    CPP_KEY_cout, CPP_KEY_9, CPP_KEY_A, CPP_KEY_B,
    CPP_KEY_4, CPP_KEY_5, CPP_KEY_6, CPP_KEY_7,
    CPP_KEY_0, CPP_KEY_1, CPP_KEY_2, CPP_KEY_3
    ),
    };


void keyboard_pre_init_user(void) {
    setPinInputHigh(ENCODER_LEFT_PUSH_BUTTON_PIN);
    setPinInputHigh(ENCODER_MAIN_PUSH_BUTTON_PIN);
    setPinInputHigh(ENCODER_RIGHT_PUSH_BUTTON_PIN);
}

int convert_tabview_to_layer(int tab_sel)
{
    extern struct kb_layer_type kb_layers[3];
    if(tab_sel < LAYER_COUNT)
    {
        return kb_layers[tab_sel].layer;
    }
    //return default
    return OFFICE_LAYER;
}
/*
- Returning true lets QMK keep processing the key event (running its built‑in functions or further custom processing).
- Returning false stops QMK from doing any further processing for that key event.
*/
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    int8_t current_layer = convert_tabview_to_layer(lv_tabview_get_tab_act(tab_view));
    layer_move(current_layer);
    if (record->event.pressed) {
        switch (current_layer) {
            case OFFICE_LAYER:
                officelayer_function_key_pressed(keycode);
                return false;

            case TOTAL_COMMANDER_LAYER:
                return true;

            case NUMPAD_LAYER:
                keypad_layer_function_key_pressed(keycode);
                return true;

            case CPP_LAYER:
                cpplayer_function_key_pressed(keycode);
                return false;
        }
    }
    /* Release #endif*/
    if (!record->event.pressed) {
        switch(current_layer)
        {
            case OFFICE_LAYER:
                break;

            case TOTAL_COMMANDER_LAYER:
                return true;

            case NUMPAD_LAYER:
                keypad_layer_function_key_released(keycode);
                return true;

            case CPP_LAYER:
                break;
        }
        return false;
    }
    return false;
}

void matrix_scan_user(void) {
    #if 0
    extern bool reset_key_a_pressed;
    extern bool reset_key_b_pressed;
    if (reset_key_a_pressed && reset_key_b_pressed) {
        wait_ms(500);
        reset_keyboard();
    }
    #endif

    /* Encoder Read */
    int16_t tab_sel = lv_tabview_get_tab_act(tab_view);
    int8_t selected_layer = 0;
    static bool encoder_push_prev = false;
    bool encoder_push_now = readPin(ENCODER_MAIN_PUSH_BUTTON_PIN);
    if(encoder_push_now && !encoder_push_prev)
    {
        selected_layer = convert_tabview_to_layer(tab_sel);
        switch(selected_layer)
        {
            case TOTAL_COMMANDER_LAYER:
                tap_code(KC_ENTER);
            break;
        }
    }

    encoder_push_prev = encoder_push_now;

    static bool encoder_left_push_button_prev = false;
    static bool encoder_right_push_button_prev = false;
    bool encoder_left_push_button_now = readPin(ENCODER_LEFT_PUSH_BUTTON_PIN);
    bool encoder_right_push_button_now = readPin(ENCODER_RIGHT_PUSH_BUTTON_PIN);

    /* Two Push Buttons Read Handling */
    if((encoder_left_push_button_now == false) &&
       (encoder_left_push_button_now != encoder_left_push_button_prev))
    {
        tab_sel--;
        lv_tabview_set_act(tab_view, tab_sel, LV_ANIM_OFF);
    }
    else if((encoder_right_push_button_now == false) &&
            (encoder_right_push_button_now != encoder_right_push_button_prev))
    {
        tab_sel++;
        if(tab_sel >= LAYER_COUNT){
            tab_sel = 0; //to reset the layer to default
        }
        lv_tabview_set_act(tab_view, tab_sel, LV_ANIM_OFF);
    }
    encoder_left_push_button_prev = encoder_left_push_button_now;
    encoder_right_push_button_prev = encoder_right_push_button_now;

    /* if Both Buttons are pressed for 2000ms, reset the keypad */
    if(encoder_left_push_button_now == false && encoder_right_push_button_now == false)
    {
        wait_ms(2000);
        //check again the buttons press value
        encoder_left_push_button_now = readPin(ENCODER_LEFT_PUSH_BUTTON_PIN);
        encoder_right_push_button_now = readPin(ENCODER_RIGHT_PUSH_BUTTON_PIN);
        if(encoder_left_push_button_now == false && encoder_right_push_button_now == false)
        {
            reset_keyboard();
        }
    }
}

/* This Encoder Update User function is only called when user rotate the knob.
   If you pressed the button, this function won't be called.
*/
bool encoder_update_user(uint8_t index, bool clockwise) {
    int16_t tab_sel = lv_tabview_get_tab_act(tab_view);
    int8_t selected_layer = 0;
    switch (index) {
        case 0: // left
            break;

        case 1: // main/middle
            /* Keyboard layer will change only when encoder is push and rotate. */
            #if 0
            if(readPin(ENCODER_MAIN_PUSH_BUTTON_PIN) == false)
            {
                if (clockwise) {
                    tab_sel++;
                }
                else {
                    tab_sel--;
                }
                tab_sel &= (LAYER_COUNT-1) ;
                lv_tabview_set_act(tab_view, tab_sel, LV_ANIM_OFF);
            }
            else
            {
            #endif
                /* Encoder can be use for other operations depending on different layer */
                selected_layer = convert_tabview_to_layer(tab_sel);
                switch(selected_layer)
                {
                    case OFFICE_LAYER:
                        if(clockwise) tap_code(KC_VOLU);
                        else tap_code(KC_VOLD);
                    break;

                    case TOTAL_COMMANDER_LAYER:
                        if(clockwise) tap_code(KC_UP);
                        else tap_code(KC_DOWN);
                    break;

                    case NUMPAD_LAYER:
                        if(clockwise) tap_code(KC_MS_WH_DOWN);
                        else tap_code(KC_MS_WH_UP);
                    break;

                    case CPP_LAYER:
                    break;
                }

            #if 0
            }
            #endif
            return false;

        case 2: // right
            return false;

        default:
            return false;
    }
    return true;
}

