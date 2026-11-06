#include "area132_13.h"

MATCH void func_801F3A64(void) {
    ActorSlot* temp_s0;
    s32        temp_v1;

    temp_v1 = Actor_FindFreeSlot() & 0xFF;
    if (temp_v1 != 0xFF) {
        temp_s0               = &g_ActorSlots[temp_v1];
        temp_s0->header.flags = 1;
        temp_s0->type         = 0x73;
        temp_s0->pos.x.fixed  = TO_COORD(42);
        temp_s0->header.mode  = 0;
        temp_s0->pos.y.fixed  = TO_COORD(29);
        temp_s0->pos.z.fixed  = Area_SampleHeight(temp_s0->pos.x.fixed, TO_COORD(29)) << 0x10;
    }
}
