#include "battle_03.h"

/* clears the work flag and, when the fade counter reaches its
 * threshold, clears the slot's paired flag words before running the shared
 * battle step; otherwise advances the counter.
 *
 * The non-volatile view of g_BattleEffectBattler is load-bearing: retail's counter store
 * sits in the return-jump delay slot, which the assembler's delay-slot
 * filling only moves for a non-volatile store.
 */
MATCH void func_801E8D04(void) {
    u32 value;

    BATTLE_ACTIVE_WORK->header.flags &= ~PARTY_MEMBER_FLAG_HANDLER_BUSY;
    value = BATTLE_ACTIVE_WORK->scale.x;
    if (value != 0x10000) {
        BATTLE_ACTIVE_WORK->scale.x = value + 0x2000;
        return;
    }
    BATTLE_ACTIVE_WORK->unk_48 = 0;
    g_Game.members[BATTLE_ACTIVE_WORK->slot].u.turn.damage_flags.value &= ~COMBATANT_FLAG_FORM_EFFECT_PLAYING;
    g_Game.members[BATTLE_ACTIVE_WORK->slot].u.turn.action_flags.value &=
        ~(COMBATANT_FLAG_DRAGON_FORM | COMBATANT_FLAG_ABILITY_ALT_POSE | COMBATANT_FLAG_DRAGON_FORM_BERSERK | COMBATANT_FLAG_DRAGON_FORM_CONTROLLED);
    Effect_Reset();
}
