#include "game_00.h"

MATCH void func_801B2AB4(void) {
    s32 index;
    s32 offset;
    u8  state;

    if (g_BattleEncounter == 0) {
        func_801BEBB0();
    } else {
        index = 1;
        if (index < g_PartySize) {
            state  = 5;
            offset = BATTLE_PARTY_STRIDE;
            do {
                Party_ClearBattlerState(index & BYTE_MASK);
                D_80145E91[offset] = state;
                offset += BATTLE_PARTY_STRIDE;
                index++;
            } while (index < g_PartySize);
        }
        g_Task->unk_0B = 0xFF;
    }
    g_Task->step = 1;
}
