#include "area173_14.h"

MATCH void func_801F4ADC(void) {
    s32 actor_index;

    actor_index = Actor_FindFreeSlot() & BYTE_MASK;
    if (actor_index != GAME_NONE) {
        g_SpawnedActors[actor_index].header.flags = ACTOR_FLAG_IN_USE;
        g_SpawnedActors[actor_index].type         = 0x9D;
        g_SpawnedActors[actor_index].unk_2E       = 0xC;
        g_SpawnedActors[actor_index].unk_06       = 0;
        g_SpawnedActors[actor_index].unk_30       = 0xA5;
        g_SpawnedActors[actor_index].link         = g_CurrentActor - g_Actors;
    }
}
