#include "battle_03.h"

/* arms the queued selection from the pending slot: when already resolved it seeds the active battler's work
 * record and advances the panel state, otherwise it resolves the selection resource and queues the 30-frame event.
 */
MATCH void func_801D3A64(void) {
    u16 packed;

    g_BattleActionId = g_BattleAction->unk_02;
    if ((func_800A9B44() & BYTE_MASK) != 0) {
        func_801DDFEC(g_BattleActiveBattler);
        func_801DD14C(g_BattleActiveBattler);
        BATTLE_ACTIVE_PARTY.step_01 = 2;
        BATTLE_ACTIVE_PARTY.unk_02  = 0;
        g_BattleMode                = 3;
        g_BattleStep                = 0;
        g_BattleSubStep             = 0;
        return;
    }
    packed = g_BattleAction->unk_02;
    SYS_CopyString((u8*)&D_80149298, Item_GetRecord(packed >> 8, packed & BYTE_MASK), 0xC);
    func_801DE560(1, 1, 0, 0x1E, (u8*)&D_80149298);
    g_BattleRowCursor    = 0;
    g_BattleMessageState = 1;
    g_BattleUiStep += 1;
}
