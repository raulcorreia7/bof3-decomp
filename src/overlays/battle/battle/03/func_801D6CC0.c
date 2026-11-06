#include "battle_03.h"

MATCH void func_801D6CC0(void) {
    if (ACTOR_IN_USE(g_BattlePartyBattlers[0])) {
        g_BattlePartyBattlers[0].header.mode = 2u;
    }
    if (ACTOR_IN_USE(g_BattlePartyBattlers[1])) {
        g_BattlePartyBattlers[1].header.mode = 2u;
    }
    if (ACTOR_IN_USE(g_BattlePartyBattlers[2])) {
        g_BattlePartyBattlers[2].header.mode = 2u;
    }
    if ((g_BattleOptions & BATTLE_OPT_KEEP_BGM) == 0u) {
        SND_StopAllSequences();
        SND_PlaySequence(0, 1, 0x64, 0x64);
    }
    func_801D9484();
    func_801DEAE0();
    g_BattleSubStep += 1u;
}
