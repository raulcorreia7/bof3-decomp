#include "boss031_13.h"

MATCH void func_800C18E4(void) {
    EnemyBattler* work;

    Actor_RequestScript(1);
    ((Actor*)g_Task)->unk_2A = 1;
    func_8014DAEC();
    Battle_DefeatEnemy();
    work = g_BattleCurrentEnemy;
    work->turn.damage_flags.value |= COMBATANT_FLAG_SKIP_ACTION_STEP;
    TASK_BYTES[0] &= ~ACTOR_FLAG_HIDDEN;
    ACTOR_SET_MODE(3);
    TASK_BYTES[2] = 0;
    TASK_BYTES[3] = 0;
}
