#include "game_00.h"

MATCH void func_8019E4A8(void) {
    Actor* work;
    u8     index;

    g_Task->timer += 1;
    work = g_Task;
    if (work->timer == 4) {
        work->timer = 0;
        index       = Actor_FindFreeSlot();
        if (index != GAME_NONE) {
            g_SpawnedActors[index].header.flags = 1;
            g_SpawnedActors[index].type         = ACCESSORY_COUNT;
            g_SpawnedActors[index].header.mode  = 2;
            g_SpawnedActors[index].header.step  = 2;
            work                             = g_Task;
            g_SpawnedActors[index].pos.x.fixed  = work->pos.x.fixed;
            g_SpawnedActors[index].pos.y.fixed  = work->pos.y.fixed;
            g_SpawnedActors[index].pos.z.fixed  = work->pos.z.fixed;
        }
        g_Task->unk_0A -= 1;
        if (g_Task->unk_0A == 0) {
            Actor_Clear();
        }
    }
}
