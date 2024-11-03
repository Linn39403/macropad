// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

bool is_locked = false;

enum custom_keycodes
{
    UIE,
    OFFICE_PASSWORD,

    RESET_KEY1,
    RESET_KEY2
};
static uint16_t last_reset_key_press_time = 0;
static bool first_reset_key_pressed = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        UIE,   OFFICE_PASSWORD,   KC_P9,   KC_PSLS,
        KC_P4,   KC_P5,   KC_P6,   KC_PAST,
        KC_P1,   KC_P2,   KC_P3,   KC_PMNS,
        KC_P0,   KC_PDOT, KC_PENT, KC_PPLS,
        RESET_KEY1,  RESET_KEY2, KC_PENT, KC_PPLS
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    uint16_t current_time = timer_read();

    if (record->event.pressed) 
    {
        switch (keycode) 
        {
            case UIE:
                    SEND_STRING("uie81489");
                break;

            case OFFICE_PASSWORD:
                    SEND_STRING("2831992#Ung");
                break;

            case RESET_KEY1:
                    first_reset_key_pressed   = true;
                    last_reset_key_press_time = current_time;
                break;

            case RESET_KEY2:
                if(first_reset_key_pressed && (current_time - last_reset_key_press_time < 500))
                {
                    wait_ms(1000);
                    reset_keyboard();
                }
                first_reset_key_pressed = false;
                break;
                
            default:
                return false;
        }
    }
    if(!record->event.pressed)
    {
        switch(keycode)
        {
            case RESET_KEY1:
                first_reset_key_pressed = false;
            break;

            default:
            return false;
        }
    }
    return true;
}

bool encoder_update_user(uint8_t index, bool clockwise)
{
    switch(index)
    {
        case 0: //left
            if(clockwise){
                tap_code(KC_KB_VOLUME_UP);
            }else{
                tap_code(KC_KB_VOLUME_DOWN);
            }
        break;

        case 1: //main/middle
            if(clockwise){
                tap_code(KC_PAGE_UP);
            }else{
                tap_code(KC_PAGE_DOWN);
            }
        break;
        
        case 2: //right
            if(clockwise){
                tap_code(KC_RIGHT);
            }else{
                tap_code(KC_LEFT);
            }
        break;
                
        default:
            return false;
    }
    return true;
}

