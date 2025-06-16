#include "keymap.h"
#include QMK_KEYBOARD_H
#include "config.h"
#include "print.h"
#include "keymaps/default/numpad_screen.h"
#include "ringbuffer.h"

bool is_locked = false;
extern RingBuffer DISP__stRbufSoundVolume;
extern struct kb_layer_type kb_layers[LAYER_COUNT];
uint8_t SCREEN_u8GetActiveLayer(void);
void SCREEN_vChangeLayer(uint16_t kb_layer_index);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    #define X X_QMK_KEYS_LAYER
        LAYER_LIST
    #undef X
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
        if(++u8ActiveLayer >= LAYER_COUNT)
        {
            u8ActiveLayer = 0;
        }
        SCREEN_vChangeLayer(u8ActiveLayer);
    }

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
    bool boEncoderLeftPushBtnStateNow = readPin(ENCODER_LEFT_PUSH_BUTTON_PIN);

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
    extern int8_t NUMPAD_i8SoundVolume;
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
        if(memcmp(&u8pData[4], "ttc", 3) == 0)
        {
            SCREEN_vChangeLayer(TOTAL_COMMANDER_LAYER);
        }
        else if(memcmp(&u8pData[4], "cal", 3) == 0)
        {
            //SCREEN_vChangeLayer(NUMPAD_LAYER);
        }
        else if(memcmp(&u8pData[4], "vsc", 3) == 0)
        {
            SCREEN_vChangeLayer(VSC_LAYER);
        }
        else if(memcmp(&u8pData[4], "bwr", 3) == 0)
        {
           // SCREEN_vChangeLayer(BROWSER_LAYER);
        }
   }
}
