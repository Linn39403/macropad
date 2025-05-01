#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"
#include <string.h>

#define __KEYPAD_SCREEN_C
#include "keypad_screen.h"

void lv_keypad_button_create(lv_obj_t *parent_screen)
{
    #define NUM_PAD_BUTTON_SIZE_X 50
    #define NUM_PAD_BUTTON_SIZE_Y 25
    #define NUM_PAD_BUTTON_SPACE_X 6
    #define NUM_PAD_BUTTON_SPACE_Y 6
    #define NUM_PAD_X_OFFSET_FROM_LEFT 10
    #define NUM_PAD_Y_OFFSET_FROM_TOP 0
	#define BUTTON_ALIGN_STYLE LV_ALIGN_DEFAULT
    /*************** FIRST ROW *******************/
    //BackSpace Button
    btn_bks = lv_btn_create(parent_screen);
    lv_obj_set_size(btn_bks, NUM_PAD_BUTTON_SIZE_X, NUM_PAD_BUTTON_SIZE_Y);
    lv_obj_align(btn_bks , BUTTON_ALIGN_STYLE,
        NUM_PAD_X_OFFSET_FROM_LEFT,
        NUM_PAD_Y_OFFSET_FROM_TOP);

    lv_obj_t* label_bks = lv_label_create(btn_bks);
    lv_label_set_text(label_bks, "<-");
    lv_obj_center(label_bks);

    //Divide Button
    btn_div = lv_btn_create(parent_screen);
    lv_obj_set_size(btn_div, NUM_PAD_BUTTON_SIZE_X, NUM_PAD_BUTTON_SIZE_Y);
    lv_obj_align(btn_div, BUTTON_ALIGN_STYLE,
        (NUM_PAD_X_OFFSET_FROM_LEFT + NUM_PAD_BUTTON_SPACE_X + NUM_PAD_BUTTON_SIZE_X),
        NUM_PAD_Y_OFFSET_FROM_TOP);

    lv_obj_t* label_div = lv_label_create(btn_div);
    lv_label_set_text(label_div, "/");
    lv_obj_center(label_div);

    //Multiply Button
    btn_mul = lv_btn_create(parent_screen);
    lv_obj_set_size(btn_mul, NUM_PAD_BUTTON_SIZE_X, NUM_PAD_BUTTON_SIZE_Y);
    lv_obj_align(btn_mul, BUTTON_ALIGN_STYLE,
        (NUM_PAD_X_OFFSET_FROM_LEFT + NUM_PAD_BUTTON_SPACE_X * 2 + NUM_PAD_BUTTON_SIZE_X * 2),
        NUM_PAD_Y_OFFSET_FROM_TOP);

    lv_obj_t* label_mul = lv_label_create(btn_mul);
    lv_label_set_text(label_mul, "*");
    lv_obj_center(label_mul);

    //Minus Button
    btn_min = lv_btn_create(parent_screen);
    lv_obj_set_size(btn_min, NUM_PAD_BUTTON_SIZE_X, NUM_PAD_BUTTON_SIZE_Y);
    lv_obj_align(btn_min, BUTTON_ALIGN_STYLE,
        (NUM_PAD_X_OFFSET_FROM_LEFT + NUM_PAD_BUTTON_SPACE_X * 3 + NUM_PAD_BUTTON_SIZE_X * 3),
        NUM_PAD_Y_OFFSET_FROM_TOP);

    lv_obj_t* label_min = lv_label_create(btn_min);
    lv_label_set_text(label_min, "-");
    lv_obj_center(label_min);

    /*************** SECOND ROW *******************/
    //7 Button
    btn_7 = lv_btn_create(parent_screen);
    lv_obj_set_size(btn_7, NUM_PAD_BUTTON_SIZE_X, NUM_PAD_BUTTON_SIZE_Y);
    lv_obj_align(btn_7, BUTTON_ALIGN_STYLE,
        NUM_PAD_X_OFFSET_FROM_LEFT,
        (NUM_PAD_Y_OFFSET_FROM_TOP + NUM_PAD_BUTTON_SPACE_Y + NUM_PAD_BUTTON_SIZE_Y ));

    lv_obj_t* label_7 = lv_label_create(btn_7);
    lv_label_set_text(label_7, "7  A");
    lv_obj_center(label_7);

    //8 Button
    btn_8 = lv_btn_create(parent_screen);
    lv_obj_set_size(btn_8, NUM_PAD_BUTTON_SIZE_X, NUM_PAD_BUTTON_SIZE_Y);
    lv_obj_align(btn_8, BUTTON_ALIGN_STYLE,
        (NUM_PAD_X_OFFSET_FROM_LEFT + NUM_PAD_BUTTON_SPACE_X + NUM_PAD_BUTTON_SIZE_X),
        (NUM_PAD_Y_OFFSET_FROM_TOP + NUM_PAD_BUTTON_SPACE_Y + NUM_PAD_BUTTON_SIZE_Y));

    lv_obj_t* label_8 = lv_label_create(btn_8);
    lv_label_set_text(label_8, "8  B");
    lv_obj_center(label_8);

    //9 Button
    btn_9 = lv_btn_create(parent_screen);
    lv_obj_set_size(btn_9, NUM_PAD_BUTTON_SIZE_X, NUM_PAD_BUTTON_SIZE_Y);
    lv_obj_align(btn_9, BUTTON_ALIGN_STYLE,
        (NUM_PAD_X_OFFSET_FROM_LEFT + NUM_PAD_BUTTON_SPACE_X * 2 + NUM_PAD_BUTTON_SIZE_X * 2),
        (NUM_PAD_Y_OFFSET_FROM_TOP + NUM_PAD_BUTTON_SPACE_Y + NUM_PAD_BUTTON_SIZE_Y));

    lv_obj_t* label_9 = lv_label_create(btn_9);
    lv_label_set_text(label_9, "9  C");
    lv_obj_center(label_9);

    //+ Button
    btn_plus = lv_btn_create(parent_screen);
    lv_obj_set_size(btn_plus, NUM_PAD_BUTTON_SIZE_X, NUM_PAD_BUTTON_SIZE_Y * 2 + NUM_PAD_BUTTON_SPACE_Y);
    lv_obj_align(btn_plus, BUTTON_ALIGN_STYLE,
        (NUM_PAD_X_OFFSET_FROM_LEFT + NUM_PAD_BUTTON_SPACE_X * 3 + NUM_PAD_BUTTON_SIZE_X * 3),
        (NUM_PAD_Y_OFFSET_FROM_TOP + NUM_PAD_BUTTON_SPACE_Y + NUM_PAD_BUTTON_SIZE_Y));

    lv_obj_t* label_plus = lv_label_create(btn_plus);
    lv_label_set_text(label_plus, "+");
    lv_obj_center(label_plus);

    /*************** THRID ROW *******************/
    //4 Button
    btn_4 = lv_btn_create(parent_screen);
    lv_obj_set_size(btn_4, NUM_PAD_BUTTON_SIZE_X, NUM_PAD_BUTTON_SIZE_Y);
    lv_obj_align(btn_4, BUTTON_ALIGN_STYLE,
        NUM_PAD_X_OFFSET_FROM_LEFT,
        (NUM_PAD_Y_OFFSET_FROM_TOP + NUM_PAD_BUTTON_SPACE_Y * 2 + NUM_PAD_BUTTON_SIZE_Y * 2));

    lv_obj_t* label_4 = lv_label_create(btn_4);
    lv_label_set_text(label_4, "4  D");
    lv_obj_center(label_4);

    //5 Button
    btn_5 = lv_btn_create(parent_screen);
    lv_obj_set_size(btn_5, NUM_PAD_BUTTON_SIZE_X, NUM_PAD_BUTTON_SIZE_Y);
    lv_obj_align(btn_5, BUTTON_ALIGN_STYLE,
        (NUM_PAD_X_OFFSET_FROM_LEFT + NUM_PAD_BUTTON_SPACE_X + NUM_PAD_BUTTON_SIZE_X),
        (NUM_PAD_Y_OFFSET_FROM_TOP + NUM_PAD_BUTTON_SPACE_Y * 2 + NUM_PAD_BUTTON_SIZE_Y * 2));

    lv_obj_t* label_5 = lv_label_create(btn_5);
    lv_label_set_text(label_5, "5  E");
    lv_obj_center(label_5);

    //6 Button
    btn_6 = lv_btn_create(parent_screen);
    lv_obj_set_size(btn_6, NUM_PAD_BUTTON_SIZE_X, NUM_PAD_BUTTON_SIZE_Y);
    lv_obj_align(btn_6, BUTTON_ALIGN_STYLE,
        (NUM_PAD_X_OFFSET_FROM_LEFT + NUM_PAD_BUTTON_SPACE_X * 2 + NUM_PAD_BUTTON_SIZE_X * 2),
        (NUM_PAD_Y_OFFSET_FROM_TOP + NUM_PAD_BUTTON_SPACE_Y * 2 + NUM_PAD_BUTTON_SIZE_Y * 2));

    lv_obj_t* label_6 = lv_label_create(btn_6);
    lv_label_set_text(label_6, "6  F");
    lv_obj_center(label_6);

    /*************** FOURTH ROW *******************/
    //1 Button
    btn_1 = lv_btn_create(parent_screen);
    lv_obj_set_size(btn_1, NUM_PAD_BUTTON_SIZE_X, NUM_PAD_BUTTON_SIZE_Y);
    lv_obj_align(btn_1, BUTTON_ALIGN_STYLE,
        NUM_PAD_X_OFFSET_FROM_LEFT,
        (NUM_PAD_Y_OFFSET_FROM_TOP + NUM_PAD_BUTTON_SPACE_Y * 3 + NUM_PAD_BUTTON_SIZE_Y * 3));

    lv_obj_t* label_1 = lv_label_create(btn_1);
    lv_label_set_text(label_1, "1");
    lv_obj_center(label_1);

    //2 Button
    btn_2 = lv_btn_create(parent_screen);
    lv_obj_set_size(btn_2, NUM_PAD_BUTTON_SIZE_X, NUM_PAD_BUTTON_SIZE_Y);
    lv_obj_align(btn_2, BUTTON_ALIGN_STYLE,
        (NUM_PAD_X_OFFSET_FROM_LEFT + NUM_PAD_BUTTON_SPACE_X + NUM_PAD_BUTTON_SIZE_X),
        (NUM_PAD_Y_OFFSET_FROM_TOP + NUM_PAD_BUTTON_SPACE_Y * 3 + NUM_PAD_BUTTON_SIZE_Y * 3));

    lv_obj_t* label_2 = lv_label_create(btn_2);
    lv_label_set_text(label_2, "2");
    lv_obj_center(label_2);

    //3 Button
    btn_3 = lv_btn_create(parent_screen);
    lv_obj_set_size(btn_3, NUM_PAD_BUTTON_SIZE_X, NUM_PAD_BUTTON_SIZE_Y);
    lv_obj_align(btn_3, BUTTON_ALIGN_STYLE,
        (NUM_PAD_X_OFFSET_FROM_LEFT + NUM_PAD_BUTTON_SPACE_X * 2 + NUM_PAD_BUTTON_SIZE_X * 2),
        (NUM_PAD_Y_OFFSET_FROM_TOP + NUM_PAD_BUTTON_SPACE_Y * 3 + NUM_PAD_BUTTON_SIZE_Y * 3));

    lv_obj_t* label_3 = lv_label_create(btn_3);
    lv_label_set_text(label_3, "3");
    lv_obj_center(label_3);

    //Enter Button
    btn_ent = lv_btn_create(parent_screen);
    lv_obj_set_size(btn_ent, NUM_PAD_BUTTON_SIZE_X, NUM_PAD_BUTTON_SIZE_Y * 2 + NUM_PAD_BUTTON_SPACE_Y);
    lv_obj_align(btn_ent, BUTTON_ALIGN_STYLE,
        (NUM_PAD_X_OFFSET_FROM_LEFT + NUM_PAD_BUTTON_SPACE_X * 3 + NUM_PAD_BUTTON_SIZE_X * 3),
        (NUM_PAD_Y_OFFSET_FROM_TOP + NUM_PAD_BUTTON_SPACE_Y * 3 + NUM_PAD_BUTTON_SIZE_Y * 3));

    lv_obj_t* label_ent = lv_label_create(btn_ent);
    lv_label_set_text(label_ent, "Ent");
    lv_obj_center(label_ent);

    /*************** FIFTH ROW *******************/
    //ZERO Button
    btn_0 = lv_btn_create(parent_screen);
    lv_obj_set_size(btn_0, NUM_PAD_BUTTON_SIZE_X * 2 + NUM_PAD_BUTTON_SPACE_X, NUM_PAD_BUTTON_SIZE_Y);
    lv_obj_align(btn_0, BUTTON_ALIGN_STYLE,
        NUM_PAD_X_OFFSET_FROM_LEFT,
        (NUM_PAD_Y_OFFSET_FROM_TOP + NUM_PAD_BUTTON_SPACE_Y * 4 + NUM_PAD_BUTTON_SIZE_Y * 4));

    lv_obj_t* label_0 = lv_label_create(btn_0);
    lv_label_set_text(label_0, "0");
    lv_obj_center(label_0);

    //dot Button
    btn_dot = lv_btn_create(parent_screen);
    lv_obj_set_size(btn_dot, NUM_PAD_BUTTON_SIZE_X , NUM_PAD_BUTTON_SIZE_Y);
    lv_obj_align(btn_dot, BUTTON_ALIGN_STYLE,
        (NUM_PAD_X_OFFSET_FROM_LEFT + NUM_PAD_BUTTON_SPACE_X * 2+ NUM_PAD_BUTTON_SIZE_X * 2),
        (NUM_PAD_Y_OFFSET_FROM_TOP + NUM_PAD_BUTTON_SPACE_Y * 4 + NUM_PAD_BUTTON_SIZE_Y * 4));

    lv_obj_t* label_dot = lv_label_create(btn_dot);
    lv_label_set_text(label_dot, ".");
    lv_obj_center(label_dot);
}
