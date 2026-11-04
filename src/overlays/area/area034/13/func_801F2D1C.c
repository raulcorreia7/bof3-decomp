#include "area034_13.h"

MATCH void func_801F2D1C(void) {
    ActorSlot* slot;
    u8         value;

    ((Actor*)g_SpadWork)->unk_0B = Actor_FindFreeSlot();
    value                        = ((Actor*)g_SpadWork)->unk_0B;
    if (value != 0xFF) {
        slot           = &g_ActorSlots[value];
        slot->flags_00 = 1;
        slot->type     = 0x51;
        slot->unk_01   = 6;
        slot->x.fixed  = 0x360000;
        slot->y.fixed  = 0x420000;
        slot->z.fixed  = Area_SampleHeight(slot->x.fixed, 0x420000) << 0x10;
    }
}
