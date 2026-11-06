#include "game_00.h"

MATCH u8 func_801BF78C(void) {
    u8* work;
    s32 off;
    s32 i;
    u8  j;

    if (g_BattleOptions & 0x10) {
        return 1;
    }
    for (i = 0; i < g_PartySize; i++) {
        work        = (u8*)g_BattlePartyBattlers + i * BATTLE_PARTY_STRIDE;
        g_GameState = (GameState*)work;
        TASK_SET(work);
        for (j = 0; j < BATTLE_PARTY_SLOT_COUNT; j++) {
            if (g_PartyFieldOrder[j] == work[0x79]) {
                break;
            }
        }
        if (g_Task->unk_0B == 0 && (func_8014DAEC() & BYTE_MASK) != 0) {
            g_Task->unk_0B = 1;
        }
    }
    for (i = 0; i < g_PartySize; i++) {
        off = i * BATTLE_PARTY_STRIDE;
        if ((&D_80145E9B)[off] != 1) {
            return 0;
        }
    }
    return 1;
}
