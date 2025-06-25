#define __LOCK_SCREEN_C
#include "lock_screen.h"
#include "print.h"
#include "fonts/fa_font_list.h"

#define UNLOCK_KEY_0 LOCK_KEY_1
#define UNLOCK_KEY_1 LOCK_KEY_0
#define LOCK_KEY_PRESS_TIME 1000UL
#define LOCK_KEY_TIME_OUT   1000*60*60UL
static uint32_t unlock__u32Timer = 0;
static uint16_t unlock__key_press_value = 0;
static lv_obj_t * spLockLabel;
void SCREEN_vSetLock(void);
void SCREEN_vSetUnLock(void);
bool SCREEN_boIsLock(void);
void SCREEN_vChangeLayer(uint8_t u8Layer);
static lv_obj_t * LOCK__spButtonCreate(lv_obj_t* spParentScreen,
                                                  const char * pcText,
                                                  const lv_font_t * font_name,
                                                  GUI_tsBtnLocation * spBtnInfo )
{
    return NULL;
}

void LOCK_vScreenCreate(lv_obj_t * spParentScreen)
{
    GUI_SCREEN_CREATE(LOCK, spParentScreen);

    /* LOCK SCREEN Label */
    spLockLabel = lv_label_create(spParentScreen);
    lv_label_set_text(spLockLabel, FA_LOCK);
    //lv_obj_set_style_text_font(spLockLabel, &lv_font_montserrat_48, LV_PART_MAIN);
    lv_obj_set_style_text_font(spLockLabel, &fa_lock_unlock, LV_PART_MAIN);
    lv_obj_set_style_text_color(spLockLabel, lv_color_hex(0xFF0000), 0);
    lv_obj_align(spLockLabel,LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_align(spLockLabel,LV_ALIGN_CENTER, 0);
    lv_obj_update_layout(spLockLabel);
}

static void LOCK__vLayerGUIStateChange(uint16_t u16KeyCode, LOCK_tpfnvGuiStateFunc pfnStateCb)
{
    /* Do Nothing */
}

/* to change the button pressed animation */
bool LOCK_boKeyPressedCallBackFunction(uint16_t u16KeyCode)
{
    LOCK__vLayerGUIStateChange(u16KeyCode, GUI_vButtonPress);    // Only process valid unlock keys
    if (u16KeyCode != UNLOCK_KEY_0 && u16KeyCode != UNLOCK_KEY_1)
        return false;

    // If no key is currently pressed, store the first unlock key and start timer
    if (unlock__key_press_value == 0) {
        unlock__key_press_value = u16KeyCode;
        unlock__u32Timer = timer_read32();
        return false;
    }

    // If the other unlock key is pressed while locked, unlock
    if (SCREEN_boIsLock()) {
        if ((u16KeyCode == UNLOCK_KEY_0 && unlock__key_press_value == UNLOCK_KEY_1) ||
            (u16KeyCode == UNLOCK_KEY_1 && unlock__key_press_value == UNLOCK_KEY_0)) {
            unlock__key_press_value = 0;
            SCREEN_vSetUnLock();
            print("unlocked\n");
            lv_label_set_text(spLockLabel, FA_UNLOCK);
            lv_obj_set_style_text_color(spLockLabel, lv_color_hex(0x00FF00), 0);
        }
    }
    else if (SCREEN_boIsLock() == false) {
        if ((u16KeyCode == UNLOCK_KEY_0 && unlock__key_press_value == UNLOCK_KEY_1) ||
            (u16KeyCode == UNLOCK_KEY_1 && unlock__key_press_value == UNLOCK_KEY_0)) {
            unlock__key_press_value = 0;
            SCREEN_vSetLock();
            unlock__u32Timer = timer_read32();
            print("locked\n");
            lv_label_set_text(spLockLabel, FA_LOCK);
            lv_obj_set_style_text_color(spLockLabel, lv_color_hex(0xFF0000), 0);
        }
    }
    return false;
}

/* to change the button released animation */
bool LOCK_boKeyReleasedCallBackFunction(uint16_t u16KeyCode)
{
    LOCK__vLayerGUIStateChange(u16KeyCode, GUI_vButtonRelease);
    return false;
}

void LOCK_vRotaryCallBackFunction(bool boClockwise, bool boModeButtonPressed)
{
    /* Do Nothing */
}

void LOCK_vRotaryButtonPressedCallBackFunction(void)
{
    /* Do Nothing */
}

void LOCK_vHouseKeeping(void)
{
    /* Do Nothing */
}

void LOCK_vLockTimerCheck(void)
{
    if(unlock__u32Timer)
    {
        if((unlock__key_press_value == UNLOCK_KEY_0 ||
            unlock__key_press_value == UNLOCK_KEY_1 ) &&
            timer_elapsed32(unlock__u32Timer) > LOCK_KEY_PRESS_TIME )
            {
                /* key press time out !!! */
                unlock__key_press_value = 0;
                print("timeout\n");
            }
        if(SCREEN_boIsLock() == false &&
           timer_elapsed32(unlock__u32Timer) > LOCK_KEY_TIME_OUT )
        {
                SCREEN_vSetLock();
                print("locked\n");
                lv_label_set_text(spLockLabel, FA_LOCK);
                SCREEN_vChangeLayer(0);
                lv_obj_set_style_text_color(spLockLabel, lv_color_hex(0xFF0000), 0);
        }
    }
}
