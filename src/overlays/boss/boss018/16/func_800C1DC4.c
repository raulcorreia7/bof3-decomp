#include "boss018_16.h"

MATCH void func_800C1DC4(void) {
    if ((SYS_TestFlag(g_SceneFlags, 0x1E) != 0) || (SYS_TestFlag(g_SceneFlags, 0x23) != 0)) {
        if (((PartyBattler *)g_SpadWork)->slot == 4) {
            g_BattleCurrentEnemy->hp_94 = D_801FD702;
        } else {
            g_BattleCurrentEnemy->hp_94 = D_801FD6FC;
        }
    }
    if (((PartyBattler *)g_SpadWork)->slot == 5) {
        ((PartyBattler *)g_SpadWork)->word_08.byte.facing_08 |= 2;
        g_BattleCurrentEnemy->script = D_800C2C74;
    } else {
        g_BattleCurrentEnemy->script = D_800C2C5C;
    }
    g_BattleCurrentEnemy->unk_E4 = func_800C2074;
    g_BattleCurrentEnemy->unk_E8 = &D_800C2CA4;
    ((PartyBattler *)g_SpadWork)->step_01 = 2;
    func_8014D978();
}
