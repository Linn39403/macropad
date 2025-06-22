#include <string.h>
#include <stdbool.h>
#include "keymap.h"

#define SCREEN_LOCK   0x55
#define SCREEN_UNLOCK 0xAA

static uint8_t u8SCREEN__CurrentActiveLayer = 0;
static uint8_t u8SCREEN__LockStatus = SCREEN_LOCK;
struct kb_layer_type kb_layers[LAYER_COUNT] =
{
    #define X(layer) X_SCREEN_LAYER(layer)
    LAYER_LIST
    #undef X
};

bool SCREEN_boIsLock(void)
{
    if(u8SCREEN__LockStatus == SCREEN_LOCK)
        return true;
    else if(u8SCREEN__LockStatus == SCREEN_UNLOCK)
        return false;
    return true;
}

void SCREEN_vSetLock(void)
{
    u8SCREEN__LockStatus = SCREEN_LOCK;
}

void SCREEN_vSetUnLock(void)
{
    u8SCREEN__LockStatus = SCREEN_UNLOCK;
}

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

