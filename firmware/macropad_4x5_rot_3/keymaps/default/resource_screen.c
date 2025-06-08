#include <lvgl.h>
// LVGL objects for the clock
static lv_obj_t *hour_label, *minute_label, *second_label;

// Timer callback to update time
void clock_update_time(int hour, int minute, int second)
{
    char buf[3];
    sprintf(buf, "%02d", hour);
    lv_label_set_text(hour_label, buf);
    sprintf(buf, "%02d", minute);
    lv_label_set_text(minute_label, buf);
    sprintf(buf, "%02d", second);
    lv_label_set_text(second_label, buf);
}

//need x, y?
void lvgl_digital_clock_init(lv_obj_t * parent)
{
    //clear the parant screen
    lv_obj_clean(parent);

    // Create a container to hold the clock
    lv_obj_t * clock_container = lv_obj_create(parent);
    lv_obj_set_size(clock_container, 160, 40); // Adjust for your LCD
    lv_obj_align(clock_container, LV_ALIGN_DEFAULT, 0, 0);
    lv_obj_set_style_bg_color(clock_container, lv_color_hex(0x111111), 0); // Black background
    lv_obj_set_style_border_width(clock_container, 1, 0);
    lv_obj_set_flex_flow(clock_container, LV_FLEX_FLOW_ROW); // Horizontal layout
    lv_obj_set_style_pad_all(clock_container, 5, 0); // Padding

    // Create hour label
    hour_label = lv_label_create(clock_container);
    lv_label_set_text(hour_label, "00");
    lv_obj_set_style_text_font(hour_label, &lv_font_montserrat_24, 0);
    lv_obj_set_style_text_color(hour_label, lv_color_hex(0xFFFFFF), 0);

    // Colon separator
    lv_obj_t *colon1 = lv_label_create(clock_container);
    lv_label_set_text(colon1, ":");
    lv_obj_set_style_text_font(colon1, &lv_font_montserrat_24, 0);
    lv_obj_set_style_text_color(colon1, lv_color_hex(0xFFFFFF), 0);

    // Create minute label
    minute_label = lv_label_create(clock_container);
    lv_label_set_text(minute_label, "00");
    lv_obj_set_style_text_font(minute_label, &lv_font_montserrat_24, 0);
    lv_obj_set_style_text_color(minute_label, lv_color_hex(0xFFFFFF), 0);

    // Colon separator
    lv_obj_t *colon2 = lv_label_create(clock_container);
    lv_label_set_text(colon2, ":");
    lv_obj_set_style_text_font(colon2, &lv_font_montserrat_24, 0);
    lv_obj_set_style_text_color(colon2, lv_color_hex(0xFFFFFF), 0);

    // Create second label
    second_label = lv_label_create(clock_container);
    lv_label_set_text(second_label, "00");
    lv_obj_set_style_text_font(second_label, &lv_font_montserrat_24, 0);
    lv_obj_set_style_text_color(second_label, lv_color_hex(0xFFFFFF), 0);

    // Create a timer to update the clock every second
    //lv_timer_create(clock_update_cb, TIME_UPDATE_INTERVAL, NULL);
}

static lv_obj_t * cpu_meter;
static lv_meter_indicator_t * cpu_indic;

void cpu_resource_set_value(int32_t v)
{
    lv_meter_set_indicator_value(cpu_meter, cpu_indic, v);
}

/**
 * A simple cpu_meter
 */
void lvgl_cpu_meter_init(lv_obj_t * parent)
{
    cpu_meter = lv_meter_create(parent);
    lv_obj_center(cpu_meter);
    lv_obj_set_size(cpu_meter, 130, 130);

    /*Add a scale first*/
    lv_meter_scale_t * scale = lv_meter_add_scale(cpu_meter);
    lv_meter_set_scale_ticks(cpu_meter, scale, 41, 2, 10, lv_palette_main(LV_PALETTE_GREY));
    lv_meter_set_scale_major_ticks(cpu_meter, scale, 8, 4, 15, lv_color_black(), 10);

    /*Add a blue arc to the start*/
    cpu_indic = lv_meter_add_arc(cpu_meter, scale, 3, lv_palette_main(LV_PALETTE_BLUE), 0);
    lv_meter_set_indicator_start_value(cpu_meter, cpu_indic, 0);
    lv_meter_set_indicator_end_value(cpu_meter, cpu_indic, 20);

    /*Make the tick lines blue at the start of the scale*/
    cpu_indic = lv_meter_add_scale_lines(cpu_meter, scale, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_BLUE), false, 0);
    lv_meter_set_indicator_start_value(cpu_meter, cpu_indic, 0);
    lv_meter_set_indicator_end_value(cpu_meter, cpu_indic, 20);

    /*Add a red arc to the end*/
    cpu_indic = lv_meter_add_arc(cpu_meter, scale, 3, lv_palette_main(LV_PALETTE_RED), 0);
    lv_meter_set_indicator_start_value(cpu_meter, cpu_indic, 80);
    lv_meter_set_indicator_end_value(cpu_meter, cpu_indic, 100);

    /*Make the tick lines red at the end of the scale*/
    cpu_indic = lv_meter_add_scale_lines(cpu_meter, scale, lv_palette_main(LV_PALETTE_RED), lv_palette_main(LV_PALETTE_RED), false, 0);
    lv_meter_set_indicator_start_value(cpu_meter, cpu_indic, 80);
    lv_meter_set_indicator_end_value(cpu_meter, cpu_indic, 100);

    /*Add a needle line indicator*/
    cpu_indic = lv_meter_add_needle_line(cpu_meter, scale, 4, lv_palette_main(LV_PALETTE_GREY), -10);
#if 0
    /*Create an animation to set the value*/
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_exec_cb(&a, set_value);
    lv_anim_set_var(&a, indic);
    lv_anim_set_values(&a, 0, 100);
    lv_anim_set_time(&a, 2000);
    lv_anim_set_repeat_delay(&a, 100);
    lv_anim_set_playback_time(&a, 500);
    lv_anim_set_playback_delay(&a, 100);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&a);
    #endif
}
