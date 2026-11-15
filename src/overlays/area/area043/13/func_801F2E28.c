#include "area043_13.h"

MATCH void func_801F2E28(void) {
    Actor* work;
    u8     index;

    index         = Actor_FindFreeSpawned();
    D_1F800000[0] = index;
    if (index != GAME_NONE) {
        g_SpawnedActors[index].header.flags        = 1;
        g_SpawnedActors[D_1F800000[0]].type        = 0x37;
        g_SpawnedActors[D_1F800000[0]].unk_2C      = 0x64;
        g_SpawnedActors[D_1F800000[0]].layer       = 1;
        g_SpawnedActors[D_1F800000[0]].unk_06      = 0;
        work                                       = g_Task;
        g_SpawnedActors[D_1F800000[0]].pos.x.fixed = work->pos.x.fixed;
        g_SpawnedActors[D_1F800000[0]].pos.y.fixed = work->pos.y.fixed;
        g_SpawnedActors[D_1F800000[0]].pos.z.fixed = work->pos.z.fixed + 0x800000;
    }
}
