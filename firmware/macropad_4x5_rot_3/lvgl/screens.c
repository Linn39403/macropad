#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"
#include <string.h>
#include "keymap.h"
#include "resource_screen.h"
#include "keypad_screen.h"

objects_t objects;
lv_obj_t *tab_view;


struct kb_layer_type kb_layers[LAYER_COUNT] =
{
    {"office", NULL, OFFICE_LAYER},
    {"total_com", NULL, TOTAL_COMMANDER_LAYER},
    {"numpad", NULL, NUMPAD_LAYER},
    {"cpp", NULL, CPP_LAYER},
    {"resource", NULL, RESOURCE_LAYER},
};

#define TAB_VIEW_OFFICE           kb_layers[OFFICE_LAYER].tab_view_obj
#define TAB_VIEW_TOTAL_COMMANDER  kb_layers[TOTAL_COMMANDER_LAYER].tab_view_obj
#define TAB_VIEW_NUMPAD           kb_layers[NUMPAD_LAYER].tab_view_obj
#define TAB_VIEW_CPP              kb_layers[CPP_LAYER].tab_view_obj
#define TAB_VIEW_RESOURCE         kb_layers[RESOURCE_LAYER].tab_view_obj

void create_screen_main(void) {
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 170);
    {
        //create a tab view obj
        lv_obj_t *parent_obj = obj;
        {
            tab_view = lv_tabview_create(parent_obj, LV_DIR_TOP, 0);
            //lv_obj_set_pos(tab_view, 0, 0);
            //lv_obj_set_size(tab_view, 320, 170);

            TAB_VIEW_OFFICE = lv_tabview_add_tab(tab_view, kb_layers[OFFICE_LAYER].tab_view_name);
            TAB_VIEW_TOTAL_COMMANDER = lv_tabview_add_tab(tab_view, kb_layers[TOTAL_COMMANDER_LAYER].tab_view_name);
            TAB_VIEW_NUMPAD = lv_tabview_add_tab(tab_view, kb_layers[NUMPAD_LAYER].tab_view_name);
            TAB_VIEW_CPP = lv_tabview_add_tab(tab_view, kb_layers[CPP_LAYER].tab_view_name);
            TAB_VIEW_RESOURCE = lv_tabview_add_tab(tab_view, kb_layers[RESOURCE_LAYER].tab_view_name);


            /**************************************************************************/
            /* Create matrix button GUI for the Personal layout */
            static const char * office_map[] =
                                   {"uie", "pwd", "uieCon", "door", "\n",
                                    ".", ".", ".", ".", "\n",
                                    ".", ".", ".", ".", "\n",
                                    ".", ".", ".", ".", "\n",
                                    "rst1", "rst2", "2", ".", "\n",
                                    "" //termination element
                                    };

            lv_obj_t * office_matrix = lv_btnmatrix_create(TAB_VIEW_OFFICE);
            lv_btnmatrix_set_map(office_matrix, office_map);
            lv_obj_align(office_matrix, LV_ALIGN_CENTER, 0, 0);

            lv_obj_set_style_bg_color(TAB_VIEW_OFFICE, lv_palette_lighten(LV_PALETTE_BLUE,3),0);
            lv_obj_set_style_bg_opa(TAB_VIEW_OFFICE, LV_OPA_COVER, 0);
            /**************************************************************************/
            /* Create matrix button GUI for the Numpad layout */
            lv_keypad_screen_create(TAB_VIEW_NUMPAD);

            /**************************************************************************/
            /* Create matrix button GUI for the TotalCommander Layout */
            static const char * tc_map[] =
                                   {"rename", "prop", "newf*", "root", "\n",
                                    "newtab", "clstab", "tabchg", "swt tab", "\n",
                                    "S_name", "S_ext", "S_time", "S_size", "\n",
                                    ".", ".", ".", ".", "\n",
                                    ".", ".", ".", ".", "\n",
                                    "" //termination element
                                    };
            lv_obj_t * tc_matrix = lv_btnmatrix_create(TAB_VIEW_TOTAL_COMMANDER);
            lv_btnmatrix_set_map(tc_matrix, tc_map);

            static lv_style_t style_btnmatrix;
            lv_style_init(&style_btnmatrix);
            lv_style_set_min_height(&style_btnmatrix, 30);
            lv_obj_add_style(tc_matrix, &style_btnmatrix, LV_BTNMATRIX_DRAW_PART_BTN);

            lv_obj_align(tc_matrix, LV_ALIGN_CENTER, 0, 0);
            lv_obj_set_style_bg_color(TAB_VIEW_TOTAL_COMMANDER, lv_palette_lighten(LV_PALETTE_GREEN,3),0);
            lv_obj_set_style_bg_opa(TAB_VIEW_TOTAL_COMMANDER, LV_OPA_COVER, 0);

            /**************************************************************************/
            /* Create matrix button GUI for the CPP Layout */
            static const char * cpp_map[] =
                                   {"for", "while", "struct", "class", "\n",
                                    "switch", "D", "E", "F", "\n",
                                    "cout", "9", "A", "B", "\n",
                                    "4", "5", "6", "7", "\n",
                                    "0", "1", "2", "3", "\n",
                                    "" //termination element
                                    };
            lv_obj_t * cpp_matrix = lv_btnmatrix_create(TAB_VIEW_CPP);
            lv_btnmatrix_set_map(cpp_matrix, cpp_map);
            lv_obj_align(cpp_matrix, LV_ALIGN_CENTER, 0, 0);

            lv_obj_set_style_bg_color(TAB_VIEW_CPP, lv_palette_lighten(LV_PALETTE_RED,3),0);
            lv_obj_set_style_bg_opa(TAB_VIEW_CPP, LV_OPA_COVER, 0);

            /**************************************************************************/
            /* Create tab view for the Resource Layer */
            //lvgl_digital_clock_init(TAB_VIEW_RESOURCE);
            lvgl_cpu_meter_init(TAB_VIEW_RESOURCE);
        }
    }
}




void tick_screen_main(void) {
}


void create_screens(void) {
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_GREEN), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);

    create_screen_main();
}

typedef void (*tick_screen_func_t)(void);

tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
};

void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
