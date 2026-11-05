#include "area132_13.h"

MATCH void func_801F3C1C(void) {
    s32        slot_index;
    ActorSlot* slot;

    slot_index = Actor_FindFreeSlot() & BYTE_MASK;
    if (slot_index == GAME_NONE) {
        return;
    }
    slot          = &g_ActorSlots[slot_index];
    slot->flags   = 1;
    slot->type    = 0x74;
    slot->x.fixed = 0x2B0000;
    slot->y.fixed = 0x280000;
    slot->z.fixed = Area_SampleHeight(slot->x.fixed, 0x280000) << 16;
}
