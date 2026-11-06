#include "area134_13.h"

MATCH void func_801F5698(void) {
    ActorSlot* slot;
    Actor*     work;
    u8         index;

    index = Actor_FindFreeSlot();
    if (index != GAME_NONE) {
        slot               = &g_ActorSlots[index];
        slot->header.flags = 1;
        slot->type         = 0x99;
        work               = g_Task;
        slot->pos.x.fixed  = work->pos.x.fixed;
        slot->pos.y.fixed  = work->pos.y.fixed;
        slot->pos.z.fixed  = work->pos.z.fixed;
    }
}
