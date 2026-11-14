#include "area081_13.h"
#include "area/spad.h"

MATCH void func_801F2C94(void) {
    SpawnedActor* slot;
    u8            index;

    index = Actor_FindFreeSlot();
    if (index != GAME_NONE) {
        slot               = &g_SpawnedActors[index];
        slot->header.flags = 1;
        slot->type         = 0x27;
        slot->pos.x.fixed  = g_Task->pos.x.fixed;
        slot->pos.y.fixed  = g_Task->pos.y.fixed;
    }
}
