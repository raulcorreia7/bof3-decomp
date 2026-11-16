#include "area086_13.h"

#ifdef NON_MATCHING
NON_MATCHING s8 func_801F34F8(s32 x, s32 y) {
    s32 count;
    s32 i;
    s32 px;
    s32 py;
    s32 radius;

    count = g_PartySize;
    for (i = 0; i < count; i++) {
        if (g_Game.members[i].header.flags == 0) {
            continue;
        }
        px     = g_Game.members[i].pos.x.fixed + g_Game.members[i].unk_0C * g_Game.members[i].unk_09;
        py     = g_Game.members[i].pos.y.fixed + g_Game.members[i].unk_10 * g_Game.members[i].unk_09;
        radius = (g_Game.members[i].unk_70 + 2) << 15;
        if (ABS(px - (x << 16)) < radius && ABS(py - (y << 16)) < radius) {
            return i;
        }
    }
    return -1;
}
#else
INCLUDE_ASM(func_801F34F8);
#endif
