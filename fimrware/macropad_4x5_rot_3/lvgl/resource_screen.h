
void lvgl_digital_clock_init(lv_obj_t * clock_container);
void clock_update_time(int hour, int minute, int second);

void lvgl_cpu_meter_init(lv_obj_t * parent);
void cpu_resource_set_value(int32_t v);
