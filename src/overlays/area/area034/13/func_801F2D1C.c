#include "area034_13.h"

MATCH void func_801F2D1C(void) {
    ActorSlot* temp_s0;
    u8         temp_v1;

    ((Actor*)g_SpadWork)->unk_0B = func_8019601C();
    temp_v1                      = ((Actor*)g_SpadWork)->unk_0B;
    if (temp_v1 != 0xFF) {
        temp_s0           = &g_ActorSlots[temp_v1];
        temp_s0->flags_00 = 1;
        temp_s0->type     = 0x51;
        temp_s0->unk_01   = 6;
        temp_s0->x.fixed  = 0x360000;
        temp_s0->y.fixed  = 0x420000;
        temp_s0->z.fixed  = Area_SampleHeight(temp_s0->x.fixed, 0x420000) << 0x10;
    }
}
