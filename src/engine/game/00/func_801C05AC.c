#include "game_00.h"

MATCH void func_801C05AC(void) {
    PartyBattler* row;
    s32           i;

    if (!(g_AreaWalkFlags & AREA_WALK_MAP_LOADING)) {
        Party_ClearActiveBattlers();
        if (g_GameRequestFlags & 8) {
            g_BattlePartyBattlers[0].mode = 9;
        } else {
            for (i = 0; i < g_PartySize; i++) {
                g_BattlePartyBattlers[i].unk_29 = 6;
            }
        }
        for (i = 0; i < g_PartySize; i++) {
            row = &g_BattlePartyBattlers[i];
            if (!((g_GameFlags >> i) & 1)) {
                g_GameState = (GameState*)row;
                g_Task      = (Actor*)row;
                if (g_BattlePartyBattlers[i].slot == 0) {
                    func_801B00F8();
                } else {
                    func_801BBE48();
                }
            }
        }
    } else {
        for (i = 0; i < g_PartySize; i++) {
            g_BattlePartyBattlers[i].flags &= ~ACTOR_FLAG_HIDDEN;
        }
    }
    g_AreaWalkFlags &= 0xBFFF;
}
