QUANTUM_PAINTER_DRIVERS += st7789_spi
QUANTUM_PAINTER_LVGL_INTEGRATION = yes
TAP_DANCE_ENABLE = yes
ENCODER_ENABLE = yes
CONSOSLE_ENABLE = yes
MOUSEKEY_ENABLE = yes
SRC += lvgl_helpers.c \
	   display.c \
	   office_keymap.c \
	   keypad_keymap.c \
	   cpp_keymap.c \
	   lvgl/ui.c \
	   lvgl/images.c \
	   lvgl/screens.c \
	   lvgl/styles.c \
	   lvgl/keypad_screen.c \

