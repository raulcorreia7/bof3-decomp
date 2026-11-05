#include "battle_03.h"

/* sets the selected local record flag, advances its state, and moves
 * the shared battle work counter forward.
 */
MATCH void func_801E7888(void) {
    PartyBattler* work;
    u8            selection;

    selection = D_801EB4E0->slot;
    g_BattlePartyBattlers[selection].flags_124.value |= 0x2000u;
    D_801EB4E0->unk_48 = 2u;
    work               = g_Task;
    work->mode++;
}
