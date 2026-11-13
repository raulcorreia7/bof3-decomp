#include "area145_14.h"

MATCH u8 func_801F5190(s32 x1, s32 y1, s32 x2, s32 y2) {
    u8 slot;

    slot          = Actor_FindFreeSlot();
    D_1F800000[0] = slot;
    if (slot != GAME_NONE) {
        g_ActorSlots[slot].header.flags        = ACTOR_FLAG_IN_USE;
        g_ActorSlots[D_1F800000[0]].type       = 0x3F;
        g_ActorSlots[D_1F800000[0]].scene_step = x1;
        g_ActorSlots[D_1F800000[0]].selection  = y1;
        g_ActorSlots[D_1F800000[0]].counter_18 = x2;
        g_ActorSlots[D_1F800000[0]].counter_1C = y2;
        slot                                   = D_1F800000[0];
        g_ActorSlots[slot].unk_20              = 0x500000;
        g_ActorSlots[slot].unk_14              = 0x500000;
        return 0;
    }
    return 1;
}
