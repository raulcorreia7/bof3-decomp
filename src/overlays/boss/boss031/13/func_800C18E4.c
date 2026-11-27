#include "boss031_13.h"

MATCH void func_800C18E4(void) {
    EnemyBattler* work;

    Script_Request(1);
    SELF(Actor)->mirror = 1;
    Script_AnimStepOnce();
    Battle_DefeatEnemy();
    work = g_BattleCurrentEnemy;
    work->turn.damage_flags.value |= BATTLER_DAMAGE_SKIP_ACTION_STEP;
    SELF(Actor)->header.flags &= ~ACTOR_FLAG_HIDDEN;
    ACTOR_SET_MODE(3);
    SELF(Actor)->header.step = 0;
    SELF(Actor)->unk_03      = 0;
}
