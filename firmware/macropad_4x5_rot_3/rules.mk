QUANTUM_PAINTER_DRIVERS += st7789_spi
QUANTUM_PAINTER_LVGL_INTEGRATION = yes
TAP_DANCE_ENABLE = yes
ENCODER_ENABLE = yes
CONSOSLE_ENABLE = yes
MOUSEKEY_ENABLE = yes
RAW_ENABLE = yes
CONSOLE_ENABLE = yes
SRC += display.c \
	   ringbuffer.c \
	   office_keymap.c \
	   lvgl/screens.c \
	   lvgl/GUI_helper.c \
	   lvgl/numpad_screen.c \
	   lvgl/resource_screen.c \
	   lvgl/total_commander_screen.c \
	   lvgl/vsc_screen.c \
	   lvgl/browser_screen.c \


