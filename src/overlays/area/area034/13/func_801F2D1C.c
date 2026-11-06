#include "area034_13.h"

MATCH void func_801F2D1C(void) {
    ActorSlot* slot;
    u8         value;

    g_Task->unk_0B = Actor_FindFreeSlot();
    value          = g_Task->unk_0B;
    if (value != 0xFF) {
        slot               = &g_ActorSlots[value];
        slot->header.flags = 1;
        slot->type         = 0x51;
        slot->header.mode  = 6;
        slot->x.fixed      = 0x360000;
        slot->y.fixed      = 0x420000;
        slot->z.fixed      = Area_SampleHeight(slot->x.fixed, 0x420000) << 0x10;
    }
}
