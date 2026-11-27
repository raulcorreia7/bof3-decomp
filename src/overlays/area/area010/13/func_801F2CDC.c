#include "area010_13.h"

MATCH void func_801F2CDC(void) {
    SpawnedActor* slot;
    s32           index;

    index = Actor_FindFreeSpawned();
    if (index != GAME_NONE) {
        slot               = &g_SpawnedActors[index];
        slot->header.flags = 1;
        slot->type         = 0x1C;
        slot->pos.x.fixed  = SELF(Actor)->pos.x.fixed;
        slot->pos.y.fixed  = SELF(Actor)->pos.y.fixed;
    }
}
