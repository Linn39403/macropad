QUANTUM_PAINTER_DRIVERS += st7789_spi
QUANTUM_PAINTER_LVGL_INTEGRATION = yes
TAP_DANCE_ENABLE = yes
ENCODER_ENABLE = yes
CONSOSLE_ENABLE = yes
MOUSEKEY_ENABLE = yes
RAW_ENABLE = yes
CONSOLE_ENABLE = yes
CFLAGS += -DLV_LVGL_H_INCLUDE_SIMPLE
SRC += display.c \
	   ringbuffer.c \
	   office_keymap.c \
	   screens.c \
	   keymaps/default/GUI_helper.c \
	   keymaps/default/numpad_screen.c \
	   keymaps/default/resource_screen.c \
	   keymaps/default/vsc_screen.c \
	   keymaps/default/total_commander_screen.c \
	   fonts/fa_terminal.c \
	   fonts/fa_search.c \
	   fonts/fa_sort_alpha_asc.c \
	   fonts/fa_sort_amount_asc.c \
	   fonts/fa_angles_34pxl_collection.c \
	   # keymaps/default/total_commander_screen.c \
	   # keymaps/default/vsc_screen.c \
	   # keymaps/default/browser_screen.c \
	   # keymaps/default/funkeys_screen.c \
	   # keymaps/default/win_explorer_screen.c \
	   # keymaps/default/office_screen.c \


