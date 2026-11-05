#include "area067_14.h"

MATCH void func_801F3F00(void) {
    ActorSlot* temp_v0;
    s32        temp_v1;

    temp_v1 = Actor_FindFreeSlot() & 0xFF;
    if (temp_v1 != 0xFF) {
        temp_v0           = &g_ActorSlots[temp_v1];
        temp_v0->flags_00 = 1;
        temp_v0->type     = 0x2D;
        temp_v0->x.fixed  = g_SpadWork->x.fixed;
        temp_v0->y.fixed  = g_SpadWork->y.fixed;
    }
}
