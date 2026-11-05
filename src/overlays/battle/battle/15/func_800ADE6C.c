#include "battle_15.h"

MATCH void func_800ADE6C(void) {
    PartyBattler* work;
    BattleSlot*   rows;
    BattleSlot*   row;
    s32           slot;

    if ((g_MenuPanelTasks[19].unk_00[0] & 1) == 0) {
        BATTLE_WORK->step_01 = 2;
        BATTLE_WORK->unk_02  = 0;
        return;
    }
    if ((s16)g_MenuPanelTasks[19].unk_1E != (s16)g_MenuPanelTasks[19].unk_12) {
        BATTLE_WORK->step_01 = 0;
        return;
    }
    work              = BATTLE_WORK;
    work->unk_2E.half = g_MenuPanelTasks[19].x + (work->word_08.byte.timer_0A * 0x16 + 0x44);
    work->unk_30.half = g_MenuPanelTasks[19].y + (work->word_08.byte.unk_09 * 0x20 + 0x22);
    rows              = D_80145518;
    row               = &rows[(s16)g_MenuPanelTasks[19].unk_12 + work->word_08.byte.unk_09];
    slot              = (&row->slot_00)[work->word_08.byte.timer_0A];
    if (slot != GAME_NONE) {
        Actor_RequestScript(slot);
        /* FAKE: opaque slot so CSE cannot fold the second test. */
        MATCH_FAKE_OPAQUE(slot);
    }
    if (slot != GAME_NONE) {
        func_8014D978();
        Area_AddActor();
    }
}
