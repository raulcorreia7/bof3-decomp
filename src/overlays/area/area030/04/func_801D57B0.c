#include "area030_04.h"

/* Claims up to two free AREA030 entry rows for the running scene, then
 * seeds the scratch record for the later menu phase and steps the work state. */
MATCH void func_801D57B0(void) {
    FishingState* work;
    FishingState* panel;
    FishingState* other;
    s32           index;

    index = Actor_FindFreeSlot() & BYTE_MASK;
    if (index != GAME_NONE) {
        g_SpawnedActors[index].header.flags = 1;
        g_SpawnedActors[index].type         = 0x1A;
        g_SpawnedActors[index].header.mode  = 0x10;
        g_SpawnedActors[index].unk_03       = 2;
    }

    index = Actor_FindFreeSlot() & BYTE_MASK;
    if (index != GAME_NONE) {
        g_SpawnedActors[index].header.flags = 1;
        g_SpawnedActors[index].type         = 0x1A;
        g_SpawnedActors[index].header.mode  = 0x10;
        g_SpawnedActors[index].unk_03       = 4;
    }

    Area_SelectSceneRecord(0x47);
    FISHING_STATE->active_flags = 0x80;
    FISHING_STATE->state_29     = 1;
    FISHING_STATE->state_2A     = 0;

    panel                = FISHING_STATE;
    panel->counter_48    = 0;
    other                = FISHING_STATE;
    panel->origin_x_2E   = 0x5E;
    panel->origin_y_30   = 0xC2;
    other->step_timer_09 = 0;

    FISHING_STATE->step_index_0A = 0;
    FISHING_STATE->tint_5D       = 0;
    FISHING_STATE->tint_5E       = 0;
    FISHING_STATE->tint_5F       = 0;

    work               = FISHING_STATE;
    work->sub_index_03 = (work->sub_index_03 + 1);
}
