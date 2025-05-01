#include "keymap.h"
#include QMK_KEYBOARD_H

static uint16_t last_reset_key_a_press_time = 0;
static uint16_t last_reset_key_b_press_time = 0;
bool reset_key_a_pressed = false;
bool reset_key_b_pressed = false;
extern painter_device_t display;

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
            if (current_time - last_reset_key_a_press_time > 800) {
                reset_key_a_pressed = true;
            } else {
                reset_key_a_pressed = false;
            }
            last_reset_key_a_press_time = current_time;
            return false;

        case RESET_KEY2:
            if (current_time - last_reset_key_b_press_time > 800) {
                reset_key_b_pressed = true;
            } else {
                reset_key_b_pressed = false;
            }
            last_reset_key_b_press_time = current_time;
            //wait_ms(600);
            //reset_keyboard();
            return false;

        case OFC_RELAY_CTRL:
            // Send Win + Space
            //register_code(KC_LGUI);   // Hold the Win key
            //tap_code(KC_SPACE);       // Tap the Space key
            //unregister_code(KC_LGUI); // Release the Win key

#if 0
            if (keyboard_language == US_ENGLISH) {
                keyboard_language = BURMESE;
                qp_drawimage(display, 220, 112, myanmar_flag_image);
            } else {
                keyboard_language = US_ENGLISH;
                qp_drawimage(display, 220, 112, us_flag_image);
            }
            qp_flush(display);
#endif
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
