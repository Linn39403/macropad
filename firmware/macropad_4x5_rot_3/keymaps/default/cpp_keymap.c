#include "keymap.h"
#include QMK_KEYBOARD_H
#include "config.h"

#ifdef ENABLE_CPP_LAYER

bool cpplayer_function_key_pressed(uint16_t keycode) {
    switch (keycode) {
        case CPP_KEY_for_loop:
            SEND_STRING("for (int i = 0; i < N; ++i)\n{\n");
        return false;
		case CPP_KEY_while_loop:
            SEND_STRING("while()\n{\n}");
        return false;
		case CPP_KEY_struct:
            SEND_STRING("struct foo \n{\n};");
            return false;
		case CPP_KEY_class:
            SEND_STRING("class foo \n{\npublic:\n\nprivate:\n\nprotected:\n\n};");
            return false;
		case CPP_KEY_switch:
            SEND_STRING("switch (var) \n{\ncase val:\nbreak;\n\ndefault:\nbreak;\n};");
            return false;
		case CPP_KEY_D:
        return false;
		case CPP_KEY_E:
        return false;
		case CPP_KEY_F:
        return false;
		case CPP_KEY_cout:
            SEND_STRING("std::cout << \"\" << std::endl;");
        return false;
		case CPP_KEY_9:
        return false;
		case CPP_KEY_A:
        return false;
		case CPP_KEY_B:
        return false;
		case CPP_KEY_4:
        return false;
		case CPP_KEY_5:
        return false;
		case CPP_KEY_6:
        return false;
		case CPP_KEY_7:
        return false;
		case CPP_KEY_0:
        return false;
		case CPP_KEY_1:
        return false;
		case CPP_KEY_2:
        return false;
		case CPP_KEY_3:
        return false;
        default:
            return false;
    }
}


bool cpplayer_function_key_released(uint16_t keycode)
{
    switch (keycode) {
        default:
            return false;
    }
}

#endif
