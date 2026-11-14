#include "area120_13.h"

/* Spawns a copy of the g_Actors[2] row in a free actor slot and advances the current task's mode. */
MATCH void func_801F2E28(void) {
    SpawnedActor* slot;
    Actor*        previous;
    u8            index;

    index = Actor_FindFreeSlot();
    if (index != GAME_NONE) {
        slot = &g_SpawnedActors[index];
        GFX_ClearRect(832, 256, 128, 256);
        *slot              = *(SpawnedActor*)&g_Actors[2];
        slot->header.flags = 1;
        slot->pos.x.fixed  = g_Actors[2].pos.x.fixed;
        slot->pos.y.fixed  = g_Actors[2].pos.y.fixed;
        slot->pos.z.fixed  = g_Actors[2].pos.z.fixed;
        slot->unk_2E       = ((RECT*)D_801F43B8)->x;
        slot->unk_30       = ((RECT*)D_801F43B8)->y;
        slot->unk_24 |= 0x88;
        previous = g_Task;
        TASK_SET(slot);
        func_8014D290();
        Actor_Clear();
        TASK_SET(previous);
        previous->timer = 2;
    }
    g_Task->header.mode += 1;
}
