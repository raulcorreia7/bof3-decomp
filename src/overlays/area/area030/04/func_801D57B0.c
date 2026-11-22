#include "area030_04.h"

/* Claims up to two free AREA030 entry rows for the running scene, then
 * seeds the scratch record for the later menu phase and steps the work state. */
MATCH void func_801D57B0(void) {
    FishingState* work;
    FishingState* panel;
    FishingState* other;
    s32           index;

    index = Actor_FindFreeSpawned() & BYTE_MASK;
    if (index != GAME_NONE) {
        g_SpawnedActors[index].header.flags = 1;
        g_SpawnedActors[index].type         = 0x1A;
        g_SpawnedActors[index].header.mode  = 0x10;
        g_SpawnedActors[index].unk_03       = 2;
    }

    index = Actor_FindFreeSpawned() & BYTE_MASK;
    if (index != GAME_NONE) {
        g_SpawnedActors[index].header.flags = 1;
        g_SpawnedActors[index].type         = 0x1A;
        g_SpawnedActors[index].header.mode  = 0x10;
        g_SpawnedActors[index].unk_03       = 4;
    }

    Area_SceneSelectRecord(0x47);
    TASK(FishingState)->active_flags = 0x80;
    TASK(FishingState)->state_29     = 1;
    TASK(FishingState)->state_2A     = 0;

    panel             = TASK(FishingState);
    panel->counter_48 = 0;
    other             = TASK(FishingState);
    panel->origin_x   = 0x5E;
    panel->origin_y   = 0xC2;
    other->step_timer = 0;

    TASK(FishingState)->step_index = 0;
    TASK(FishingState)->tint_5D    = 0;
    TASK(FishingState)->tint_5E    = 0;
    TASK(FishingState)->tint_5F    = 0;

    work            = TASK(FishingState);
    work->sub_index = (work->sub_index + 1);
}
