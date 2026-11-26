#include "area048_13.h"

/* Probe ten cells at the row's height and turn the member standing in one toward the probe. */
MATCH void func_801F2EC0(void) {
    u8 i;
    u8 index;

    for (i = 0; i < 10u; i++) {
        SELF(Actor)->pos.x.fixed = TO_COORD(i + 97) | COORD_HALF;
        SELF(Actor)->pos.y.fixed = TO_COORD(D_801F4D78[SELF(Actor)->unk_06 * 2]);
        index                    = Game_GetPartySize(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, 0);
        if (index == GAME_NONE) {
            continue;
        }
        if ((g_Game.walk_flags & (AREA_WALK_TRANSITION | AREA_WALK_LEADER_SWITCH_ACTIVE)) != 0) {
            continue;
        }
        if (g_GameStateIndex != GAME_REQUEST_IDLE) {
            continue;
        }
        if (SELF(Actor)->pos.y.fixed - g_Game.members[index].pos.y.fixed <= 0) {
            g_Game.members[index].facing = FACING_UP;
        } else {
            g_Game.members[index].facing = FACING_DOWN;
        }
        if (g_Game.members[index].header.mode == 1) {
            func_8015C214(index, D_801F4D79[SELF(Actor)->unk_06 * 2]);
        }
    }
}
