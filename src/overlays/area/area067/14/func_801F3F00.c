#include "area067_14.h"

MATCH void func_801F3F00(void) {
    ActorSlot* actor;
    s32        slot;

    slot = Actor_FindFreeSlot() & BYTE_MASK;
    if (slot != GAME_NONE) {
        actor               = &g_ActorSlots[slot];
        actor->header.flags = 1;
        actor->type         = 0x2D;
        actor->pos.x.fixed  = g_Task->pos.x.fixed;
        actor->pos.y.fixed  = g_Task->pos.y.fixed;
    }
}
