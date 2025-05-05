// Copyright 2023 zzeneg (@zzeneg)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "display.h"
#include "config.h"
#include "lvgl.h"
#include "qp.h"
#include "lvgl_helpers.h"
#include "color.h"
#include "keymap.h"

/* shared styles */
lv_style_t style_screen;
lv_style_t style_container;
lv_style_t style_button;
lv_style_t style_button_active;

/* screens */
static lv_obj_t *screen_home;

/* home screen content */
painter_device_t display;

void init_styles(void) {
    lv_style_init(&style_screen);
    lv_style_set_bg_color(&style_screen, lv_color_black());

    lv_style_init(&style_container);
    lv_style_set_pad_top(&style_container, 0);
    lv_style_set_pad_bottom(&style_container, 0);
    lv_style_set_pad_left(&style_container, 0);
    lv_style_set_pad_right(&style_container, 0);
    lv_style_set_bg_opa(&style_container, 0);
    lv_style_set_border_width(&style_container, 0);
    lv_style_set_width(&style_container, lv_pct(100));
    lv_style_set_height(&style_container, LV_SIZE_CONTENT);

    lv_style_init(&style_button);
    lv_style_set_pad_top(&style_button, 4);
    lv_style_set_pad_bottom(&style_button, 4);
    lv_style_set_pad_left(&style_button, 4);
    lv_style_set_pad_right(&style_button, 4);
    lv_style_set_radius(&style_button, 6);
    lv_style_set_text_color(&style_button, lv_palette_main(LV_PALETTE_AMBER));

    lv_style_init(&style_button_active);
    lv_style_set_bg_color(&style_button_active, lv_palette_main(LV_PALETTE_AMBER));
    lv_style_set_bg_opa(&style_button_active, LV_OPA_100);
    lv_style_set_text_color(&style_button_active, lv_color_black());
}

void init_screen_home(void) {
    screen_home = lv_scr_act();

    lv_obj_add_style(screen_home, &style_screen, 0);
    use_flex_column(screen_home);

    //lv_obj_t *mods = lv_obj_create(screen_home);
    //lv_obj_add_style(mods, &style_container, 0);
    //use_flex_column(mods);

    //lv_obj_t *mods_row2 = lv_obj_create(mods);
    //lv_obj_add_style(mods_row2, &style_container, 0);
    //use_flex_row(mods_row2);
    //label_ctrl  = create_button(mods_row2, "CTL", &style_button, &style_button_active);
    //label_shift = create_button(mods_row2, "SFT", &style_button, &style_button_active);

    lv_obj_t *label_locked = lv_label_create(screen_home);
    lv_label_set_text(label_locked, "LOCKED");

    static lv_style_t style_locked_text;
    lv_style_init(&style_locked_text);
    lv_style_set_text_color(&style_locked_text, lv_color_hex(0xff0000));
    lv_obj_add_style(label_locked, &style_locked_text, 0);
    lv_obj_align(label_locked, LV_ALIGN_CENTER, 0, 0);

#if LV_FONT_MONTSERRAT_48
    lv_obj_set_style_text_font(label_locked, &lv_font_montserrat_48, LV_PART_MAIN);
#endif

}
#include "lvgl/ui.h"
void keyboard_post_init_kb(void)
{
    display = qp_st7789_make_spi_device(170, 320, LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN, 4, 3);
    //painter_device_t display = qp_st7789_make_spi_device(240, 320, LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN, 16, 3);
    qp_init(display, QP_ROTATION_90);
    qp_set_viewport_offsets(display, 0, 35);
    qp_power(display, 1);

    qp_lvgl_attach(display);
    lv_disp_t  *lv_display = lv_disp_get_default();
    lv_theme_t *lv_theme   = lv_theme_default_init(lv_display, lv_palette_main(LV_PALETTE_AMBER), lv_palette_main(LV_PALETTE_BLUE), true, LV_FONT_DEFAULT);
    lv_disp_set_theme(lv_display, lv_theme);
    init_styles();
    ui_init();
}

__attribute__((weak)) bool display_init_user(void) {
    return true;
}

void display_housekeeping_task(void) {
    qp_flush(display);
}

__attribute__((weak)) void display_process_caps(bool active) {
}
