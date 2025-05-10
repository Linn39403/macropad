// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "keymap.h"
#include QMK_KEYBOARD_H
#include "config.h"
#include "print.h"

bool is_locked = false;

extern lv_obj_t *tab_view;
extern struct kb_layer_type kb_layers[LAYER_COUNT];
uint16_t get_active_kb_layer(void);
void set_kb_layer(uint16_t kb_layer_index);
#ifdef ENABLE_NUMPAD_LAYER
tap_dance_action_t tap_dance_actions[] =
{
    [NUM_KEY_7_AND_A] = ACTION_TAP_DANCE_DOUBLE(KC_KP_7, KC_A),
    [NUM_KEY_8_AND_B] = ACTION_TAP_DANCE_DOUBLE(KC_KP_8, KC_B),
    [NUM_KEY_9_AND_C] = ACTION_TAP_DANCE_DOUBLE(KC_KP_9, KC_C),
    [NUM_KEY_4_AND_D] = ACTION_TAP_DANCE_DOUBLE(KC_KP_4, KC_D),
    [NUM_KEY_5_AND_E] = ACTION_TAP_DANCE_DOUBLE(KC_KP_5, KC_E),
    [NUM_KEY_6_AND_F] = ACTION_TAP_DANCE_DOUBLE(KC_KP_6, KC_F),
};
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Office Keys Layer Layout */
#ifdef ENABLE_HOME_SCREEN_LAYER
    [HOME_SCREEN_LAYER] = LAYOUT(
    UIE, OFFICE_PASSWORD, OFC_KEY_3, OFC_KEY_4,
    OFC_KEY_5, OFC_KEY_6, OFC_KEY_7, OFC_KEY_8,
    OFC_KEY_9, OFC_KEY_10, OFC_KEY_11, OFC_KEY_12,
    OFC_KEY_13, OFC_KEY_14, OFC_KEY_15, OFC_KEY_16,
    RESET_KEY1, RESET_KEY2, OFC_KEY_19, OFC_RELAY_CTRL),
#endif

#ifdef ENABLE_TOTAL_COMMANDER_LAYER
    /* Total Commander Layer Layout */
    [TOTAL_COMMANDER_LAYER] = LAYOUT(
//  rename , properties, new text file, jump to root
    S(KC_F6), S(KC_F10), S(KC_F4), LCTL(KC_BSLS),
//  new tab    , close tab , tab change  , switch tab
    LCTL(KC_UP), LCTL(KC_W), LCTL(KC_TAB), KC_TAB,
//  Sort Name, Sort Ext, Sort Time, Sort Size
    LCTL(KC_F3), LCTL(KC_F4), LCTL(KC_F5), LCTL(KC_F6),
    KC_NO, KC_NO, KC_NO, KC_BACKSPACE,
    KC_NO, KC_NO, KC_NO, KC_NO),
#endif

#ifdef ENABLE_NUMPAD_LAYER
    /*NUMPAD Layer Layout */
    [NUMPAD_LAYER] = LAYOUT(
    KC_BACKSPACE, KC_KP_SLASH, KC_KP_ASTERISK, KC_KP_MINUS,
	TD(NUM_KEY_7_AND_A), TD(NUM_KEY_8_AND_B), TD(NUM_KEY_9_AND_C), KC_KP_PLUS ,
	TD(NUM_KEY_4_AND_D), TD(NUM_KEY_5_AND_E), TD(NUM_KEY_6_AND_F), KC_KP_PLUS,
	KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_ENTER,
	KC_KP_0, KC_KP_0, KC_KP_DOT, KC_KP_ENTER),
#endif
#ifdef ENABLE_CPP_LAYER
    /* cpp Layer Layout */
    [CPP_LAYER] = LAYOUT (
    CPP_KEY_for_loop, CPP_KEY_while_loop, CPP_KEY_struct, CPP_KEY_class,
    CPP_KEY_switch, CPP_KEY_D, CPP_KEY_E, CPP_KEY_F,
    CPP_KEY_cout, CPP_KEY_9, CPP_KEY_A, CPP_KEY_B,
    CPP_KEY_4, CPP_KEY_5, CPP_KEY_6, CPP_KEY_7,
    CPP_KEY_0, CPP_KEY_1, CPP_KEY_2, CPP_KEY_3
    ),
#endif

#ifdef ENABLE_RESOURCE_LAYER
    /* Resource Layer purely GUI */
    [RESOURCE_LAYER] = LAYOUT(
    KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO
    ),
