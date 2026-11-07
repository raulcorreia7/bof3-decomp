#include "battle_03.h"

/* sets the selected local record flag, advances its state, and moves
 * the shared battle work counter forward.
 */
MATCH void func_801E7888(void) {
    PartyBattler* work;
    u8            selection;

    selection = g_BattleEffectBattler->slot;
    g_BattlePartyBattlers[selection].turn.damage_flags.value |= COMBATANT_FLAG_FORM_EFFECT_PLAYING;
    g_BattleEffectBattler->unk_48 = 2u;
    work                          = g_Task;
    work->header.mode++;
}
