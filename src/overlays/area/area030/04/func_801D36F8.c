#include "area030_04.h"

/* TODO */
MATCH void func_801D36F8(void) {
    FishingState* record;
    s8            slot;
    u8            area;

    record = FISHING_STATE;
    if (D_801E1F20[record->cue_index_06][3] != 0) {
        slot = Actor_FindFreeSlot();
        if (slot != -1) {
            g_ActorSlots[slot].flags_00 = 1;
            g_ActorSlots[slot].type     = 0xF;
            area                        = FISHING_STATE->cue_index_06;
            g_ActorSlots[slot].unk_4A   = 0;
            g_ActorSlots[slot].link_0B  = 0;
            g_ActorSlots[slot].unk_01   = 8;
            g_ActorSlots[slot].unk_06   = area;
        }
        FISHING_STATE->handler_index_01 = 6;
    } else {
        record->row_4B                  = D_801E1F20[record->cue_index_06][0];
        FISHING_STATE->handler_index_01 = FISHING_STATE->handler_index_01 + 1;
    }
    func_801D9534(0x14, 0x12, 0x118, 0x13, 0);
}
