#include <string.h>
#include "screens.h"
#include "fonts.h"
#include "actions.h"
#include <string.h>
#include "keymap.h"
#include "resource_screen.h"
#include "keypad_screen.h"
#include "total_commander_screen.h"
#include "lvgl_helpers.h"
#include "config.h"

// /objects_t objects;
lv_obj_t *tab_view;
static uint16_t kb_current_active_layer = 0;
struct kb_layer_type kb_layers[LAYER_COUNT] =
{
#ifdef ENABLE_RESOURCE_LAYER
    {
     .screen_obj = NULL,
     .screen_layer_id = HOME_SCREEN_LAYER},
#endif
#ifdef ENABLE_TOTAL_COMMANDER_LAYER
    {
     .screen_obj = NULL,
     .screen_init_fptr = &lv_tc_screen_create,
     .screen_layer_id = TOTAL_COMMANDER_LAYER},
#endif
#ifdef ENABLE_NUMPAD_LAYER
    {
     .screen_obj = NULL,
     .screen_init_fptr = &lv_keypad_screen_create,
     .screen_layer_id = NUMPAD_LAYER},
#endif
#ifdef ENABLE_CPP_LAYER
    {
     .screen_obj = NULL,
     .screen_layer_id = CPP_LAYER},
#endif
#ifdef ENABLE_RESOURCE_LAYER
    {
     .screen_obj = NULL,
     .screen_layer_id = RESOURCE_LAYER},
#endif
};

#ifdef ENABLE_RESOURCE_LAYER
#define TAB_VIEW_OFFICE           kb_layers[HOME_SCREEN_LAYER].tab_view_obj
#endif

#ifdef ENABLE_TOTAL_COMMANDER_LAYER
#define TAB_VIEW_TOTAL_COMMANDER  kb_layers[TOTAL_COMMANDER_LAYER].tab_view_obj
#endif

#ifdef ENABLE_NUMPAD_LAYER
#define TAB_VIEW_NUMPAD           kb_layers[NUMPAD_LAYER].tab_view_obj
#endif

#ifdef ENABLE_CPP_LAYER
#define TAB_VIEW_CPP              kb_layers[CPP_LAYER].tab_view_obj
#endif

#ifdef ENABLE_RESOURCE_LAYER
#define TAB_VIEW_RESOURCE         kb_layers[RESOURCE_LAYER].tab_view_obj
#endif

uint16_t get_active_kb_layer(void)
{
    return kb_layers[kb_current_active_layer].screen_layer_id;
}

void set_kb_layer(uint16_t kb_layer_index)
{
    if(kb_layer_index < LAYER_COUNT)
    {
        kb_current_active_layer = kb_layer_index;
        lv_scr_load(kb_layers[kb_current_active_layer].screen_obj);
    }
}

void init_screen_home(void)
{
#if 0
    #define HOME_SCR_ST kb_layers[HOME_SCREEN_LAYER]
    HOME_SCR_ST.screen_obj = lv_scr_act();
    if(HOME_SCR_ST.screen_obj != NULL)
    {
        lv_style_init(&HOME_SCR_ST.screen_style);
        lv_style_set_bg_color(&HOME_SCR_ST.screen_style, lv_color_black());

        lv_obj_add_style(HOME_SCR_ST.screen_obj, &HOME_SCR_ST.screen_style, 0);
        //[TODO] will add flex feature later
        use_flex_row(HOME_SCR_ST.screen_obj);

        lv_obj_t *btn1 = lv_btn_create(HOME_SCR_ST.screen_obj);
        lv_obj_set_size(btn1, 50, 25);
        lv_obj_align(btn1, LV_ALIGN_DEFAULT, 100, 100);

        lv_obj_t* label_btn1 = lv_label_create(btn1);
        lv_label_set_text(label_btn1, "TEST");
        lv_obj_center(label_btn1);
    }
#endif
    #define HOME_SCR_ST kb_layers[NUMPAD_LAYER]
    #define TC_SCR_ST   kb_layers[TOTAL_COMMANDER_LAYER]

    for(uint16_t cnt = 0; cnt < LAYER_COUNT; cnt ++ )
    {
        /* set as active screen for the first layer */
        if(cnt == 0 )
        {
            kb_layers[cnt].screen_obj = lv_scr_act();
        }
        else
        {
            kb_layers[cnt].screen_obj = lv_obj_create(NULL);
        }
        kb_layers[cnt].screen_init_fptr(kb_layers[cnt].screen_obj);
    }
}
#if 0
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

            TAB_VIEW_OFFICE = lv_tabview_add_tab(tab_view, kb_layers[HOME_SCREEN_LAYER].tab_view_name);
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
#endif



void tick_screen_main(void) {
}

typedef void (*tick_screen_func_t)(void);

tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
};

void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
