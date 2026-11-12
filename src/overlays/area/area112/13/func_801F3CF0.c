#include "area112_13.h"

#ifdef NON_MATCHING
NON_MATCHING s32 func_801F3CF0(void) {
    s32 i;
    s32 j;
    s32 x;
    s32 y;
    s32 dx;
    s32 dy;

    for (i = 0; i < g_Game.party_size; i++) {
        x = (g_Game.members[i].pos.x.fixed + g_Game.members[i].unk_0C * g_Game.members[i].unk_09) >> 16;
        y = (g_Game.members[i].pos.y.fixed + g_Game.members[i].unk_10 * g_Game.members[i].unk_09) >> 16;
        j = 0;
        do {
            dx = x - D_801F492C[j];
            dx = ABS(dx);
            dy = y - D_801F492D[j];
            dy = ABS(dy);
            if ((dx < D_801F492E[j]) && (dy < D_801F492F[j])) {
                return 1;
            }
            j += 4;
        } while (j < 16);
    }
    return 0;
}
#else
INCLUDE_ASM(func_801F3CF0);
#endif
