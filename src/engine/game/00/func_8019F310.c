#include "game_00.h"

MATCH void func_8019F310(void) {
    u8 alt;

    alt                   = g_GameRequestFlags & 1;
    COORD_FRAC(g_Task->y) = 0;
    if (alt) {
        COORD_INT(g_Task->y) = -0xA;
    } else {
        COORD_INT(g_Task->y) = -0x14;
    }
    g_Task->vy     = 0x20000;
    g_Task->unk_29 = 3;
    g_Task->unk_09 = 6;
    g_Task->header.mode++;
}
