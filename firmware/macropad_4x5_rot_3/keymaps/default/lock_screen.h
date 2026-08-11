#pragma once

#include "GUI_helper.h"
#include QMK_KEYBOARD_H
#include "fonts/fa_font_list.h"

/* Physical keys are numbered left-to-right, top-to-bottom: 1 through 20. */
#define LOCK_KEY_0     KC_A
#define LOCK_KEY_1     KC_B
#define LOCK_KEY_2     KC_C
#define LOCK_KEY_3     KC_D
#define LOCK_KEY_4     KC_E
#define LOCK_KEY_5     KC_F
#define LOCK_KEY_6     KC_G
#define LOCK_KEY_7     KC_H
#define LOCK_KEY_8     KC_I
#define LOCK_KEY_9     KC_J
#define LOCK_KEY_10    KC_K
#define LOCK_KEY_11    KC_L
#define LOCK_KEY_12    KC_M
#define LOCK_KEY_13    KC_O
#define LOCK_KEY_14    KC_P
#define LOCK_KEY_15    KC_Q
#define LOCK_KEY_16    KC_R
#define LOCK_KEY_17    KC_S
#define LOCK_KEY_18    KC_T
#define LOCK_KEY_19    KC_U

#define LOCK_PIN_LENGTH          4U
#define LOCK_PIN_MAGIC_LENGTH    8U
#define LOCK_PIN_MAGIC_BYTES     {'M', 'P', 'L', 'O', 'C', 'K', '0', '1'}
#define LOCK_PIN_VERSION         1U
#define LOCK_PIN_GUARD_0         0xA5U
#define LOCK_PIN_GUARD_1         0x5AU
#define LOCK_PIN_GUARD_2         0xC3U

/* This record is intentionally patched in the generated UF2 by the host tool. */
typedef struct __attribute__((packed)) {
    uint8_t m_au8Magic[LOCK_PIN_MAGIC_LENGTH];
    uint8_t m_u8Version;
    uint8_t m_au8Pin[LOCK_PIN_LENGTH];
    uint8_t m_u8Checksum;
    uint8_t m_au8Guard[3];
} LOCK_tsPinRecord;

void LOCK_vScreenCreate(lv_obj_t *);
bool LOCK_boKeyPressedCallBackFunction(uint16_t);
bool LOCK_boKeyReleasedCallBackFunction(uint16_t);
void LOCK_vRotaryCallBackFunction(bool boClockwise);
void LOCK_vRotaryButtonPressedCallBackFunction(void);
void LOCK_vHouseKeeping(void);
