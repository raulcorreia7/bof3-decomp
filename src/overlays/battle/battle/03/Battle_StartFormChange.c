#include "battle_03.h"

/* sets the selected local record flag, advances its state, and moves
 * the shared battle work counter forward.
 */
/* func_801E7888 */
MATCH void Battle_StartFormChange(void) {
    PartyMember* work;
    u8           selection;

    selection = g_BattleEffectBattler->slot;
    g_Game.members[selection].u.turn.damage_flags.value |= BATTLER_DAMAGE_FORM_EFFECT_PLAYING;
    g_BattleEffectBattler->unk_48 = 2u;
    work                          = SELF(PartyMember);
    work->header.mode++;
}
