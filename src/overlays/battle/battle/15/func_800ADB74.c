#include "battle_15.h"

MATCH void func_800ADB74(void) {
    PartyMember* work;
    BattleSlot*  rows;
    BattleSlot*  row;
    s32          slot;

    if ((g_UiPanelTasks[18].active & 0x1) == 0) {
        BATTLE_WORK->header.mode = 2;
        BATTLE_WORK->header.step = 0;
        return;
    }
    if ((s16)g_UiPanelTasks[18].u.addr.unk_1E != (s16)g_UiPanelTasks[18].u.battle.row_base) {
        BATTLE_WORK->header.mode = 0;
        return;
    }
    work                 = BATTLE_WORK;
    work->screen_x.value = g_UiPanelTasks[18].pos.x + (work->timer * 0x16 + 0x44);
    work->screen_y.value = g_UiPanelTasks[18].pos.y + (work->unk_09 * 0x20 + 0x22);
    rows                 = g_BattleTargetRows;
    row                  = &rows[(s16)g_UiPanelTasks[18].u.battle.row_base + work->unk_09];
    slot                 = (&row->slot_00)[work->timer];
    if (slot != GAME_NONE) {
        Script_Request(slot);
        /* FAKE: opaque slot so CSE cannot fold the second test. */
        FAKE_OPAQUE(slot);
    }
    if (slot != GAME_NONE) {
        Script_AnimStepLoop();
        Area_AddActor();
    }
}
