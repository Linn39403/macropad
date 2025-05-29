#include <string.h>
#include "keymap.h"
#include "resource_screen.h"
#include "keypad_screen.h"
#include "total_commander_screen.h"
#include "vsc_screen.h"
#include "config.h"

static uint8_t u8SCREEN__CurrentActiveLayer = 0;
struct kb_layer_type kb_layers[LAYER_COUNT] =
{
#ifdef ENABLE_RESOURCE_LAYER
    {
     .m_spScreenObj = NULL,
     .m_u8ScreenLayerId = HOME_SCREEN_LAYER},
#endif
#ifdef ENABLE_TOTAL_COMMANDER_LAYER
    {
     .m_spScreenObj = NULL,
     .m_pfnScreenInit = &TTCMD_vScreenCreate,
     .m_u8ScreenLayerId = TOTAL_COMMANDER_LAYER},
#endif
#ifdef ENABLE_NUMPAD_LAYER
    {
     .m_spScreenObj = NULL,
     .m_pfnScreenInit = &KPAD_vScreenCreate,
     .m_u8ScreenLayerId = NUMPAD_LAYER},
#endif
#ifdef ENABLE_VSC_LAYER
    {
     .m_spScreenObj = NULL,
     .m_pfnScreenInit = &VSC_vScreenCreate,
     .m_u8ScreenLayerId = VSC_LAYER},
#endif
#ifdef ENABLE_BROWSER_LAYER
    {
     .m_spScreenObj = NULL,
     .m_pfnScreenInit = &BWSER_vScreenCreate,
     .m_u8ScreenLayerId = BROWSER_LAYER},
#endif
#ifdef ENABLE_RESOURCE_LAYER
    {
     .m_spScreenObj = NULL,
     .m_u8ScreenLayerId = RESOURCE_LAYER},
#endif
};

uint8_t SCREEN_u8GetActiveLayer(void)
{
    return kb_layers[u8SCREEN__CurrentActiveLayer].m_u8ScreenLayerId;
}

void SCREEN_vChangeLayer(uint8_t u8Layer)
{
    if(u8Layer < LAYER_COUNT)
    {
        u8SCREEN__CurrentActiveLayer = u8Layer;
        lv_scr_load(kb_layers[u8SCREEN__CurrentActiveLayer].m_spScreenObj);
    }
}

void SCREEN_vInit(void)
{
    for(uint8_t u8Layer = 0; u8Layer < LAYER_COUNT; u8Layer ++ )
    {
        /* set as active screen for the first layer */
        if(0 == u8Layer)
        {
            kb_layers[u8Layer].m_spScreenObj = lv_scr_act();
        }
        else
        {
            kb_layers[u8Layer].m_spScreenObj = lv_obj_create(NULL);
        }
        kb_layers[u8Layer].m_pfnScreenInit(kb_layers[u8Layer].m_spScreenObj);
    }
}

