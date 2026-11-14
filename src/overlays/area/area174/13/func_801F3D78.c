#include "area174_13.h"

MATCH void func_801F3D78(void) {
    u8  actor_slot;
    s32 link;

    actor_slot = Actor_FindFreeSlot();
    if (actor_slot != GAME_NONE) {
        g_SpawnedActors[actor_slot].header.flags = 1;
        g_SpawnedActors[actor_slot].type         = 0x9D;
        g_SpawnedActors[actor_slot].unk_06       = 0;
        g_SpawnedActors[actor_slot].unk_30       = 0xA5;
        link                                  = (s32)(-(((s32)g_CurrentActor - (s32)g_Actors) * ACTOR_LINK_MULTIPLIER)) >> 3;
        g_SpawnedActors[actor_slot].link         = link;
        g_SpawnedActors[actor_slot].unk_2E       = (link & BYTE_MASK) * 24 + 12;
    }
    g_Task->param.actor_slot = actor_slot;
}
