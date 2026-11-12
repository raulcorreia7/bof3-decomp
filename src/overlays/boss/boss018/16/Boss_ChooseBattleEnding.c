#include "boss018_16.h"

MATCH void Boss_ChooseBattleEnding(void) {
    s8 var_v0_2;

    if (!(g_Battle.outcome.result & BATTLE_RESULT_VICTORY)) {
        goto block_4;
    }
    if (g_Battle.boss_flags & 0x2) {
        g_SceneState.step_05 = 0x1A;
    } else {
        g_SceneState.step_05 = 0x1B;
    }
    func_801DDED8();
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
    func_801DDF00();
    goto block_11;
block_8:
    func_800C2A40();
    var_v0_2 = 0x3A;
    goto block_10;
block_9:
    func_800C2A40();
    var_v0_2 = 0x1C;
block_10:
    g_SceneState.step_05 = var_v0_2;
    func_801DDF28();
block_11:
    D_801FD702 = D_801EB7DC;
    D_801FD6FC = D_801EB8F4;
    D_801FD700 = D_801EB6C4;
    D_801FD6FE = D_801EB6C6;
    return;
}
