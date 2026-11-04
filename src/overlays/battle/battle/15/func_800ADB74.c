#include "battle_15.h"

MATCH void func_800ADB74(void) {
    PartyBattler* work;
    BattleSlot*   rows;
    BattleSlot*   row;
    s32           slot;

    if ((g_MenuPanelTasks[18].unk_00[0] & 1) == 0) {
        BATTLE_WORK->step_01 = 2;
        BATTLE_WORK->unk_02  = 0;
        return;
    }
    if ((s16)g_MenuPanelTasks[18].unk_1E != (s16)g_MenuPanelTasks[18].unk_12) {
        BATTLE_WORK->step_01 = 0;
        return;
    }
    work              = BATTLE_WORK;
    work->unk_2E.half = g_MenuPanelTasks[18].x + (work->word_08.byte.unk_0A * 0x16 + 0x44);
    work->unk_30.half = g_MenuPanelTasks[18].y + (work->word_08.byte.unk_09 * 0x20 + 0x22);
    rows              = g_BattleTargetRows;
    row               = &rows[(s16)g_MenuPanelTasks[18].unk_12 + work->word_08.byte.unk_09];
    slot              = (&row->slot_00)[work->word_08.byte.unk_0A];
    if (slot != GAME_NONE) {
        Actor_RequestScript(slot);
        /* Retail threads the first test to the exit and keeps the second;
         * pure C folds the second test (76.32%), so the slot stays opaque
         * across the call. */
        /* FAKE: opaque slot so CSE cannot fold the second test. */
        MATCH_FAKE_OPAQUE(slot);
    }
    if (slot != GAME_NONE) {
        func_8014D978();
        Area_AddActor();
    }
}
