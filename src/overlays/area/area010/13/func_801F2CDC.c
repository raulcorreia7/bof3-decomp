#include "area010_13.h"
#include "area/spad.h"

MATCH void func_801F2CDC(void) {
    SpawnedActor* slot;
    s32           index;

    index = Actor_FindFreeSlot();
    if (index != GAME_NONE) {
        slot               = &g_SpawnedActors[index];
        slot->header.flags = 1;
        slot->type         = 0x1C;
        slot->pos.x.fixed  = g_Task->pos.x.fixed;
        slot->pos.y.fixed  = g_Task->pos.y.fixed;
    }
}
