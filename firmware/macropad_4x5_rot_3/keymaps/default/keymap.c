// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "keymap.h"
#include QMK_KEYBOARD_H
#include "config.h"
#include "print.h"
#include "lvgl/keypad_screen.h"

bool is_locked = false;

extern struct kb_layer_type kb_layers[LAYER_COUNT];
uint8_t SCREEN_u8GetActiveLayer(void);
void SCREEN_vChangeLayer(uint16_t kb_layer_index);
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


void keyboard_pre_init_user(void)
{
    setPinInputHigh(ENCODER_LEFT_PUSH_BUTTON_PIN);
    setPinInputHigh(ENCODER_MAIN_PUSH_BUTTON_PIN);
    setPinInputHigh(ENCODER_RIGHT_PUSH_BUTTON_PIN);
}

/*
- Returning true lets QMK keep processing the key event (running its built‑in functions or further custom processing).
- Returning false stops QMK from doing any further processing for that key event.
*/
bool process_record_user(uint16_t u16KeyCode, keyrecord_t * spRecord) {
    uint8_t u8CurrentLayer = SCREEN_u8GetActiveLayer();
    layer_move(u8CurrentLayer);
    /* Button Pressed */
    if (spRecord->event.pressed)
    {
        switch (u8CurrentLayer)
        {
#ifdef ENABLE_HOME_SCREEN_LAYER
            case HOME_SCREEN_LAYER:
                officelayer_function_key_pressed(u16KeyCode);
                return false;
#endif

#ifdef ENABLE_TOTAL_COMMANDER_LAYER
            case TOTAL_COMMANDER_LAYER:
                TTCMD_vKeyPressedCallBackFunction(u16KeyCode);
                return true;
#endif

#ifdef ENABLE_NUMPAD_LAYER
            case NUMPAD_LAYER:
                //uprintf("numpad P:Key = %d\n", keycode);
                KPAD_vKeyPressedCallBackFunction(u16KeyCode);
                return true;
#endif

#ifdef ENABLE_CPP_LAYER
            case CPP_LAYER:
                cpplayer_function_key_pressed(u16KeyCode);
                return false;
#endif
        }/*end switch (u8CurrentLayer)*/
    }/*end if(spRecord->event.pressed)*/

    /* Button Released */
    if (!spRecord->event.pressed)
    {
        switch(u8CurrentLayer)
        {
#ifdef ENABLE_HOME_SCREEN_LAYER
            case HOME_SCREEN_LAYER:
                break;
#endif

#ifdef ENABLE_TOTAL_COMMANDER_LAYER
            case TOTAL_COMMANDER_LAYER:
                TTCMD_vKeyReleasedCallBackFunction(u16KeyCode);
                return true;
#endif

#ifdef ENABLE_NUMPAD_LAYER
            case NUMPAD_LAYER:
                KPAD_vKeyReleasedCallBackFunction(u16KeyCode);
                return true;
#endif

#ifdef ENABLE_CPP_LAYER
            case CPP_LAYER:
                break;
#endif
        }/*end switch(u8CurrentLayer)*/
        return false;
    }/*end if (!spRecord->event.pressed)*/
    return false;
}

