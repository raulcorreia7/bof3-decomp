#include "area047_13.h"

MATCH void func_801F396C(void) {
    s32        slot_index;
    ActorSlot* slot;

    slot_index = Actor_FindFreeSlot() & BYTE_MASK;
    if (slot_index == GAME_NONE) {
        return;
    }
    slot        = &g_ActorSlots[slot_index];
    slot->flags = 1;
    slot->type  = 0x3D;
}
