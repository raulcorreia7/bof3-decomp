#include "battle_15.h"

MATCH void func_800ADE6C(void) {
    PartyMember* work;
    BattleSlot*  rows;
    BattleSlot*  row;
    s32          slot;

    if ((g_MenuPanelTasks[19].active & 0x1) == 0) {
        BATTLE_WORK->header.mode = 2;
        BATTLE_WORK->header.step = 0;
        return;
    }
    if ((s16)g_MenuPanelTasks[19].u.addr.unk_1E != (s16)g_MenuPanelTasks[19].u.battle.row_base) {
        BATTLE_WORK->header.mode = 0;
        return;
    }
    work              = BATTLE_WORK;
    work->unk_2E.half = g_MenuPanelTasks[19].pos.x + (work->timer * 0x16 + 0x44);
    work->unk_30.half = g_MenuPanelTasks[19].pos.y + (work->unk_09 * 0x20 + 0x22);
    rows              = D_80145518;
    row               = &rows[(s16)g_MenuPanelTasks[19].u.battle.row_base + work->unk_09];
    slot              = (&row->slot_00)[work->timer];
    if (slot != GAME_NONE) {
        Actor_RequestScript(slot);
        /* FAKE: opaque slot so CSE cannot fold the second test. */
        FAKE_OPAQUE(slot);
    }
    if (slot != GAME_NONE) {
        Actor_StepAnimLoop();
        Area_AddActor();
    }
}
