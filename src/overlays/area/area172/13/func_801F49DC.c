#include "area172_13.h"

MATCH void func_801F49DC(void) {
    s32 actor_index;

    actor_index = Actor_FindFreeSlot() & BYTE_MASK;
    if (actor_index != GAME_NONE) {
        g_ActorSlots[actor_index].header.flags = ACTOR_FLAG_IN_USE;
        g_ActorSlots[actor_index].type         = 0x92;
        g_ActorSlots[actor_index].unk_29       = 4;
        g_ActorSlots[actor_index].unk_2E       = 0;
        g_ActorSlots[actor_index].unk_30       = 0;
        g_ActorSlots[actor_index].link         = g_CurrentActor - g_Actors;
    }
}
