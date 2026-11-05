#include "game_00.h"

MATCH void func_801BEDD0(void) {
    s32 index;
    u8* work;
    s32 count;

    index = 0;
    count = (s32)g_PartySize;
    if (count <= index) {
        return;
    }
    work = (u8*)g_BattlePartyBattlers + index * BATTLE_PARTY_STRIDE;
    do {
        SP_REF(u8*, 0x44) = work;
        g_Task->unk_0B    = Actor_GetTurnStep((s32)s_RouteIndexByMode[g_BattleScrollDir]);
        work += BATTLE_PARTY_STRIDE;
        index += 1;
    } while (index < (s32)g_PartySize);
}
