#include "config.h"
#include "lvgl.h"
#include "qp.h"
#include "color.h"
#include "keymap.h"


/* home screen content */
static painter_device_t DISP__stDisplay;

void SCREEN_vInit(void);
bool display_init_user(void)
{
    SCREEN_vInit();
    return false;
}

void keyboard_post_init_kb(void)
{
    DISP__stDisplay = qp_st7789_make_spi_device(170, 320, LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN, 4, 3);
    qp_init(DISP__stDisplay, QP_ROTATION_90);
    qp_set_viewport_offsets(DISP__stDisplay, 0, 35);
    qp_power(DISP__stDisplay, 1);

    qp_lvgl_attach(DISP__stDisplay);
    lv_disp_t  *lv_display = lv_disp_get_default();
    lv_theme_t *lv_theme   = lv_theme_default_init(lv_display, lv_palette_main(LV_PALETTE_AMBER), lv_palette_main(LV_PALETTE_BLUE), true, LV_FONT_DEFAULT);
    lv_disp_set_theme(lv_display, lv_theme);
    display_init_user();
}

void display_housekeeping_task(void) {
    //qp_flush(display);
}

__attribute__((weak)) void display_process_caps(bool active) {
}
