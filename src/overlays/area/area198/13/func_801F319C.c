#include "area198_13.h"

MATCH void func_801F319C(void) {
    s32 slot;

    slot = Actor_FindFreeSpawned() & BYTE_MASK;
    if (slot != GAME_NONE) {
        g_SpawnedActors[slot].header.flags = 1;
        g_SpawnedActors[slot].type         = 0xA6;
        g_SpawnedActors[slot].unk_06       = 1;
        g_SpawnedActors[slot].unk_07       = g_CurrentActor - g_Actors;
    }
    slot = Actor_FindFreeSpawned() & BYTE_MASK;
    if (slot != GAME_NONE) {
        g_SpawnedActors[slot].header.flags = 1;
        g_SpawnedActors[slot].type         = 0xA6;
        g_SpawnedActors[slot].unk_06       = 0;
        g_SpawnedActors[slot].unk_07       = g_CurrentActor - g_Actors;
    }
    slot = Actor_FindFreeSpawned() & BYTE_MASK;
    if (slot != GAME_NONE) {
        g_SpawnedActors[slot].header.flags = 1;
        g_SpawnedActors[slot].type         = 0xA6;
        g_SpawnedActors[slot].unk_06       = 2;
        g_SpawnedActors[slot].unk_07       = g_CurrentActor - g_Actors;
    }
}
