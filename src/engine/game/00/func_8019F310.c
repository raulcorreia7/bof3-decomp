#include "game_00.h"

MATCH void func_8019F310(void) {
    u8 alt;

    alt                            = g_GameRequestFlags & AREA_LOAD_FLAG_WORLD_MAP;
    COORD_FRAC(TASK(Actor)->pos.y) = 0;
    if (alt) {
        COORD_INT(TASK(Actor)->pos.y) = -0xA;
    } else {
        COORD_INT(TASK(Actor)->pos.y) = -0x14;
    }
    TASK(Actor)->vy         = 131072;
    TASK(Actor)->draw_layer = 3;
    TASK(Actor)->timer      = 6;
    TASK(Actor)->header.mode++;
}
