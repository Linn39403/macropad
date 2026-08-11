#define __SPECIAL_SCREEN_C
#include "special_screen.h"

static uint16_t SPECIAL__u16ScreenTimer = 0;


static lv_obj_t * SPECIAL__spButtonCreate(lv_obj_t* spParentScreen,
                                      const char * pcText,
                                      const lv_font_t * font_name,
                                      GUI_tsBtnLocation * spBtnInfo )
{
    return GUI_spButtonCreate(spParentScreen,
                          pcText,
                          font_name,
                          lv_color_hex(0x73FBFD),
                          lv_color_hex(0x000000),
                          spBtnInfo);
}

void SPECIAL_vScreenCreate(lv_obj_t * spParentScreen)
{
    GUI_SCREEN_CREATE(SPECIAL, spParentScreen);

    /* Special Layer Label */
    GUI_spLayerNameCreate(spParentScreen,
                          "Special Screen",
                          &lv_font_montserrat_24);


}

static bool SPECIAL__boLayerGUIStateChange(uint16_t u16KeyCode, bool boKeyPressed, SPECIAL_tpfnvGuiStateFunc pfnStateCb)
{
    //want to optimize this function
    uint8_t u8Index = u16KeyCode - SAFE_RANGE;
    if(u16KeyCode >= SPECIAL_KEY_0 && u16KeyCode <= SPECIAL_KEY_19)
    {
        //SPECIAL__executeKeys(u8Index, boKeyPressed);
        if(boKeyPressed == true)
        {
            switch(u16KeyCode)
            {
                /* Credential shortcuts intentionally disabled. */
            }
        }
        pfnStateCb(SPECIAL_staBtnInfo[u8Index].m_spBtn);
        return false;
    }

    /* Return True -> Let QMK Handle Key Event */
    /* Return False -> User Handle Key Event */
    return true;
}

/* to change the button pressed animation for the keypad screen */
bool SPECIAL_boKeyPressedCallBackFunction(uint16_t u16KeyCode)
{
    return SPECIAL__boLayerGUIStateChange(u16KeyCode, true, GUI_vButtonPress);
}

/* to change the button released animation for the keypad screen */
bool SPECIAL_boKeyReleasedCallBackFunction(uint16_t u16KeyCode)
{
    return SPECIAL__boLayerGUIStateChange(u16KeyCode, false, GUI_vButtonRelease);
}

void SPECIAL_vRotaryCallBackFunction(bool boClockwise)
{

}

void SPECIAL_vStartScreenTimer(void)
{
    SPECIAL__u16ScreenTimer = timer_read();
}

void SPECIAL_vRotaryButtonPressedCallBackFunction(void)
{

}

void SPECIAL_vHouseKeeping(void)
{
    uint8_t KMAP_u8GetStoredLayer(void);
    void SCREEN_vChangeLayer(uint8_t u8Layer);
    if(SPECIAL__u16ScreenTimer && timer_elapsed(SPECIAL__u16ScreenTimer) > 10000)
    {
        SPECIAL__u16ScreenTimer = 0;
        SCREEN_vChangeLayer(KMAP_u8GetStoredLayer());
    }
}
