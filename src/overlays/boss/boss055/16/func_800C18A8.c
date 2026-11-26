#include "boss055_16.h"

MATCH void func_800C18A8(void) {
    EnemyBattler* enemy;

    enemy           = g_BattleCurrentEnemy;
    g_Battle.unk_DE = 0;
    EnemyBattler_SetScript(enemy, D_800C34F0, (EnemyScriptCallback)func_800C22F0, D_800C34FC);
    enemy->unk_29 = 6;
    enemy->turn.action_flags.value |= BATTLER_ACTION_OWN_MODE;
    Battle_RequestEnemyScript(0);
    func_800C238C(0, 6);
    func_800C238C(1, 6);
    func_800C238C(2, 6);
    func_80196CF0(g_Self, D_800C352C);
    SELF(PartyMember)->header.mode = 2;
    Script_AnimStepLoop();
}
