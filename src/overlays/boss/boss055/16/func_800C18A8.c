#include "boss055_16.h"

MATCH void func_800C18A8(void) {
    EnemyBattler* enemy;

    enemy           = g_BattleCurrentEnemy;
    g_Battle.unk_DE = 0;
    EnemyBattler_SetScript(enemy, D_800C34F0, (ModeFunc)func_800C22F0, D_800C34FC);
    enemy->unk_29 = 6;
    enemy->turn.action_flags.value |= COMBATANT_FLAG_MODE_HANDLER_ACTION;
    func_801E2314(0);
    func_800C238C(0, 6);
    func_800C238C(1, 6);
    func_800C238C(2, 6);
    func_80196CF0(g_Task, D_800C352C);
    g_Task->header.mode = 2;
    Actor_StepAnimLoop();
}
