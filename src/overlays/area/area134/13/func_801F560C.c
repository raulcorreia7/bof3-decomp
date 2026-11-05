#include "area134_13.h"

MATCH void func_801F560C(void) {
    ActorSlot* slot;
    Actor*     work;
    u8         index;

    index = Actor_FindFreeSlot();
    if (index != GAME_NONE) {
        slot          = &g_ActorSlots[index];
        slot->flags   = 1;
        slot->type    = 0x93;
        work          = g_Task;
        slot->x.fixed = work->x.fixed;
        slot->y.fixed = work->y.fixed;
        slot->z.fixed = work->z.fixed;
    }
}
