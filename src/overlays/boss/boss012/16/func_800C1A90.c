#include "boss012_16.h"

MATCH void func_800C1A90(void) {
    EnemyBattler* work;

    GFX_PaletteFreeSlotOwner(g_Self);
    Battle_DefeatEnemy();
    work = g_BattleCurrentEnemy;
    work->turn.damage_flags.value |= BATTLER_DAMAGE_SKIP_ACTION_STEP;
    SELF(Actor)->header.flags &= ~ACTOR_FLAG_HIDDEN;
    ACTOR_SET_MODE(3);
    SELF(Actor)->header.step = 0;
    SELF(Actor)->unk_03      = 0;
}
