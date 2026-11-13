#include "battle_03.h"

/* clears one local work flag bit, then either integrates the local
 * velocity or resets the step and clears the selected record's pending flag.
 */
MATCH void func_801E7778(void) {
    PartyMember* work;
    u8           flag;
    u32          index;
    u32          step;
    u32          value;

    g_BattleEffectBattler->header.flags &= ~ACTOR_FLAG_HIDDEN;
    work = g_BattleEffectBattler;
    step = work->scale.x;
    if (step != 0x10000) {
        work->scale.x = step + 0x2000;
    } else {
        work->unk_48                                    = 0;
        index                                           = g_BattleEffectBattler->slot;
        value                                           = g_Game.members[index].u.turn.damage_flags.value & ~COMBATANT_FLAG_FORM_EFFECT_PLAYING;
        g_Game.members[index].u.turn.damage_flags.value = value;
        Effect_Reset();
    }
}
