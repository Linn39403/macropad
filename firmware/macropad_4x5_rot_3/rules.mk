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
	   screens.c \
	   keymaps/default/GUI_helper.c \
	   keymaps/default/numpad_screen.c \
	   keymaps/default/resource_screen.c \
	   keymaps/default/total_commander_screen.c \
	   keymaps/default/vsc_screen.c \
	   keymaps/default/browser_screen.c \


