#include "boss018_16.h"

MATCH void Boss_ChooseBattleEnding(void) {
    s8 var_v0_2;

    if (!(g_BattleResult & 2)) {
        goto block_4;
    }
    if (g_BattleBossFlags & 2) {
        D_80146875 = 0x1A;
    } else {
        D_80146875 = 0x1B;
    }
    func_801DDED8();
    goto block_11;
block_4:
    if (g_BattleBossFlags & 1) {
        goto block_7;
    }
    if (SYS_TestFlag(g_SceneFlags, 0x23) == 0) {
        goto block_9;
    }
    if (SYS_TestFlag(g_SceneFlags, 0x24) == 0) {
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
    D_80146875 = var_v0_2;
    func_801DDF28();
block_11:
    D_801FD702 = D_801EB7DC;
    D_801FD6FC = D_801EB8F4;
    D_801FD700 = D_801EB6C4;
    D_801FD6FE = D_801EB6C6;
    return;
}
