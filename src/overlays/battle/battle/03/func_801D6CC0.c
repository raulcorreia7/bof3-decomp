#include "battle_03.h"

MATCH void func_801D6CC0(void) {
    if (ACTOR_IN_USE(g_Game.members[0])) {
        g_Game.members[0].header.mode = 2u;
    }
    if (ACTOR_IN_USE(g_Game.members[1])) {
        g_Game.members[1].header.mode = 2u;
    }
    if (ACTOR_IN_USE(g_Game.members[2])) {
        g_Game.members[2].header.mode = 2u;
    }
    if ((g_Battle.outcome.options & BATTLE_OPT_KEEP_BGM) == 0u) {
        SND_StopAllSequences();
        SND_PlaySequence(0, 1, 0x64, 0x64);
    }
    Battle_OpenPanel();
    func_801DEAE0();
    g_Battle.phase.sub_step += 1u;
}
