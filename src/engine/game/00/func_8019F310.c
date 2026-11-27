#include "game_00.h"

MATCH void func_8019F310(void) {
    u8 alt;

    alt                            = g_GameRequestFlags & AREA_LOAD_FLAG_WORLD_MAP;
    COORD_FRAC(SELF(Actor)->pos.y) = 0;
    if (alt) {
        COORD_INT(SELF(Actor)->pos.y) = -0xA;
    } else {
        COORD_INT(SELF(Actor)->pos.y) = -0x14;
    }
    SELF(Actor)->vy         = 131072;
    SELF(Actor)->draw_layer = 3;
    SELF(Actor)->timer      = 6;
    SELF(Actor)->header.mode++;
}
