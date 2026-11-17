#include "area086_13.h"

#ifdef NON_MATCHING
NON_MATCHING s8 func_801F34F8(s32 x, s32 y) {
    s32 i;
    s32 count;
    s32 dx;
    s32 dy;
    s32 height;

    i     = 0;
    count = g_PartySize;
    if (count > 0) {
        do {
            if (g_Game.members[i].header.flags != 0) {
                height = (g_Game.members[i].speed + 2) << 15;
                dx     = g_Game.members[i].pos.x.fixed + g_Game.members[i].unk_0C * g_Game.members[i].unk_09 - (x << 16);
                if (dx < 0) {
                    dx = -dx;
                }
                if (dx < height) {
                    dy = g_Game.members[i].pos.y.fixed + g_Game.members[i].unk_10 * g_Game.members[i].unk_09 - (y << 16);
                    if (dy < 0) {
                        dy = -dy;
                    }
                    if (dy < height) {
                        return i;
                    }
                }
            }
            i++;
        } while (i < count);
    }
    return -1;
}
#else
INCLUDE_ASM(func_801F34F8);
#endif
