#include "battle_15.h"

MATCH void func_800ADB74(void) {
    PartyMember* work;
    BattleSlot*  entries;
    BattleSlot*  entry;
    s32          slot;

    if ((g_UIPanelTasks[18].active & 0x1) == 0) {
        SELF(PartyMember)->header.mode = 2;
        SELF(PartyMember)->header.step = 0;
        return;
    }
    if ((s16)g_UIPanelTasks[18].u.addr.unk_1E != (s16)g_UIPanelTasks[18].u.battle.row_base) {
        SELF(PartyMember)->header.mode = 0;
        return;
    }
    work                 = SELF(PartyMember);
    work->screen_x.value = g_UIPanelTasks[18].pos.vx + (work->timer * 0x16 + 0x44);
    work->screen_y.value = g_UIPanelTasks[18].pos.vy + (work->unk_09 * 0x20 + 0x22);
    entries              = g_BattleTargetRows;
    entry                = &entries[(s16)g_UIPanelTasks[18].u.battle.row_base + work->unk_09];
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
