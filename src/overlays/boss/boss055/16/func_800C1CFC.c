#include "boss055_16.h"

MATCH void func_800C1CFC(void) {
    EnemyBattler* work;

    func_8014DAEC();
    Battle_DefeatEnemy();
    GFX_FreePaletteSlotOwner(g_Task);
    work = g_BattleCurrentEnemy;
    work->turn.damage_flags.value |= COMBATANT_FLAG_SKIP_ACTION_STEP;
    g_Task->header.flags &= ~ACTOR_FLAG_HIDDEN;
    ACTOR_SET_MODE(2);
    g_Task->header.step = 0;
    g_Task->unk_03      = 0;
}
