#include "game_00.h"

MATCH void func_801B2AB4(void) {
    s32 index;
    u8  state;

    if (BATTLE_IS_RANDOM()) {
        func_801BEBB0();
    } else {
        index = 1;
        if (index < g_Game.party_size) {
            state = 5;
            do {
                Party_BattlersClearState(index & BYTE_MASK);
                g_Game.members[index].header.mode = state;
                index++;
            } while (index < g_Game.party_size);
        }
        SELF(Actor)->param.unk_0B = 0xFF;
    }
    SELF(Actor)->header.step = 1;
}