void matrix_scan_user(void)
{
    static bool KMAP__boEncoderLeftPushBtnStatePrev = false;
    static bool KMAP__boEncoderRightPushBtnStatePrev = false;
    static bool KMAP__boEncoderMainPushBtnStatePrev = false;

    bool KMAP_boEncoderLeftPushBtnStateNow = readPin(ENCODER_LEFT_PUSH_BUTTON_PIN);
    bool KMAP_boEncoderRightPushBtnStateNow = readPin(ENCODER_RIGHT_PUSH_BUTTON_PIN);
    bool KMAP_boEncoderMainPushBtnStateNow = readPin(ENCODER_MAIN_PUSH_BUTTON_PIN);

    uint8_t u8ActiveLayer = SCREEN_u8GetActiveLayer();

    if((KMAP_boEncoderMainPushBtnStateNow == false) &&
       (KMAP_boEncoderMainPushBtnStateNow != KMAP__boEncoderMainPushBtnStatePrev))
    {
        /* Main Encoder Button Pressed */
        switch(u8ActiveLayer)
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
    if((KMAP_boEncoderLeftPushBtnStateNow == false) &&
       (KMAP_boEncoderLeftPushBtnStateNow != KMAP__boEncoderLeftPushBtnStatePrev))
    {
        if(--u8ActiveLayer == 0xFF) /* reach minus ? */
        {
            u8ActiveLayer = LAYER_COUNT - 1;
        }
        SCREEN_vChangeLayer(u8ActiveLayer);
    }
    else if((KMAP_boEncoderRightPushBtnStateNow == false) &&
            (KMAP_boEncoderRightPushBtnStateNow != KMAP__boEncoderRightPushBtnStatePrev))
    {
        if(++u8ActiveLayer >= LAYER_COUNT)
        {
            u8ActiveLayer = 0;
        }
        SCREEN_vChangeLayer(u8ActiveLayer);
    }

    KMAP__boEncoderLeftPushBtnStatePrev = KMAP_boEncoderLeftPushBtnStateNow;
    KMAP__boEncoderRightPushBtnStatePrev = KMAP_boEncoderRightPushBtnStateNow;
    KMAP__boEncoderMainPushBtnStatePrev = KMAP_boEncoderMainPushBtnStateNow;

    /* if Both Buttons are pressed for 1000ms, reset the keypad */
    if(KMAP_boEncoderLeftPushBtnStateNow == false && KMAP_boEncoderRightPushBtnStateNow == false)
    {
        wait_ms(1000);
        //check again the buttons press value
        KMAP_boEncoderLeftPushBtnStateNow = readPin(ENCODER_LEFT_PUSH_BUTTON_PIN);
        KMAP_boEncoderRightPushBtnStateNow = readPin(ENCODER_RIGHT_PUSH_BUTTON_PIN);
        if(KMAP_boEncoderLeftPushBtnStateNow == false && KMAP_boEncoderRightPushBtnStateNow == false)
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
    uint8_t u8ActiveLayer = SCREEN_u8GetActiveLayer();

    switch (index) {
        case 0: /* left */
            break;

        case 1: /* main, middle */
            /* Encoder can be use for other operations depending on different layer */
            switch(u8ActiveLayer)
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
void raw_hid_receive(uint8_t *u8pData, uint8_t u8Length)
{
    extern int8_t KPAD_i8SoundVolume;
    //uint8_t response[length];
    //memset(response, 0, length);
    //response[0] = 'B';

    /* getting time from host
     * FOrmat : ti123456
    */
    if(u8pData[0] == 't' && u8pData[1] == 'i') {
        //int hr = (u8pData[2] - '0')*10 + (u8pData[3] - '0');
        //int min= (u8pData[4] - '0')*10 + (u8pData[5] - '0');
        //int sec= (u8pData[6] - '0')*10 + (u8pData[7] - '0');
        //clock_update_time(hr, min,sec);
        //raw_hid_send(response, length);
    }
    if(u8pData[0] == 'c' && u8pData[1] == 'p')
    {
        //int cpu_res_in_percent = (u8pData[2] - '0') * 100 + (u8pData[3] - '0') * 10 + (u8pData[4] - '0');
        //cpu_resource_set_value(cpu_res_in_percent);
    }
    if(u8pData[0] == 'v' && u8pData[1] == 'o' && u8pData[2] == 'l' && u8pData[3] == '_')
    {
        /* speaker volume update to LVGL Arc */
        KPAD_i8SoundVolume = (u8pData[4] - '0') * 100 +
                             (u8pData[5] - '0') * 10  +
                             (u8pData[6] - '0');
        //uprintf("Volume %d\n", KPAD_i8SoundVolume);
        lv_label_set_text_fmt(KPAD_spVolumeLbl, "%03d", KPAD_i8SoundVolume);
        lv_arc_set_value(KPAD_spVolumeObj, KPAD_i8SoundVolume);
        //SCREEN_vChangeLayer(NUMPAD_LAYER);
    }
    if(u8pData[0] == 'a' && u8pData[1] == 'p' && u8pData[2] == 'p' && u8pData[3] == '_')
    {
        uint8_t * app_name = &u8pData[4];
        if(app_name[0] == 't' && app_name[1] == 't' && app_name[2] == 'c')
        {
#ifdef ENABLE_TOTAL_COMMANDER_LAYER
            SCREEN_vChangeLayer(TOTAL_COMMANDER_LAYER);
#endif
        }
        else if(app_name[0] == 'c' && app_name[1] == 'a' && app_name[2] == 'l')
        {
#ifdef ENABLE_NUMPAD_LAYER
            SCREEN_vChangeLayer(NUMPAD_LAYER);
#endif
        }
        else if(app_name[0] == 'v' && app_name[1] == 's' && app_name[2] == 'c')
        {

        }
    }/* end if(u8pData[0] == 'a' && u8pData[1] == 'p' && u8pData[2] == 'p' && u8pData[3] == '_') */
}
