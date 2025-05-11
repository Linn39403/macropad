#include "keymap.h"
#include QMK_KEYBOARD_H
#include "config.h"

#ifdef ENABLE_HOME_SCREEN_LAYER

/* return true for the tap dance keys, otherwise return false */
bool officelayer_function_key_pressed(uint16_t keycode) {
    uint16_t current_time = timer_read();
    switch (keycode) {
        case OFC_KEY_3:
        case OFC_KEY_4:
        case OFC_KEY_5:
        case OFC_KEY_6:
        case OFC_KEY_7:
        case OFC_KEY_8:
        case OFC_KEY_9:
        case OFC_KEY_10:
        case OFC_KEY_11:
        case OFC_KEY_12:
        case OFC_KEY_13:
        case OFC_KEY_14:
        case OFC_KEY_15:
        case OFC_KEY_16:
        case OFC_KEY_19:
            return false;

        case UIE:
            SEND_STRING("uie81489");
            return false;

        case OFFICE_PASSWORD:
            SEND_STRING("world");
            return false;

        case RESET_KEY1:
            return false;

        case RESET_KEY2:
            return false;

        case OFC_RELAY_CTRL:
            // Send Win + Space
            //register_code(KC_LGUI);   // Hold the Win key
            //tap_code(KC_SPACE);       // Tap the Space key
            //unregister_code(KC_LGUI); // Release the Win key
            return false;

        default:
            return false;
    }
}


bool officelayer_function_key_released(uint16_t keycode)
{
    switch (keycode) {
        case RESET_KEY1:
            return false;

        case OFC_RELAY_CTRL:
            return false;

        default:
            return false;
    }
}

#endif
