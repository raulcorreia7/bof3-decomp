#include "game_00.h"

MATCH void func_801BEDD0(void) {
    s32 index;
    u8* work;
    s32 count;

    index = 0;
    count = g_PartySize;
    if (count <= index) {
        return;
    }
    work = (u8*)g_BattlePartyBattlers + index * BATTLE_PARTY_STRIDE;
    do {
        TASK_SET(work);
        g_Task->param.unk_0B = Actor_GetTurnStep(s_RouteIndexByMode[g_BattleScrollDir]);
        work += BATTLE_PARTY_STRIDE;
        index += 1;
    } while (index < g_PartySize);
}
