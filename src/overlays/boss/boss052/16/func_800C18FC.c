#include "boss052_16.h"
#include "area/spad.h"

MATCH void func_800C18FC(void) {
    Actor_RequestScript(3);
    Actor_StepAnimOnce();
    Battle_DefeatEnemy();
    g_BattleCurrentEnemy->turn.damage_flags.value |= COMBATANT_FLAG_SKIP_ACTION_STEP;
    g_Task->header.flags &= ~ACTOR_FLAG_HIDDEN;
    ACTOR_SET_MODE(3);
    g_Task->header.step = 0;
    g_Task->unk_03      = 0;
}
