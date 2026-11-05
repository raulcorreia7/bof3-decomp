#include "boss012_16.h"

MATCH void func_800C1A90(void) {
    EnemyBattler* work;

    GFX_FreePaletteSlotOwner((s32)g_SpadWork);
    func_801E54EC();
    work = g_BattleCurrentEnemy;
    work->flags_100 |= COMBATANT_FLAG_SKIP_ACTION_STEP;
    SPAD_WORK_BYTES[0] &= ~ACTOR_FLAG_HIDDEN;
    ACTOR_SET_STEP(3);
    SPAD_WORK_BYTES[2] = 0;
    SPAD_WORK_BYTES[3] = 0;
}
