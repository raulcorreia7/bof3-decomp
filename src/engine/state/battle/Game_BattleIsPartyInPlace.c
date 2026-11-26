#include "engine/game/00/game_00.h"

/* func_801BF78C */
MATCH bool Game_BattleIsPartyInPlace(void) {
    u8* work;
    s32 i;
    u8  j;

    if (g_Battle.outcome.options & 0x10) {
        return 1;
    }
    for (i = 0; i < g_Game.party_size; i++) {
        work        = (u8*)g_Game.members + i * BATTLE_PARTY_STRIDE;
        g_GameState = work;
        SELF_SET(work);
        for (j = 0; j < BATTLE_PARTY_CHARACTERS_COUNT; j++) {
            if (g_PartyFieldOrder[j] == work[0x79]) {
                break;
            }
        }
        if (SELF(Actor)->param.unk_0B == 0 && (Script_AnimStepOnce() & BYTE_MASK) != 0) {
            SELF(Actor)->param.unk_0B = 1;
        }
    }
    for (i = 0; i < g_Game.party_size; i++) {
        if (g_Game.members[i].param.unk_0B != 1) {
            return 0;
        }
    }
    return 1;
}
