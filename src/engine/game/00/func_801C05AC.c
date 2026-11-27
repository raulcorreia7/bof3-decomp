#include "game_00.h"

MATCH void func_801C05AC(void) {
    PartyMember* member;
    s32          i;

    if (!(g_AreaWalkFlags & AREA_WALK_MAP_LOADING)) {
        Party_BattlersClearActive();
        if (g_GameRequestFlags & AREA_LOAD_FLAG_FISHING) {
            g_Game.members[0].header.mode = 9;
        } else {
            for (i = 0; i < g_PartySize; i++) {
                g_Game.members[i].unk_29 = 6;
            }
        }
        for (i = 0; i < g_PartySize; i++) {
            member = &g_Game.members[i];
            if (!((g_GameFlags >> i) & 0x1)) {
                g_GameState = member;
                SELF_SET(member);
                if (g_Game.members[i].slot == 0) {
                    Party_RunLeader();
                } else {
                    Party_RunFollower();
                }
            }
        }
    } else {
        for (i = 0; i < g_PartySize; i++) {
            g_Game.members[i].header.flags &= ~ACTOR_FLAG_HIDDEN;
        }
    }
    g_AreaWalkFlags &= 0xBFFF;
}
