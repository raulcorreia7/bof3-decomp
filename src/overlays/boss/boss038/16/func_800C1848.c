#include "boss038_16.h"
#include "game/enemy.h"

MATCH void func_800C1848(void) {
    g_BattleCurrentEnemy->script = g_BossEnemyScript;
    g_BattleCurrentEnemy->unk_E4 = func_800C18EC;
    g_BattleCurrentEnemy->unk_E8 = g_BossEnemyActions;
    g_BattleCurrentEnemy->turn.action_flags.value |= COMBATANT_FLAG_MODE_HANDLER_ACTION;
    g_Task->header.mode = 2;
    Actor_StepAnimLoop();
    if (SYS_TestFlag(g_SceneFlags, 2) != 0) {
        Battle_LoadEnemyBattler((g_BattleCurrentEnemy->slot - 3) & BYTE_MASK, func_800AC704(ENEMY_ID_AMMONITE_ALT) & BYTE_MASK);
    }
}
