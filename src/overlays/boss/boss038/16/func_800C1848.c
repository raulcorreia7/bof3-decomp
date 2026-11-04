#include "boss038_16.h"

MATCH void func_800C1848(void) {
    g_BattleCurrentEnemy->script = D_800C1C10;
    g_BattleCurrentEnemy->unk_E4 = func_800C18EC;
    g_BattleCurrentEnemy->unk_E8 = D_800C1C1C;
    g_BattleCurrentEnemy->flags_104 |= 8;
    ((PartyBattler*)g_SpadWork)->step_01 = 2;
    func_8014D978();
    if (SYS_TestFlag(g_SceneFlags, 2) != 0) {
        func_800AC218((g_BattleCurrentEnemy->slot - 3) & 0xFF, func_800AC704(0x96) & 0xFF);
    }
}
