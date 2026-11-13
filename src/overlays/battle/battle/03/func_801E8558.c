#include "battle_03.h"

/* clears the work record's 0x40 flag and advances the step word by 0x2000 until it reaches 0x10000; on
 * completion it clears the 0x48 byte, drops the 0x2000 flag on the owner's damage row and the low suppress bits, then
 * runs the queued step.
 */
MATCH void func_801E8558(void) {
    PartyMember* work;
    PartyMember* stage;
    u32          step;

    g_BattleEffectBattler->header.flags &= ~ACTOR_FLAG_HIDDEN;
    stage = g_BattleEffectBattler;
    step  = stage->scale.x;
    if (step != 0x10000) {
        stage->scale.x = step + 0x2000;
        return;
    }
    stage->unk_48 = 0;
    work          = g_BattleEffectBattler;
    g_Game.members[work->slot].u.turn.damage_flags.value &= ~COMBATANT_FLAG_FORM_EFFECT_PLAYING;
    g_Game.members[work->slot].u.turn.action_flags.value &=
        ~(COMBATANT_FLAG_DRAGON_FORM | COMBATANT_FLAG_ABILITY_ALT_POSE | COMBATANT_FLAG_DRAGON_FORM_BERSERK | COMBATANT_FLAG_DRAGON_FORM_CONTROLLED);
    Effect_Reset();
}
