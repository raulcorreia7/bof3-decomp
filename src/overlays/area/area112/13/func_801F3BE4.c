#include "area112_13.h"

#ifdef NON_MATCHING
NON_MATCHING s32 func_801F3BE4(s32 x, s32 y) {
    s32 i;
    s32 count;
    s32 dx;
    s32 dy;
    s32 height;

    /* FAKE: retail reserves eight bytes of frame that no access explains. */
    FAKE_STACK_PADS(u8, 8);
    i     = 0;
    count = g_PartySize;
    if (count > 0) {
        do {
            if (g_Game.members[i].header.flags != 0) {
                height = (g_Game.members[i].unk_70 + 2) << 15;
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
                        return (s8)i;
                    }
                }
            }
            i++;
        } while (i < count);
    }
    return -1;
}
#else
INCLUDE_ASM(func_801F3BE4);
#endif
