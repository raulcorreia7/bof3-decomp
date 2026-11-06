#include "area077_14.h"

MATCH void func_801F61F0(s32 type) {
    ActorSlot* record;
    u8         slot;

    slot = Actor_FindFreeSlot();
    if (slot != 0xFF) {
        record               = &g_ActorSlots[slot];
        record->header.flags = 1;
        record->type         = type;
    }
}
