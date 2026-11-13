#include "game_00.h"

MATCH void func_8019F310(void) {
    u8 alt;

    alt                       = g_GameRequestFlags & AREA_LOAD_FLAG_WORLD_MAP;
    COORD_FRAC(g_Task->pos.y) = 0;
    if (alt) {
        COORD_INT(g_Task->pos.y) = -0xA;
    } else {
        COORD_INT(g_Task->pos.y) = -0x14;
    }
    g_Task->vy         = 131072;
    g_Task->draw_layer = 3;
    g_Task->timer      = 6;
    g_Task->header.mode++;
}
