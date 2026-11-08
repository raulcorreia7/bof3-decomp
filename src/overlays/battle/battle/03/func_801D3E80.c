#include "battle_03.h"

MATCH void func_801D3E80(void) {
    s32 voice;
    u16 selection;
    u32 entry_index;
    u8* counter;

    for (voice = 16; (voice & BYTE_MASK) < 24u; voice++) {
        SsUtKeyOffV(voice & BYTE_MASK);
    }

    if (LOBU(g_BattleActionType) == BATTLE_ACTION_ABILITY) {
        entry_index = g_BattleActionSelection[LOHU(g_BattleActionId)];
        /* mode 4 shares the stream-entry test below */
        goto check_entry;
    }
    if (LOBU(g_BattleActionType) == BATTLE_ACTION_ITEM) {
        selection   = g_BattleAction->unk_02;
        entry_index = D_800B6AB0[selection >> 8][selection & BYTE_MASK];
    check_entry:
        if (g_BattleSelections[entry_index].id != 0xFFFFu) {
            EMI_LoadArchive(EMI_SLOT_BATL_RET);
        }
    }
    counter = &g_BattleSubStep;
    *counter += 1u;
}
