#include "game_00.h"

MATCH void func_801B80B4(void) {
    s32 next_step;

    g_Task->unk_09 = (u8)(g_Task->unk_09 - 1);
    if (g_Task->unk_09 != 0) {
        return;
    }
    g_Task->unk_0A = (u8)(g_Task->unk_0A + 1);
    if (g_Task->direction_08 == 3) {
        next_step = 7;
        next_step -= g_Task->unk_0A;
    } else {
        next_step = g_Task->unk_0A;
        next_step += 1;
    }
    Actor_RequestScript((u8)next_step);
    if (g_Task->unk_0A == 4) {
        if (g_Task->unk_05 == 0) {
            g_AreaWalkFlags &= ~AREA_WALK_ENTRY_ACTIVE;
        }
        g_Task->unk_09 = 0;
        g_Task->unk_0A = 0;
        g_Task->mode   = 1;
        ACTOR_CLEAR_STATE();
        g_Task->unk_03 = 0;
        g_Task->unk_04 = 0;
    } else {
        g_Task->unk_09 = 2;
    }
}
