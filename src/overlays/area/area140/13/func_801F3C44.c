#include "area140_13.h"

#ifdef NON_MATCHING
NON_MATCHING s32 func_801F3C44(s32 x, s32 y) {
    /* FAKE: the first distance check uses the x argument saved in t2. */
    FAKE_REG(s32, target_x, "t2");
    /* FAKE: retail keeps the party count in v0 for the initial branch. */
    FAKE_REG(s32, count, "v0");
    s32 i;
    s32 dx;
    s32 dy;
    s32 height;

    /* FAKE: retail reserves eight bytes of frame that no access explains. */
    FAKE_STACK_PADS(u8, 8);
    target_x = x;
    /* FAKE: keep the saved x argument live across the count load. */
    FAKE_USE(target_x);
    count = g_PartySize;
    i     = 0;
    if (count > 0) {
        do {
            if (g_Game.members[i].header.flags != 0) {
                height = (g_Game.members[i].unk_70 + 3) << 15;
                dx     = g_Game.members[i].pos.x.fixed + g_Game.members[i].unk_0C * g_Game.members[i].unk_09 - target_x;
                if (dx < 0) {
                    dx = -dx;
                }
                if (dx < height) {
                    dy = g_Game.members[i].pos.y.fixed + g_Game.members[i].unk_10 * g_Game.members[i].unk_09 - y;
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
INCLUDE_ASM(func_801F3C44);
#endif
