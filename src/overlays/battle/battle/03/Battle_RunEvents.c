#include "battle_03.h"

/* func_801DE43C */
MATCH void Battle_RunEvents(void) {
    BattleEventSteps handlers;
    u8               group;
    s8               event_slot;
    BattleEventSlot* slot;
    ScratchPad*      sp;

    handlers                     = g_BattleEvents;
    g_Battle.outcome.event_flags = 0u;
    for (group = 0u; group < 2u; group++) {
        for (event_slot = 0; event_slot < 8; event_slot++) {
            slot       = (BattleEventSlot*)&g_BattleEventSlots[event_slot * 12];
            D_801EB4DC = slot;
            if ((slot->unk_00 != 0u) && (slot->unk_03 == group) &&
                ((slot->unk_01 & g_Battle.outcome.event_flags) == 0u)) {
                sp                       = SPAD(0u);
                sp->view.battle.state_00 = event_slot;
                handlers.events[slot->unk_01]();
            }
        }
    }
}
