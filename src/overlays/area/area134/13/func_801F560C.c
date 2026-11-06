#include "area134_13.h"

MATCH void func_801F560C(void) {
    ActorSlot* slot;
    Actor*     work;
    u8         index;

    index = Actor_FindFreeSlot();
    if (index != GAME_NONE) {
        slot               = &g_ActorSlots[index];
        slot->header.flags = 1;
        slot->type         = 0x93;
        work               = g_Task;
        slot->x.fixed      = work->pos.x.fixed;
        slot->y.fixed      = work->pos.y.fixed;
        slot->z.fixed      = work->pos.z.fixed;
    }
}
