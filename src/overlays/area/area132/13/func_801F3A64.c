#include "area132_13.h"

MATCH void func_801F3A64(void) {
    ActorSlot* temp_s0;
    s32        temp_v1;

    temp_v1 = func_8019601C() & 0xFF;
    if (temp_v1 != 0xFF) {
        temp_s0           = &g_ActorSlots[temp_v1];
        temp_s0->flags_00 = 1;
        temp_s0->type     = 0x73;
        temp_s0->x.fixed  = 0x2A0000;
        temp_s0->unk_01   = 0;
        temp_s0->y.fixed  = 0x1D0000;
        temp_s0->z.fixed  = Area_SampleHeight(temp_s0->x.fixed, 0x1D0000) << 0x10;
    }
}