#endif

    };


void keyboard_pre_init_user(void) {
    setPinInputHigh(ENCODER_LEFT_PUSH_BUTTON_PIN);
    setPinInputHigh(ENCODER_MAIN_PUSH_BUTTON_PIN);
    setPinInputHigh(ENCODER_RIGHT_PUSH_BUTTON_PIN);
}
//this func need to destory
int convert_tabview_to_layer(int tab_sel)
{
    if(tab_sel < LAYER_COUNT)
    {
        return kb_layers[tab_sel].screen_layer_id;
    }
    //return default
    return 0;
}

/*
- Returning true lets QMK keep processing the key event (running its built‑in functions or further custom processing).
- Returning false stops QMK from doing any further processing for that key event.
*/
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    //int8_t current_layer = convert_tabview_to_layer(lv_tabview_get_tab_act(tab_view));
    //layer_move(current_layer);
    uint16_t current_layer = get_active_kb_layer();
    layer_move(current_layer);
    /* Button Pressed */
    if (record->event.pressed)
    {
        switch (current_layer)
        {
#ifdef ENABLE_HOME_SCREEN_LAYER
            case HOME_SCREEN_LAYER:
                officelayer_function_key_pressed(keycode);
                return false;
#endif

#ifdef ENABLE_TOTAL_COMMANDER_LAYER
            case TOTAL_COMMANDER_LAYER:
                tc_layer_function_key_pressed(keycode);
                return true;
#endif

#ifdef ENABLE_NUMPAD_LAYER
            case NUMPAD_LAYER:
                //uprintf("numpad P:Key = %d\n", keycode);
                keypad_layer_function_key_pressed(keycode);
                return true;
#endif

#ifdef ENABLE_CPP_LAYER
            case CPP_LAYER:
                cpplayer_function_key_pressed(keycode);
                return false;
#endif
        }/*end switch (current_layer)*/
    }/*end if(record->event.pressed)*/

    /* Button Released */
    if (!record->event.pressed)
    {
        switch(current_layer)
        {
#ifdef ENABLE_HOME_SCREEN_LAYER
            case HOME_SCREEN_LAYER:
                break;
#endif

#ifdef ENABLE_TOTAL_COMMANDER_LAYER
            case TOTAL_COMMANDER_LAYER:
                tc_layer_function_key_released(keycode);
                return true;
#endif

#ifdef ENABLE_NUMPAD_LAYER
            case NUMPAD_LAYER:
                keypad_layer_function_key_released(keycode);
                return true;
#endif

#ifdef ENABLE_CPP_LAYER
            case CPP_LAYER:
                break;
#endif
        }/*end switch(current_layer)*/
        return false;
    }/*end if (!record->event.pressed)*/
    return false;
}

void matrix_scan_user(void)
{
    static bool encoder_left_push_button_state_prev = false;
    static bool encoder_main_push_button_state_prev = false;
    static bool encoder_right_push_button_state_prev = false;

    bool encoder_left_push_button_state_now = readPin(ENCODER_LEFT_PUSH_BUTTON_PIN);
    bool encoder_right_push_button_state_now = readPin(ENCODER_RIGHT_PUSH_BUTTON_PIN);
    bool encoder_main_push_button_state_now = readPin(ENCODER_MAIN_PUSH_BUTTON_PIN);

    uint8_t selected_layer = get_active_kb_layer();

    if((encoder_main_push_button_state_now == false) &&
       (encoder_main_push_button_state_now != encoder_main_push_button_state_prev))
    {
        /* Main Encoder Button Pressed */
        switch(selected_layer)
        {
#ifdef ENABLE_TOTAL_COMMANDER_LAYER
            case TOTAL_COMMANDER_LAYER:
                tap_code(KC_ENT);
            break;
#endif
            default:
            break;
        }
    }

    /* Two Push Buttons Read Handling */
    if((encoder_left_push_button_state_now == false) &&
       (encoder_left_push_button_state_now != encoder_left_push_button_state_prev))
    {
        int16_t index = get_active_kb_layer();
        if(--index < 0)
        {
            index = LAYER_COUNT - 1;
        }
        set_kb_layer(index);
    }
    else if((encoder_right_push_button_state_now == false) &&
            (encoder_right_push_button_state_now != encoder_right_push_button_state_prev))
    {
        uint16_t index = get_active_kb_layer();
        if(++index >= LAYER_COUNT)
        {
            index=0;
        }
        set_kb_layer(index);
    }

    encoder_left_push_button_state_prev = encoder_left_push_button_state_now;
    encoder_right_push_button_state_prev = encoder_right_push_button_state_now;
    encoder_main_push_button_state_prev = encoder_main_push_button_state_now;

    /* if Both Buttons are pressed for 1000ms, reset the keypad */
    if(encoder_left_push_button_state_now == false && encoder_right_push_button_state_now == false)
    {
        wait_ms(1000);
        //check again the buttons press value
        encoder_left_push_button_state_now = readPin(ENCODER_LEFT_PUSH_BUTTON_PIN);
        encoder_right_push_button_state_now = readPin(ENCODER_RIGHT_PUSH_BUTTON_PIN);
        if(encoder_left_push_button_state_now == false && encoder_right_push_button_state_now == false)
        {
            reset_keyboard();
        }
    }


}

