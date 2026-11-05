#include "boss055_16.h"

MATCH void func_800C1CFC(void) {
    EnemyBattler* work;

    func_8014DAEC();
    func_801E54EC();
    GFX_FreePaletteSlotOwner((s32)g_SpadWork);
    work = g_BattleCurrentEnemy;
    work->flags_100 |= COMBATANT_FLAG_SKIP_ACTION_STEP;
    SPAD_WORK_BYTES[0] &= ~ACTOR_FLAG_HIDDEN;
    ACTOR_SET_STEP(2);
    SPAD_WORK_BYTES[2] = 0;
    SPAD_WORK_BYTES[3] = 0;
}
