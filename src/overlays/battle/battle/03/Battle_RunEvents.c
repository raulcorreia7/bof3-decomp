#include "battle_03.h"

/* func_801DE43C */
MATCH void Battle_RunEvents(void) {
    BattleHandlerTable5 handlers;
    u8                  group;
    s8                  slot_index;
    BattleEventSlot*    slot;
    ScratchPad*         sp;

    handlers           = g_BattleEvents;
    g_BattleEventFlags = 0u;
    for (group = 0u; group < 2u; group++) {
        for (slot_index = 0; slot_index < 8; slot_index++) {
            slot       = (BattleEventSlot*)&g_BattleEventSlots[slot_index * 12];
            D_801EB4DC = slot;
            if ((slot->unk_00 != 0u) && (slot->unk_03 == group) && ((slot->unk_01 & g_BattleEventFlags) == 0u)) {
                sp                       = SPAD(0u);
                sp->view.battle.state_00 = slot_index;
                handlers.handlers[slot->unk_01]();
            }
        }
    }
}
