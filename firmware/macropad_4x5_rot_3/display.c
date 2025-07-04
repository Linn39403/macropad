#include "config.h"
#include "lvgl.h"
#include "qp.h"
#include "color.h"
#include "keymap.h"
#include "print.h"
#include "keymaps/default/numpad_screen.h"
#include "ringbuffer.h"

//#define LCD_1_9_INCH
#define LCD_2_INCH
/* home screen content */
static painter_device_t DISP__stDisplay;
RingBuffer DISP__stRbufSoundVolume;
void SCREEN_vInit(void);
uint8_t SCREEN_u8GetActiveLayer(void);

enum DISP__enSoundVolumeAniState
{
    enSoundVolumeDefaultState = 0,
    enSoundVolumeAnimationState = 1
};

enum DISP__enSoundVolumeAniState DISP__enSoundVolumeAniState;
#define DISP_nAnimationUpdateFreq  1 //ms
uint16_t DISP__u16AniTimerValue = 0;

static void DISP__vVarInit(void)
{
    RingBuffer_Init(&DISP__stRbufSoundVolume);
    DISP__enSoundVolumeAniState = enSoundVolumeDefaultState;
}

bool display_init_user(void)
{
    DISP__vVarInit();
    SCREEN_vInit();
    return false;
}

void keyboard_post_init_kb(void)
{
    #ifdef LCD_1_9_INCH
    DISP__stDisplay = qp_st7789_make_spi_device(170, 320, LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN, 4, 3);
    #elif defined(LCD_2_INCH)
    DISP__stDisplay = qp_st7789_make_spi_device(240, 320, LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN, 4, 3);
    #endif
    qp_init(DISP__stDisplay, QP_ROTATION_90);
    #ifdef LCD_1_9_INCH
    qp_set_viewport_offsets(DISP__stDisplay, 0, 35);
    #elif defined(LCD_2_INCH)
    qp_set_viewport_offsets(DISP__stDisplay, 0, 0);
    #endif
    qp_power(DISP__stDisplay, 1);

    qp_lvgl_attach(DISP__stDisplay);
    lv_disp_t  *lv_display = lv_disp_get_default();
    lv_theme_t *lv_theme   = lv_theme_default_init(lv_display, lv_palette_main(LV_PALETTE_AMBER), lv_palette_main(LV_PALETTE_BLUE), true, LV_FONT_DEFAULT);
    lv_disp_set_theme(lv_display, lv_theme);
    display_init_user();
}



void housekeeping_task_user(void)
{
    static uint8_t DISP__stSoundVolumeFromFifo;
    uint8_t DISP_stSoundVolumeCurr = lv_arc_get_value(NUMPAD_spVolumeObj);

    switch(DISP__enSoundVolumeAniState)
    {
        case enSoundVolumeDefaultState:
            if(RingBuffer_GetDataLength(&DISP__stRbufSoundVolume))
            {
                RingBuffer_Read(&DISP__stRbufSoundVolume, &DISP__stSoundVolumeFromFifo, 1);
                DISP__enSoundVolumeAniState = enSoundVolumeAnimationState;
                DISP__u16AniTimerValue = timer_read();
            }
        break;

        case enSoundVolumeAnimationState:
            uprintf("VolAniState\n");
            if(timer_elapsed(DISP__u16AniTimerValue) > DISP_nAnimationUpdateFreq)
            {
                //Positive or Negative?
                uint8_t u8DeltaTimeCntPerFreq = timer_elapsed(DISP__u16AniTimerValue);
                u8DeltaTimeCntPerFreq /= DISP_nAnimationUpdateFreq;

                if(DISP_stSoundVolumeCurr > DISP__stSoundVolumeFromFifo)
                {
                    /* Current Showing Value is Greater than update value */
                    if(DISP_stSoundVolumeCurr - u8DeltaTimeCntPerFreq >= DISP__stSoundVolumeFromFifo)
                    {
                        DISP_stSoundVolumeCurr -= u8DeltaTimeCntPerFreq;
                    }
                    else
                    {
                        DISP_stSoundVolumeCurr--;
                    }
                    lv_label_set_text_fmt(NUMPAD_spVolumeLbl, "%03d", DISP_stSoundVolumeCurr);
                    lv_arc_set_value(NUMPAD_spVolumeObj, DISP_stSoundVolumeCurr);
                }
                else if(DISP_stSoundVolumeCurr < DISP__stSoundVolumeFromFifo)
                {
                    /* Currnet Showing Value is Smaller than update value */
                    if(DISP_stSoundVolumeCurr + u8DeltaTimeCntPerFreq <= DISP__stSoundVolumeFromFifo)
                    {
                        DISP_stSoundVolumeCurr += u8DeltaTimeCntPerFreq;
                    }
                    else
                    {
                        DISP_stSoundVolumeCurr++;
                    }
                    lv_label_set_text_fmt(NUMPAD_spVolumeLbl, "%03d", DISP_stSoundVolumeCurr);
                    lv_arc_set_value(NUMPAD_spVolumeObj, DISP_stSoundVolumeCurr);
                }
                else
                {
                    /* Both of them are equal, Go back to Default State */
                    DISP__enSoundVolumeAniState = enSoundVolumeDefaultState;
                }
                DISP__u16AniTimerValue = timer_read();
            }
        break;
        default:
        break;
    }/* end switch(DISP__enSoundVolumeAniState) */

    uint8_t u8CurrentLayer = SCREEN_u8GetActiveLayer();
    switch(u8CurrentLayer)
    {
        #define X X_HOUSEKEEPING
        LAYER_LIST
        #undef X
    }
}

__attribute__((weak)) void display_process_caps(bool active) {
}
