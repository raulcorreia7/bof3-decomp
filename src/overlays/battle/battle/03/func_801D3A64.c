#include "battle_03.h"

/* arms the queued selection from the pending slot: when already resolved it seeds the active battler's work
 * record and advances the panel state, otherwise it resolves the selection resource and queues the 30-frame event.
 */
MATCH void func_801D3A64(void) {
    u16 packed;

    g_Battle.action_id = g_Battle.action->unk_02;
    if ((func_800A9B44() & BYTE_MASK) != 0) {
        Battle_GetTurnCursor(g_Battle.active_battler);
        Battle_CancelTurn(g_Battle.active_battler);
        BATTLE_ACTIVE_PARTY.header.mode = 2;
        BATTLE_ACTIVE_PARTY.header.step = 0;
        g_Battle.phase.mode             = BATTLE_MODE_TURNS;
        g_Battle.phase.step             = 0;
        g_Battle.phase.sub_step         = 0;
        return;
    }
    packed = g_Battle.action->unk_02;
    SYS_CopyString((u8*)&D_80149298, Item_GetRecord(packed >> 8, packed & BYTE_MASK), 12);
    Battle_QueueEvent(1, 1, 0, 30, (u8*)&D_80149298);
    g_Battle.row_cursor  = 0;
    g_BattleMessageState = 1;
    g_Battle.ui_step += 1;
}
