#include "area132_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3AEC(void) {
    SpawnedActor* actor;
    s32           slot;

    slot = Actor_FindFreeSpawned() & BYTE_MASK;
    if (slot != GAME_NONE) {
        actor               = &g_SpawnedActors[slot];
        actor->pos.x.fixed  = TO_COORD(46);
        actor->type         = 0x73;
        actor->header.flags = 1;
        actor->header.mode  = 1;
        actor->link         = 1;
        actor->pos.y.fixed  = TO_COORD(28);
        actor->pos.z.fixed  = (Area_SampleHeight(actor->pos.x.fixed, actor->pos.y.fixed) << 16) + TO_COORD(512);
        actor->pos.x.fixed -= 0x8000;
    }

    slot = Actor_FindFreeSpawned() & BYTE_MASK;
    if (slot != GAME_NONE) {
        actor               = &g_SpawnedActors[slot];
        actor->pos.x.fixed  = TO_COORD(47);
        actor->type         = 0x73;
        actor->header.flags = 1;
        actor->header.mode  = 1;
        actor->link         = 0;
        actor->pos.y.fixed  = TO_COORD(28);
        actor->pos.z.fixed  = (Area_SampleHeight(actor->pos.x.fixed, actor->pos.y.fixed) << 16) + TO_COORD(512);
        actor->pos.x.fixed -= 0x8000;
    }
}
#else
INCLUDE_ASM(func_801F3AEC);
#endif
