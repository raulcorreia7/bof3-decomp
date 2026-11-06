#include "boss038_16.h"
#include "game/enemy.h"

MATCH void func_800C1848(void) {
    g_BattleCurrentEnemy->script = D_800C1C10;
    g_BattleCurrentEnemy->unk_E4 = func_800C18EC;
    g_BattleCurrentEnemy->unk_E8 = D_800C1C1C;
    g_BattleCurrentEnemy->turn.action_flags.value |= 8;
    g_Task->header.mode = 2;
    func_8014D978();
    if (SYS_TestFlag(g_SceneFlags, 2) != 0) {
        Battle_LoadEnemyBattler((g_BattleCurrentEnemy->slot - 3) & 0xFF, func_800AC704(ENEMY_ID_AMMONITE_ALT) & 0xFF);
    }
}
