#include "boss031_13.h"

MATCH void func_800C18E4(void) {
    EnemyBattler* work;

    Actor_RequestScript(1);
    ((Actor*)g_Task)->unk_2A = 1;
    func_8014DAEC();
    func_801E54EC();
    work = g_BattleCurrentEnemy;
    work->damage_flags |= COMBATANT_FLAG_SKIP_ACTION_STEP;
    TASK_BYTES[0] &= ~ACTOR_FLAG_HIDDEN;
    ACTOR_SET_STEP(3);
    TASK_BYTES[2] = 0;
    TASK_BYTES[3] = 0;
}
