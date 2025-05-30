#pragma once
#include "config.h"
#include "lv_obj.h"
#include "quantum_keycodes.h"
#include "lvgl/total_commander_screen.h"
#include "lvgl/numpad_screen.h"
#include "lvgl/vsc_screen.h"
#include "lvgl/browser_screen.h"

/* X MACRO */
#define LAYER_LIST\
    X(TOTAL_COMMANDER)\
    X(NUMPAD)\
    X(VSC)\
    X(BROWSER)

enum keyboard_layers_enum{
    #define X(layer) layer##_LAYER,
    LAYER_LIST
    #undef X
    LAYER_COUNT
};

#define X_PRESSED(layer)\
    case layer##_LAYER:\
        return layer##_boKeyPressedCallBackFunction(u16KeyCode);

#define X_RELEASED(layer)\
    case layer##_LAYER:\
        return layer##_boKeyReleasedCallBackFunction(u16KeyCode);

#define X_SCREEN_LAYER(layer)\
    {\
        .m_spScreenObj = NULL,\
        .m_pfnScreenInit = &layer##_vScreenCreate,\
        .m_u8ScreenLayerId = layer##_LAYER\
    },

struct kb_layer_type{
    lv_obj_t * m_spScreenObj;
    const uint8_t m_u8ScreenLayerId;
    void (*m_pfnScreenInit)(lv_obj_t*);
};


