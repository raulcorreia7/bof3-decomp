#include "area120_13.h"

/* Spawns a copy of the g_Actors[2] row in a free actor slot and advances the current task's mode. */
MATCH void func_801F2E28(void) {
    SpawnedActor* slot;
    Actor*        previous;
    u8            index;

    index = Actor_FindFreeSpawned();
    if (index != GAME_NONE) {
        slot = &g_SpawnedActors[index];
        GFX_ClearRect(832, 256, 128, 256);
        *slot              = *(SpawnedActor*)&g_Actors[2];
        slot->header.flags = 1;
        slot->pos.x.fixed  = g_Actors[2].pos.x.fixed;
        slot->pos.y.fixed  = g_Actors[2].pos.y.fixed;
        slot->pos.z.fixed  = g_Actors[2].pos.z.fixed;
        slot->screen_x     = AREA120_IMAGE_RECT->box.x;
        slot->screen_y     = AREA120_IMAGE_RECT->box.y;
        slot->unk_24 |= 0x88;
        previous = SELF(Actor);
        SELF_SET(slot);
        Area_AddGridActor();
        Actor_Clear();
        SELF_SET(previous);
        previous->timer = 2;
    }
    SELF(Actor)->header.mode += 1;
}
