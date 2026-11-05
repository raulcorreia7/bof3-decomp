#include "game_00.h"

MATCH void func_8019F310(void) {
    u8 alt;

    alt                     = g_GameRequestFlags & 1;
    g_Task->y.part.fraction = 0;
    if (alt) {
        g_Task->y.part.integer = -0xA;
    } else {
        g_Task->y.part.integer = -0x14;
    }
    g_Task->vy     = 0x20000;
    g_Task->unk_29 = 3;
    g_Task->unk_09 = 6;
    g_Task->mode++;
}
