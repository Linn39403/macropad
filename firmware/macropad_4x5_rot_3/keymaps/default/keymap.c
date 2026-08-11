#include "keymap.h"
#include QMK_KEYBOARD_H
#include "config.h"
#include "print.h"
#include "keymaps/default/numpad_screen.h"
#include "ringbuffer.h"

static uint8_t KMAP_u8StoreCurrentLayer = -1;
extern RingBuffer DISP__stRbufSoundVolume;
extern struct kb_layer_type kb_layers[LAYER_COUNT];
uint8_t SCREEN_u8GetActiveLayer(void);
void SCREEN_vChangeLayer(uint16_t kb_layer_index);
void SCREEN_vChangeToSpecialLayer(void);
bool SCREEN_boIsLock(void);
void SPECIAL_vStartScreenTimer(void);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    #define X X_QMK_KEYS_LAYER
        LAYER_LIST
    #undef X
};

void keyboard_pre_init_user(void)
{
    gpio_set_pin_input_high(ENCODER_LEFT_PUSH_BUTTON_PIN);
    gpio_set_pin_input_high(ENCODER_MAIN_PUSH_BUTTON_PIN);
    gpio_set_pin_input_high(ENCODER_RIGHT_PUSH_BUTTON_PIN);
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
            #define X X_PRESSED
            LAYER_LIST
            #undef X
        }/*end switch (u8CurrentLayer)*/
    }/*end if(spRecord->event.pressed)*/

    /* Button Released */
    if (!spRecord->event.pressed)
    {
        switch(u8CurrentLayer)
        {
            #define X X_RELEASED
            LAYER_LIST
            #undef X
        }/*end switch(u8CurrentLayer)*/
    }/*end if (!spRecord->event.pressed)*/
    return false;
}

void matrix_scan_user(void)
{
    static bool KMAP__boEncoderRightPushBtnStatePrev = false;
    static bool KMAP__boEncoderMainPushBtnStatePrev = false;

    bool KMAP_boEncoderLeftPushBtnStateNow = gpio_read_pin(ENCODER_LEFT_PUSH_BUTTON_PIN);
    bool KMAP_boEncoderRightPushBtnStateNow = gpio_read_pin(ENCODER_RIGHT_PUSH_BUTTON_PIN);
    bool KMAP_boEncoderMainPushBtnStateNow = gpio_read_pin(ENCODER_MAIN_PUSH_BUTTON_PIN);

    uint8_t u8ActiveLayer = SCREEN_u8GetActiveLayer();

    if((KMAP_boEncoderMainPushBtnStateNow == false) &&
       (KMAP_boEncoderMainPushBtnStateNow != KMAP__boEncoderMainPushBtnStatePrev))
    {
        /* Main Encoder Button Pressed */
        switch(u8ActiveLayer)
        {
            #define X X_ROTARY_BTN_PRESSED
            LAYER_LIST
            #undef X
            default:
            break;
        }
    }

    /* Right Side Push Button Read */
    if((KMAP_boEncoderRightPushBtnStateNow == false) &&
       (KMAP_boEncoderRightPushBtnStateNow != KMAP__boEncoderRightPushBtnStatePrev))
    {
        wait_ms(100);
        if(SCREEN_boIsLock() == false)
        {
            if(++u8ActiveLayer >= LAYER_COUNT - 1)
            {
                /* when the screen is unlock, don't show again the lock layer */
                u8ActiveLayer = 1;
            }
            SCREEN_vChangeLayer(u8ActiveLayer);
        }
    }

    KMAP__boEncoderRightPushBtnStatePrev = KMAP_boEncoderRightPushBtnStateNow;
    KMAP__boEncoderMainPushBtnStatePrev = KMAP_boEncoderMainPushBtnStateNow;

    /* if Both Buttons are pressed for 1000ms, reset the keypad */
    if(KMAP_boEncoderLeftPushBtnStateNow == false && KMAP_boEncoderRightPushBtnStateNow == false)
    {
        wait_ms(1000);
        //check again the buttons press value
        KMAP_boEncoderLeftPushBtnStateNow = gpio_read_pin(ENCODER_LEFT_PUSH_BUTTON_PIN);
        KMAP_boEncoderRightPushBtnStateNow = gpio_read_pin(ENCODER_RIGHT_PUSH_BUTTON_PIN);
        if(KMAP_boEncoderLeftPushBtnStateNow == false && KMAP_boEncoderRightPushBtnStateNow == false)
        {
            reset_keyboard();
        }
    }
    /* if only left button is pressed, we need to show the special screen only when the screen is unlocked */
    else if(KMAP_boEncoderLeftPushBtnStateNow == false && SCREEN_boIsLock() == false)
    {
        wait_ms(200);
        if(KMAP_boEncoderLeftPushBtnStateNow == false)
        {
            print("Change to Special Layer\n");
            KMAP_u8StoreCurrentLayer = u8ActiveLayer;
            SPECIAL_vStartScreenTimer();
            SCREEN_vChangeToSpecialLayer();
        }
    }
}

uint8_t KMAP_u8GetStoredLayer(void)
{
    return KMAP_u8StoreCurrentLayer;
}

/* This Encoder Update User function is only called when user rotate the knob.
   If you pressed the button, this function won't be called.
*/
bool encoder_update_user(uint8_t index, bool clockwise)
{
    uint8_t u8ActiveLayer = SCREEN_u8GetActiveLayer();
    switch (index) {
        case 1: /*  middle */
            /* Encoder can be use for other operations depending on different layer */
            switch(u8ActiveLayer)
            {
                #define X X_ROTARY_ROTATE
                LAYER_LIST
                #undef X
            }
            return false;
        default:
            return false;
    }
    return true;
}

#include "raw_hid.h"
void raw_hid_receive(uint8_t *u8pData, uint8_t u8Length)
{
    if (u8Length < 4) {
        return;
    }

    extern int8_t NUMPAD_i8SoundVolume;
    typedef struct {
        const char * m_cpCmd;
        uint16_t m_u16Layer;
    } CmdMap;
    static const CmdMap mapping[] =
    {
        { "ttc", TOTAL_COMMANDER_LAYER },
        { "cal", NUMPAD_LAYER },
        { "vsc", VSC_LAYER},
        { "bwr", BROWSER_LAYER},
        { "exp", WIN_EXPLORER_LAYER},
    };
    /* `rst_` enters the RP2040 UF2 bootloader, even when the screen is locked. */
    if(memcmp(&u8pData[0], "rst_", 4) == 0)
    {
        reset_keyboard();
        return;
    }

    /* If the screen is locked, just return it. */
    if(SCREEN_boIsLock()) return;

    if(memcmp(&u8pData[0], "vol_", 4) == 0)
    {
        /* speaker volume update to LVGL Arc */
        NUMPAD_i8SoundVolume = (u8pData[4] - '0') * 100 +
                             (u8pData[5] - '0') * 10  +
                             (u8pData[6] - '0');
        RingBuffer_Write(&DISP__stRbufSoundVolume, (uint8_t *)&NUMPAD_i8SoundVolume, 1);
    }
    if(memcmp(&u8pData[0], "app_", 4) == 0)
    {
        for (uint8_t i = 0; i < sizeof(mapping)/sizeof(mapping[0]); i++)
        {
            if(memcmp(&u8pData[4], mapping[i].m_cpCmd, 3) == 0) {
                SCREEN_vChangeLayer(mapping[i].m_u16Layer);
            break;
            }
        }
    }
}