/* This Encoder Update User function is only called when user rotate the knob.
   If you pressed the button, this function won't be called.
*/
bool encoder_update_user(uint8_t index, bool clockwise)
{
    uint8_t selected_layer = get_active_kb_layer();

    switch (index) {
        case 0: /* left */
            break;

        case 1: /* main, middle */
            /* Encoder can be use for other operations depending on different layer */
            switch(selected_layer)
            {
#ifdef ENABLE_HOME_SCREEN_LAYER
                case HOME_SCREEN_LAYER:
                    if(clockwise) tap_code(KC_VOLU);
                    else tap_code(KC_VOLD);
                break;
#endif

#ifdef ENABLE_TOTAL_COMMANDER_LAYER
                case TOTAL_COMMANDER_LAYER:
                    if(clockwise)
                    {
                        tap_code(KC_UP);
                    }
                    else
                    {
                        tap_code(KC_DOWN);
                    }
                break;
#endif

#ifdef ENABLE_NUMPAD_LAYER
                case NUMPAD_LAYER:
                    if(clockwise) tap_code(KC_MS_WH_DOWN);
                    else tap_code(KC_MS_WH_UP);
                break;
#endif

#ifdef ENABLE_CPP_LAYER
                case CPP_LAYER:
                break;
#endif
            }
            return false;

        case 2: /* right */
            return false;

        default:
            return false;
    }
    return true;
}

#include "raw_hid.h"
#include "lvgl/resource_screen.h"
#define CHANGE_LVGL_KEYPAD_LAYER(LAYER_NAME) lv_tabview_set_act(tab_view, kb_layers[LAYER_NAME].screen_layer_id, LV_ANIM_OFF)
void raw_hid_receive(uint8_t *data, uint8_t length)
{
    //uint8_t response[length];
    //memset(response, 0, length);
    //response[0] = 'B';

    /* getting time from host
     * FOrmat : ti123456
    */
    if(data[0] == 't' && data[1] == 'i') {
        int hr = (data[2] - '0')*10 + (data[3] - '0');
        int min= (data[4] - '0')*10 + (data[5] - '0');
        int sec= (data[6] - '0')*10 + (data[7] - '0');
       clock_update_time(hr, min,sec);
        //raw_hid_send(response, length);
    }
    if(data[0] == 'c' && data[1] == 'p')
    {
        int cpu_res_in_percent = (data[2] - '0') * 100 + (data[3] - '0') * 10 + (data[4] - '0');
        cpu_resource_set_value(cpu_res_in_percent);
    }
    if(data[0] == 'a' && data[1] == 'p' && data[2] == 'p' && data[3] == '_')
    {
        uint8_t * app_name = &data[4];
        if(app_name[0] == 't' && app_name[1] == 't' && app_name[2] == 'c')
        {
#ifdef ENABLE_TOTAL_COMMANDER_LAYER
            CHANGE_LVGL_KEYPAD_LAYER(TOTAL_COMMANDER_LAYER);
#endif
        }
        else if(app_name[0] == 'c' && app_name[1] == 'a' && app_name[2] == 'l')
        {
#ifdef ENABLE_CPP_LAYER
            CHANGE_LVGL_KEYPAD_LAYER(NUMPAD_LAYER);
#endif
        }
        else if(app_name[0] == 'v' && app_name[1] == 's' && app_name[2] == 'c')
        {

        }
    }/* end if(data[0] == 'a' && data[1] == 'p' && data[2] == 'p' && data[3] == '_') */
}
