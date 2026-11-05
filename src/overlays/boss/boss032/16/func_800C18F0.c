#include "boss032_16.h"

MATCH void func_800C18F0(void) {
    Actor_RequestScript(0);
    func_8014DAEC();
    func_801E54EC();
    g_BattleCurrentEnemy->flags_100 |= COMBATANT_FLAG_SKIP_ACTION_STEP;
    TASK_BYTES[0] &= ~ACTOR_FLAG_HIDDEN;
    ACTOR_SET_STEP(3);
    TASK_BYTES[2] = 0;
    TASK_BYTES[3] = 0;
}
