#include "boss018_16.h"

MATCH void func_800C1BC8(void) {
    if (SYS_TestFlag(g_SceneFlags, 0x37) != 0) {
        g_BattleCurrentEnemy->hp_94 = D_801FD700;
        g_BattleCurrentEnemy->ap = D_801FD6FE;
    } else {
        SYS_SetFlag(g_SceneFlags, 0x37U);
    }
    g_BattleCurrentEnemy->script = &D_800C2C50;
    g_BattleCurrentEnemy->unk_E4 = func_800C1C6C;
    g_BattleCurrentEnemy->unk_E8 = &D_800C2C9C;
    ((PartyBattler *)g_SpadWork)->step_01 = 2;
    func_8014D978();
}
