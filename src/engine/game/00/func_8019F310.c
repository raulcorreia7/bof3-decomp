#include "game_00.h"

MATCH void func_8019F310(void) {
    u8 alt;

    alt                         = g_GameRequestFlags & 1;
    g_SpadWork->y.part.fraction = 0;
    if (alt) {
        g_SpadWork->y.part.integer = -0xA;
    } else {
        g_SpadWork->y.part.integer = -0x14;
    }
    g_SpadWork->vy     = 0x20000;
    g_SpadWork->unk_29 = 3;
    g_SpadWork->unk_09 = 6;
    g_SpadWork->unk_01++;
}
