#include "boss012_16.h"

MATCH void func_800C1A90(void) {
    EnemyBattler* work;

    GFX_FreePaletteSlotOwner(g_Task);
    func_801E54EC();
    work = g_BattleCurrentEnemy;
    work->damage_flags |= COMBATANT_FLAG_SKIP_ACTION_STEP;
    TASK_BYTES[0] &= ~ACTOR_FLAG_HIDDEN;
    ACTOR_SET_STEP(3);
    TASK_BYTES[2] = 0;
    TASK_BYTES[3] = 0;
}
