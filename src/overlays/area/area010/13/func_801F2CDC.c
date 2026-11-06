#include "area010_13.h"
#include "work/area_spad.h"

MATCH void func_801F2CDC(void) {
    ActorSlot* slot;
    s32        index;

    index = Actor_FindFreeSlot();
    if (index != GAME_NONE) {
        slot               = &g_ActorSlots[index];
        slot->header.flags = 1;
        slot->type         = 0x1C;
        slot->pos.x.fixed  = g_Task->pos.x.fixed;
        slot->pos.y.fixed  = g_Task->pos.y.fixed;
    }
}
