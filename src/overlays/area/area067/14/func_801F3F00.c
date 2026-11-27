#include "area067_14.h"

MATCH void func_801F3F00(void) {
    SpawnedActor* actor;
    s32           slot;

    slot = Actor_FindFreeSpawned() & BYTE_MASK;
    if (slot != GAME_NONE) {
        actor               = &g_SpawnedActors[slot];
        actor->header.flags = 1;
        actor->type         = 0x2D;
        actor->pos.x.fixed  = SELF(Actor)->pos.x.fixed;
        actor->pos.y.fixed  = SELF(Actor)->pos.y.fixed;
    }
}
