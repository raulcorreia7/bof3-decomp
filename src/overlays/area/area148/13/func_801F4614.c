#include "area148_13.h"

MATCH void func_801F4614(void) {
    s8* trail;
    s32 saved_z;
    s32 group;
    u8  i;
    u8  code;
    u8  facing;
    u8  next;

    saved_z             = g_Task->pos.z.fixed;
    group               = (g_Task->direction_08 & 6) << 2;
    trail               = g_PartyTrailStep[g_Task->timer >> 3];
    g_Task->pos.z.fixed = g_Task->gravity;
    i                   = 0;
    do {
        code = Game_GetPartySize(g_Task->pos.x.fixed + TO_COORD(g_PartyTrailOffset[group + trail[i]][0]), g_Task->pos.y.fixed + TO_COORD(g_PartyTrailOffset[group + trail[i]][1]), 0);
        if (code != GAME_NONE && !(g_Game.walk_flags & (AREA_WALK_LEADER_SWITCH_ACTIVE | AREA_WALK_TRANSITION)) && g_GameStateIndex == GAME_REQUEST_IDLE) {
            facing = g_Game.members[code].facing;
            next   = facing & 7;
            if ((facing & 1) == 0) {
                next = (next + 1) & 7;
            }
            if (g_Game.members[code].header.mode == 1) {
                g_Game.members[code].facing = next;
                func_8015C214(code, 2);
            }
        }
        i++;
    } while (i < 2);
    g_Task->pos.z.fixed = saved_z;
}
