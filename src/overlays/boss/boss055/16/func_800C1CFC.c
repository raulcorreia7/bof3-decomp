#include "boss055_16.h"

MATCH void func_800C1CFC(void) {
    EnemyBattler* work;

    Script_AnimStepOnce();
    Battle_DefeatEnemy();
    GFX_PaletteFreeSlotOwner(g_Self);
    work = g_BattleCurrentEnemy;
    work->turn.damage_flags.value |= BATTLER_DAMAGE_SKIP_ACTION_STEP;
    SELF(PartyMember)->header.flags &= ~ACTOR_FLAG_HIDDEN;
    ACTOR_SET_MODE(2);
    SELF(PartyMember)->header.step = 0;
    SELF(PartyMember)->unk_03      = 0;
}
