#pragma once
#include "lv_obj.h"
#include "quantum_keycodes.h"

enum keyboard_layers_enum{
    OFFICE_LAYER = 0, //media, naviations
    TOTAL_COMMANDER_LAYER = 1,
    NUMPAD_LAYER = 2, //numpad
    CPP_LAYER = 3,
    LAYER_COUNT
};

struct kb_layer_type{
    const char * tab_view_name;
    lv_obj_t * tab_view_obj;
    const char layer;
};

enum office_Keys {
    UIE = SAFE_RANGE, OFFICE_PASSWORD, OFC_KEY_3, OFC_KEY_4,
    OFC_KEY_5, OFC_KEY_6, OFC_KEY_7, OFC_KEY_8,
    OFC_KEY_9, OFC_KEY_10, OFC_KEY_11, OFC_KEY_12,
    OFC_KEY_13, OFC_KEY_14, OFC_KEY_15, OFC_KEY_16,
    RESET_KEY1, RESET_KEY2, OFC_KEY_19, OFC_RELAY_CTRL,
    END_OFFICE_KEYS
};

enum totalCommander_Keys{
    PER_KEY0 = END_OFFICE_KEYS, PER_KEY1, PER_KEY2, PER_KEY3,
    PER_KEY4, PER_KEY5, PER_KEY6, PER_KEY7,
    PER_KEY8, PER_KEY9, PER_KEY10, PER_KEY11,
    PER_KEY12, PER_KEY13, PER_KEY14, PER_KEY15,
    PER_KEY16, PER_KEY17, PER_KEY18, PER_KEY19,
    END_TOTAL_COMMANDER_KEYS
};

enum numpad_Keys{
    NUM_KEY_7_AND_A, NUM_KEY_8_AND_B, NUM_KEY_9_AND_C,
    NUM_KEY_4_AND_D, NUM_KEY_5_AND_E, NUM_KEY_6_AND_F,
};

enum cpp_Keys{
    CPP_KEY_for_loop = END_TOTAL_COMMANDER_KEYS, CPP_KEY_while_loop, CPP_KEY_struct, CPP_KEY_class,
    CPP_KEY_switch, CPP_KEY_D, CPP_KEY_E, CPP_KEY_F,
    CPP_KEY_cout, CPP_KEY_9, CPP_KEY_A, CPP_KEY_B,
    CPP_KEY_4, CPP_KEY_5, CPP_KEY_6, CPP_KEY_7,
    CPP_KEY_0, CPP_KEY_1, CPP_KEY_2, CPP_KEY_3,
    END_CPP_KEYS
};


bool officelayer_function_key_pressed(uint16_t keycode);
bool officelayer_function_key_released(uint16_t keycode);
bool keypad_layer_function_key_pressed(uint16_t keycode);
bool keypad_layer_function_key_released(uint16_t keycode);
bool cpplayer_function_key_pressed(uint16_t keycode);
bool cpplayer_function_key_released(uint16_t keycode);
