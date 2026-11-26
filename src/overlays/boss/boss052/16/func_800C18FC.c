#include "boss052_16.h"

MATCH void func_800C18FC(void) {
    Script_Request(3);
    Script_AnimStepOnce();
    Battle_DefeatEnemy();
    g_BattleCurrentEnemy->turn.damage_flags.value |= BATTLER_DAMAGE_SKIP_ACTION_STEP;
    SELF(Actor)->header.flags &= ~ACTOR_FLAG_HIDDEN;
    ACTOR_SET_MODE(3);
    SELF(Actor)->header.step = 0;
    SELF(Actor)->unk_03      = 0;
}
