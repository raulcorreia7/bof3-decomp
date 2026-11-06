#include "boss021_16.h"

MATCH void func_800C18FC(void) {
    EnemyBattler* work;

    Actor_RequestScript(4);
    ((Actor*)g_Task)->unk_2A = 0;
    func_8014DAEC();
    Battle_CollectEnemySpoils();
    work = g_BattleCurrentEnemy;
    work->damage_flags |= COMBATANT_FLAG_SKIP_ACTION_STEP;
    TASK_BYTES[0] &= ~ACTOR_FLAG_HIDDEN;
    ACTOR_SET_MODE(3);
    TASK_BYTES[2] = 0;
    TASK_BYTES[3] = 0;
}
