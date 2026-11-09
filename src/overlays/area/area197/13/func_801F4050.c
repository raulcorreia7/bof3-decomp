#include "area197_13.h"

MATCH void func_801F4050(void) {
    s32 actor_index;

    actor_index = Actor_FindFreeSlot() & 0xFF;
    if (actor_index != 0xFF) {
        g_ActorSlots[actor_index].header.flags = ACTOR_FLAG_IN_USE;
        g_ActorSlots[actor_index].type         = 0x92;
        *(s16*)&g_ActorSlots[actor_index].unk_30 = -0x1E;
        g_ActorSlots[actor_index].unk_29       = 6;
        g_ActorSlots[actor_index].unk_2E       = 0;
        g_ActorSlots[actor_index].link         = g_CurrentActor - g_Actors;
    }
}
