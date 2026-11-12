#include "area086_13.h"

#ifdef NON_MATCHING
NON_MATCHING s8 func_801F34F8(s32 x, s32 y) {
    s32 dx;
    s32 dy;
    s32 i;
    s32 radius;

    for (i = 0; i < g_Game.party_size; i++) {
        if (g_Game.members[i].header.flags == 0) {
            continue;
        }
        radius = (g_Game.members[i].unk_70 + 2) << 15;
        dx     = g_Game.members[i].pos.x.fixed + g_Game.members[i].unk_0C * g_Game.members[i].unk_09 - TO_COORD(x);
        dy     = g_Game.members[i].pos.y.fixed + g_Game.members[i].unk_10 * g_Game.members[i].unk_09 - TO_COORD(y);
        if (abs(dx) < radius && abs(dy) < radius) {
            return i;
        }
    }
    return -1;
}
#else
INCLUDE_ASM(func_801F34F8);
#endif
