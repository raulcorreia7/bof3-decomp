#include "boss052_16.h"

MATCH void func_800C18FC(void) {
    Actor_RequestScript(3);
    func_8014DAEC();
    func_801E54EC();
    g_BattleCurrentEnemy->damage_flags |= COMBATANT_FLAG_SKIP_ACTION_STEP;
    TASK_BYTES[0] &= ~ACTOR_FLAG_HIDDEN;
    ACTOR_SET_STEP(3);
    TASK_BYTES[2] = 0;
    TASK_BYTES[3] = 0;
}
