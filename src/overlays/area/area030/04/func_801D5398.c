#include "area030_04.h"

/* Arms the panel window and cursor row, counts the panel timer down
 * and, at zero, claims a free entry row for the selected scene and advances the
 * work state. */
/* FAKE: retail reads the distance halfword unsigned (lhu). */
MATCH void func_801D5398(void) {
    FishingState* work;
    s32           index;
    s32           mask;

    func_801D9534(0x14, 0x12, 0x118, 0x13, 0);

    mask = 0;
    if (D_80145E93[0] >= 3) {
        mask = (1 << FISHING_STATE->cue_index_06) & BYTE_MASK;
    }
    func_801D7C10(0x58, 0x28, mask);

    work                = FISHING_STATE;
    work->step_timer_09 = (u8)(work->step_timer_09 - 1);
    func_801D72E4(0x27, (s16)(FISHING_STATE->step_timer_09 * 0x3C + 0x40));

    if (FISHING_STATE->step_timer_09 == 0) {
        index                     = Actor_FindFreeSlot() & BYTE_MASK;
        g_ActorSlots[index].flags = 1;
        g_ActorSlots[index].type  = 0x1A;
        g_ActorSlots[index].mode  = 0x10;
        g_ActorSlots[index].step  = (u8) * (u16*)&g_Task->z.part.integer;

        work                   = FISHING_STATE;
        work->handler_index_01 = (u8)(work->handler_index_01 + 1);
    }
}
