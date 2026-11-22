#include "boss032_16.h"

MATCH void func_800C18F0(void) {
    Script_Request(0);
    Script_AnimStepOnce();
    Battle_DefeatEnemy();
    g_BattleCurrentEnemy->turn.damage_flags.value |= BATTLER_DAMAGE_SKIP_ACTION_STEP;
    g_Task->header.flags &= ~ACTOR_FLAG_HIDDEN;
    ACTOR_SET_MODE(3);
    g_Task->header.step = 0;
    g_Task->unk_03      = 0;
}
