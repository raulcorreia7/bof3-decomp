#include "game_00.h"

MATCH void func_801A02E8(void) {
    u16* seed;
    s32  i;

    seed = (u16*)&g_GameEntryAreaId;
    for (i = 0; i < 11; i++) {
        if (*seed == D_801C8384[i]) {
            g_GameRequestKind = 11;
            return;
        }
    }
    if (i == 11) {
        g_GameRequestKind = 1;
    }
}
