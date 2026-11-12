#include "area145_14.h"

MATCH u8 func_801F5190(s32 scene_step, s32 selection, s32 counter_18, s32 counter_1C) {
    u8 slot;

    slot          = Actor_FindFreeSlot();
    D_1F800000[0] = slot;
    if (slot != GAME_NONE) {
        g_ActorSlots[slot].header.flags        = 1;
        g_ActorSlots[D_1F800000[0]].type       = 0x3F;
        g_ActorSlots[D_1F800000[0]].scene_step = scene_step;
        g_ActorSlots[D_1F800000[0]].selection  = selection;
        g_ActorSlots[D_1F800000[0]].counter_18 = counter_18;
        g_ActorSlots[D_1F800000[0]].counter_1C = counter_1C;
        slot                                   = D_1F800000[0];
        g_ActorSlots[slot].unk_20              = 0x500000;
        g_ActorSlots[slot].unk_14              = 0x500000;
        return 0;
    }
    return 1;
}
