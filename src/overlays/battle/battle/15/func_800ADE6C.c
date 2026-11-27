#include "battle_15.h"

MATCH void func_800ADE6C(void) {
    PartyMember* work;
    BattleSlot*  entries;
    BattleSlot*  entry;
    s32          slot;

    if ((g_UiPanelTasks[19].active & 0x1) == 0) {
        SELF(PartyMember)->header.mode = 2;
        SELF(PartyMember)->header.step = 0;
        return;
    }
    if ((s16)g_UiPanelTasks[19].u.addr.unk_1E != (s16)g_UiPanelTasks[19].u.battle.row_base) {
        SELF(PartyMember)->header.mode = 0;
        return;
    }
    work                 = SELF(PartyMember);
    work->screen_x.value = g_UiPanelTasks[19].pos.vx + (work->timer * 0x16 + 0x44);
    work->screen_y.value = g_UiPanelTasks[19].pos.vy + (work->unk_09 * 0x20 + 0x22);
    entries              = D_80145518;
    entry                = &entries[(s16)g_UiPanelTasks[19].u.battle.row_base + work->unk_09];
    slot                 = (&entry->slot_00)[work->timer];
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
