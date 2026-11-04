#include "area108_14.h"

MATCH void func_801F4DC8(void) {
    ActorSlot* temp_s0;
    u8         temp_a0;

    g_SpadWork->unk_0B = func_8019601C();
    temp_a0            = g_SpadWork->unk_0B;
    if (temp_a0 != 0xFF) {
        temp_s0           = &g_ActorSlots[temp_a0];
        temp_s0->x.fixed  = 0x158000;
        temp_s0->flags_00 = 1;
        temp_s0->type     = 0x51;
        temp_s0->unk_01   = 0xA;
        temp_s0->y.fixed  = 0x418000;
        temp_s0->z.fixed  = Area_SampleHeight(temp_s0->x.fixed, 0x418000) << 0x10;
        return;
    }
    g_ScriptState->cursor -= 2;
}
