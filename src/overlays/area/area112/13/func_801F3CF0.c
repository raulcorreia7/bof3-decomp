#include "area112_13.h"

/* Returns whether a party member's offset position lies inside one of the four zones. */
MATCH bool func_801F3CF0(void) {
    s32 i;
    s32 j;
    s32 x;
    s32 y;
    s32 delta_x;
    s32 delta_y;

    for (i = 0; i < g_Game.party_size; i++) {
        x = (g_Game.members[i].pos.x.fixed + g_Game.members[i].unk_0C * g_Game.members[i].unk_09) >> 16;
        y = (g_Game.members[i].pos.y.fixed + g_Game.members[i].unk_10 * g_Game.members[i].unk_09) >> 16;
        for (j = 0; j < 4; j++) {
            delta_x = abs(x - D_801F492C[j].x);
            delta_y = abs(y - D_801F492C[j].y);
            if (delta_x < D_801F492C[j].reach_x && delta_y < D_801F492C[j].reach_y) {
                return true;
            }
        }
    }
    return false;
}
