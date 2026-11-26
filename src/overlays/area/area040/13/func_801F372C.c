#include "area040_13.h"

MATCH void func_801F372C(s32 pos0, s32 pos1) {
    s16 cell0;
    s16 cell1;
    s32 off;
    s32 x;
    s32 y;

    cell0 = pos0 >> 16;
    pos0  = pos0 & 0xFFFF;
    cell1 = pos1 >> 16;
    pos1  = pos1 & 0xFFFF;
    off   = g_Game.members[0].facing & 7;
    cell0 -= D_80181B00[off][0];
    pos0 = pos0 | (cell0 << 16);
    cell1 -= D_80181B00[off][1];
    pos1 = pos1 | (cell1 << 16);
    x    = pos0 >> 16;
    if ((u32)(x - 0x94) < 4) {
        y = pos1 >> 16;
        if ((u32)(y - 0x20) < 4) {
            func_801A4BC0(x, y, 0x50);
        }
    }
}
