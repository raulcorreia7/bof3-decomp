#include "engine/slus/slus.h"

/* claims the record slot returned by Actor_FindFreeSlot and fills it: flag
 * and kind bytes, the caller's byte argument, two sign-extended byte fields and
 * three coordinate fields; a slot index of 0xFF is left untouched.
 */
MATCH s32 func_8015CC00(u8 id, s32 step, s32 selection, s32 x, s32 y, s32 z) {
    s32 slot_index;
    u32 offset;

    slot_index = Actor_FindFreeSlot() & BYTE_MASK;
    if (slot_index != GAME_NONE) {
        offset                                = (u32)slot_index * 0x74u;
        g_ActorSlots[slot_index].flags        = 1;
        g_ActorSlots[slot_index].type         = 0x19;
        g_ActorSlots[slot_index].unk_06       = id;
        g_ActorSlots[slot_index].step_0C      = (s8)step;
        g_ActorSlots[slot_index].selection_10 = (s8)selection;
        g_ActorSlots[slot_index].x.fixed      = x;
        g_ActorSlots[slot_index].y.fixed      = y;
        g_ActorSlots[slot_index].z.fixed      = z;
    }
    return slot_index;
}
