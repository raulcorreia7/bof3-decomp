#include "area048_13.h"

/* Probe ten cells at the row's height and turn the party member standing in one toward the probe;
 * a member already in mode 1 also takes the row's second byte. */
MATCH void func_801F2EC0(void) {
    u8 i;
    u8 index;

    for (i = 0; i < 10u; i++) {
        g_Task->pos.x.fixed = TO_COORD(i + 97) | COORD_HALF;
        g_Task->pos.y.fixed = TO_COORD(D_801F4D78[g_Task->unk_06 * 2]);
        index               = Game_GetPartySize(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 0);
        if (index == 0xFF) {
            continue;
        }
        if ((g_Game.walk_flags & 0x1400) != 0) {
            continue;
        }
        if (g_GameStateIndex != 0) {
            continue;
        }
        if (g_Task->pos.y.fixed - g_Game.members[index].pos.y.fixed <= 0) {
            g_Game.members[index].facing = FACING_UP;
        } else {
            g_Game.members[index].facing = FACING_DOWN;
        }
        if (g_Game.members[index].header.mode == 1) {
            func_8015C214(index, D_801F4D79[g_Task->unk_06 * 2]);
        }
    }
}
