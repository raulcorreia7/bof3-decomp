#include "area043_13.h"

MATCH void func_801F2E28(void) {
    u8 slot;

    slot          = Actor_FindFreeSpawned();
    D_1F800000[0] = slot;
    if (slot != GAME_NONE) {
        g_SpawnedActors[slot].header.flags         = ACTOR_FLAG_IN_USE;
        /* Kept: retail re-reads the staged slot byte for every row store, so this index must come
         * back from the scratchpad instead of from the local. */
        g_SpawnedActors[D_1F800000[0]].type        = 0x37;
        g_SpawnedActors[D_1F800000[0]].unk_2C      = 0x64;
        g_SpawnedActors[D_1F800000[0]].layer       = 1;
        g_SpawnedActors[D_1F800000[0]].unk_06      = 0;
        g_SpawnedActors[D_1F800000[0]].pos.x.fixed = g_Task->pos.x.fixed;
        g_SpawnedActors[D_1F800000[0]].pos.y.fixed = g_Task->pos.y.fixed;
        g_SpawnedActors[D_1F800000[0]].pos.z.fixed = g_Task->pos.z.fixed + TO_COORD(128);
    }
}
