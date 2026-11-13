#include "game_00.h"

MATCH void func_801C05AC(void) {
    PartyMember* row;
    s32          i;

    if (!(g_AreaWalkFlags & AREA_WALK_MAP_LOADING)) {
        Party_ClearActiveBattlers();
        if (g_GameRequestFlags & AREA_LOAD_FLAG_FISHING) {
            g_Game.members[0].header.mode = 9;
        } else {
            for (i = 0; i < g_PartySize; i++) {
                g_Game.members[i].unk_29 = 6;
            }
        }
        for (i = 0; i < g_PartySize; i++) {
            row = &g_Game.members[i];
            if (!((g_GameFlags >> i) & 0x1)) {
                g_GameState = row;
                TASK_SET(row);
                if (g_Game.members[i].slot == 0) {
                    func_801B00F8();
                } else {
                    func_801BBE48();
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
