#include "area130_13.h"

MATCH void func_801F38F0(void) {
    ActorSlot* slot;
    Actor*     work;
    u8         index;

    index = Actor_FindFreeSlot();
    if (index != GAME_NONE) {
        slot               = &g_ActorSlots[index];
        slot->header.flags = 1;
        slot->type         = 0x78;
        work               = g_Task;
        slot->x.fixed      = work->x.fixed;
        slot->y.fixed      = work->y.fixed;
        slot->z.fixed      = work->z.fixed;
    }
}
