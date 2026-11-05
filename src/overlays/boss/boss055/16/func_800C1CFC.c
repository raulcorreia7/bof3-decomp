#include "boss055_16.h"

MATCH void func_800C1CFC(void) {
    EnemyBattler* work;

    func_8014DAEC();
    func_801E54EC();
    GFX_FreePaletteSlotOwner((s32)g_Task);
    work = g_BattleCurrentEnemy;
    work->damage_flags |= COMBATANT_FLAG_SKIP_ACTION_STEP;
    TASK_BYTES[0] &= ~ACTOR_FLAG_HIDDEN;
    ACTOR_SET_STEP(2);
    TASK_BYTES[2] = 0;
    TASK_BYTES[3] = 0;
}
