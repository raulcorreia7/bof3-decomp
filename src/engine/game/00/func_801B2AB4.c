#include "game_00.h"

MATCH void func_801B2AB4(void) {
    s32 index;
    s32 offset;
    u8  state;

    if (BATTLE_IS_RANDOM()) {
        func_801BEBB0();
    } else {
        index = 1;
        if (index < g_Game.party_size) {
            state  = 5;
            offset = BATTLE_PARTY_STRIDE;
            do {
                Party_ClearBattlerState(index & BYTE_MASK);
                D_80145E91[offset] = state;
                offset += BATTLE_PARTY_STRIDE;
                index++;
            } while (index < g_Game.party_size);
        }
        g_Task->param.unk_0B = 0xFF;
    }
    g_Task->header.step = 1;
}
