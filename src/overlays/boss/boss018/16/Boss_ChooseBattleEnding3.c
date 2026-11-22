#include "boss018_16.h"

MATCH void Boss_ChooseBattleEnding3(void) {
    s8 step;

    if (!(g_Battle.outcome.result & BATTLE_RESULT_VICTORY)) {
        goto block_4;
    }
    if (g_Battle.boss_flags & 0x2) {
        g_ScenarioState.step = 0x1A;
    } else {
        g_ScenarioState.step = 0x29;
    }
    Battle_EndVictory();
    goto block_11;
block_4:
    if (g_Battle.boss_flags & 0x1) {
        goto block_7;
    }
    if (SYS_TestFlag(g_SceneFlags, 35) == 0) {
        goto block_9;
    }
    if (SYS_TestFlag(g_SceneFlags, 36) == 0) {
        goto block_8;
    }
block_7:
    Battle_EndDefeat();
    goto block_11;
block_8:
    step = 0x3A;
    goto block_10;
block_9:
    step = 0x1C;
block_10:
    g_ScenarioState.step = step;
    Boss_SetCharacterId();
    Battle_EndToArea();
block_11:
    D_801FD702 = D_801EB7DC;
    D_801FD6FC = D_801EB8F4;
    D_801FD700 = D_801EB6C4;
    D_801FD6FE = D_801EB6C6;
}
