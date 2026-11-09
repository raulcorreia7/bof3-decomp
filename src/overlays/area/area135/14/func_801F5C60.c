#include "area135_14.h"

MATCH u8 func_801F5C60(s32 x, s32 y) {
    u8 i;

    for (i = 0; i < 0x1E; i++) {
        if ((g_Actors[i].header.flags & ACTOR_FLAG_IN_USE) && &g_Actors[i] != g_Task && g_Actors[i].unk_06 == 0xA &&
            g_Actors[i].pos.x.fixed == x && g_Actors[i].pos.y.fixed == y) {
            return i;
        }
    }
    return 0xFF;
}
