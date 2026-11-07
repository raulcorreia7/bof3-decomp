#include "area034_13.h"

MATCH void func_801F2D1C(void) {
    ActorSlot* slot;
    u8         index;

    g_Task->param.actor_slot = Actor_FindFreeSlot();
    index                    = g_Task->param.actor_slot;
    if (index != 0xFF) {
        slot               = &g_ActorSlots[index];
        slot->header.flags = 1;
        slot->type         = 0x51;
        slot->header.mode  = 6;
        slot->pos.x.fixed  = TO_COORD(54);
        slot->pos.y.fixed  = TO_COORD(66);
        slot->pos.z.fixed  = Area_SampleHeight(slot->pos.x.fixed, TO_COORD(66)) << 0x10;
    }
}
