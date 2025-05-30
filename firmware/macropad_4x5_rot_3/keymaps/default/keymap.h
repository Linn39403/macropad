#pragma once
#include "config.h"
#include "lv_obj.h"
#include "quantum_keycodes.h"
#include "lvgl/total_commander_screen.h"
#include "lvgl/keypad_screen.h"
#include "lvgl/vsc_screen.h"
#include "lvgl/browser_screen.h"

enum keyboard_layers_enum{
#ifdef ENABLE_HOME_SCREEN_LAYER
    HOME_SCREEN_LAYER , //media, naviations
#endif

#ifdef ENABLE_TOTAL_COMMANDER_LAYER
    TOTAL_COMMANDER_LAYER ,
#endif

#ifdef ENABLE_NUMPAD_LAYER
    NUMPAD_LAYER , //numpad
#endif

#ifdef ENABLE_VSC_LAYER
    VSC_LAYER ,
#endif

#ifdef ENABLE_BROWSER_LAYER
    BROWSER_LAYER ,
#endif

#ifdef ENABLE_RESOURCE_LAYER
    RESOURCE_LAYER ,
#endif

    LAYER_COUNT
};


/* X MACRO */
#define LAYER_LIST\
    X(TOTAL_COMMANDER)\
    X(NUMPAD)\
    X(VSC)\
    X(BROWSER)

#define X_PRESSED(layer)\
    case layer##_LAYER:\
        return layer##_boKeyPressedCallBackFunction(u16KeyCode);

#define X_RELEASED(layer)\
    case layer##_LAYER:\
        return layer##_boKeyReleasedCallBackFunction(u16KeyCode);

struct kb_layer_type{
    lv_obj_t * m_spScreenObj;
    const uint8_t m_u8ScreenLayerId;
    void (*m_pfnScreenInit)(lv_obj_t*);
};

#ifdef ENABLE_HOME_SCREEN_LAYER
enum office_Keys {
    UIE = SAFE_RANGE, OFFICE_PASSWORD, OFC_KEY_3, OFC_KEY_4,
    OFC_KEY_5, OFC_KEY_6, OFC_KEY_7, OFC_KEY_8,
    OFC_KEY_9, OFC_KEY_10, OFC_KEY_11, OFC_KEY_12,
    OFC_KEY_13, OFC_KEY_14, OFC_KEY_15, OFC_KEY_16,
    RESET_KEY1, RESET_KEY2, OFC_KEY_19, OFC_RELAY_CTRL,
    END_OFFICE_KEYS
};
#endif



bool officelayer_function_key_pressed(uint16_t keycode);
bool officelayer_function_key_released(uint16_t keycode);

