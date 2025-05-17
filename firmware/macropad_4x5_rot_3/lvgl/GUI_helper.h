#pragma once
#include QMK_KEYBOARD_H

/* Button Screen's Button Location Typedef Structure */
typedef struct GUI_tsBtnLocation
{
    /* Button Size X in pixels */
    uint8_t m_u8BtnSizeX;
    /* Button Size Y in pixels */
    uint8_t m_u8BtnSizeY;
    /* Button Size X coordinate in pixels */
    uint8_t m_u8BtnLocX;
    /* Button Size Y coordinate in pixels */
    uint8_t m_u8BtnLocY;
}GUI_tsBtnLocation;

#define GUI_SCREEN_CREATE(PREFIX, spParentScreen)                \
    do {                                                             \
        uint8_t u8RowCnt = 4;                                          \
        uint8_t u8ColCnt = PREFIX##_BUTTON_COUNT / u8RowCnt;           \
                                                                       \
        GUI_tsBtnLocation stBtnLoc;                                    \
        stBtnLoc.m_u8BtnSizeX = PREFIX##_BUTTON_SIZE_X;                \
        stBtnLoc.m_u8BtnSizeY = PREFIX##_BUTTON_SIZE_Y;                \
                                                                       \
        for (uint8_t u8Col = 0; u8Col < u8ColCnt; u8Col++) {           \
            for (uint8_t u8Row = 0; u8Row < u8RowCnt; u8Row++) {       \
                stBtnLoc.m_u8BtnLocX = PREFIX##_X_OFFSET_FROM_LEFT +   \
                                      (u8Row * PREFIX##_BUTTON_SPACE_X) +   \
                                      (u8Row * PREFIX##_BUTTON_SIZE_X);       \
                stBtnLoc.m_u8BtnLocY = PREFIX##_Y_OFFSET_FROM_TOP +      \
                                      (u8Col * PREFIX##_BUTTON_SPACE_Y) +   \
                                      (u8Col * PREFIX##_BUTTON_SIZE_Y);       \
                PREFIX##_staBtnInfo[u8Row + (u8RowCnt * u8Col)].m_spBtn = \
                    PREFIX##__spButtonCreate(                           \
                        spParentScreen,                                \
                        PREFIX##_staBtnInfo[u8Row + (u8RowCnt * u8Col)].m_cpBtnName, \
                        &stBtnLoc);                                    \
            }                                                        \
        }                                                            \
    } while(0)

void GUI_vButtonPress(lv_obj_t * );
void GUI_vButtonRelease(lv_obj_t * );
lv_obj_t * GUI_spButtonCreate(lv_obj_t* ,
                              const char * ,
                              lv_color_t ,
                              lv_color_t ,
                              GUI_tsBtnLocation * );
