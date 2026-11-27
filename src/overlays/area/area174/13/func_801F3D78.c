#include "area174_13.h"

MATCH void func_801F3D78(void) {
    u8  actor_slot;
    s32 link;

    actor_slot = Actor_FindFreeSpawned();
    if (actor_slot != GAME_NONE) {
        g_SpawnedActors[actor_slot].header.flags = 1;
        g_SpawnedActors[actor_slot].type         = 0x9D;
        g_SpawnedActors[actor_slot].unk_06       = 0;
        g_SpawnedActors[actor_slot].screen_y     = 0xA5;
        link                                     = (s32)(-(((s32)g_CurrentActor - (s32)g_Actors) * ACTOR_LINK_MULTIPLIER)) >> 3;
        g_SpawnedActors[actor_slot].link         = link;
        g_SpawnedActors[actor_slot].screen_x     = (link & BYTE_MASK) * 24 + 12;
    }
    SELF(Actor)->param.actor_slot = actor_slot;
}
