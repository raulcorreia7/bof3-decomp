#include "game_00.h"

MATCH void func_8019E4A8(void) {
    Actor* work;
    u8     index;

    SELF(Actor)->timer += 1;
    work = SELF(Actor);
    if (work->timer == 4) {
        work->timer = 0;
        index       = Actor_FindFreeSpawned();
        if (index != GAME_NONE) {
            g_SpawnedActors[index].header.flags = 1;
            g_SpawnedActors[index].type         = ACCESSORY_COUNT;
            g_SpawnedActors[index].header.mode  = 2;
            g_SpawnedActors[index].header.step  = 2;
            work                                = SELF(Actor);
            g_SpawnedActors[index].pos.x.fixed  = work->pos.x.fixed;
            g_SpawnedActors[index].pos.y.fixed  = work->pos.y.fixed;
            g_SpawnedActors[index].pos.z.fixed  = work->pos.z.fixed;
        }
        SELF(Actor)->unk_0A -= 1;
        if (SELF(Actor)->unk_0A == 0) {
            Actor_Clear();
        }
    }
}
