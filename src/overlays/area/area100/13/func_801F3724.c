#include "area100_13.h"

MATCH void func_801F3724(void) {
    ActorSlot* temp_v0;
    s32        temp_v1;

    g_AreaSceneMode = 1;
    Area_SetCellPalette(0x4A, 0x2F);
    temp_v1 = Actor_FindFreeSlot() & 0xFF;
    if (temp_v1 != 0xFF) {
        temp_v0           = &g_ActorSlots[temp_v1];
        temp_v0->type     = 0xB7;
        temp_v0->x.fixed  = 0x460000;
        temp_v0->flags_00 = 1;
        temp_v0->y.fixed  = 0x340000;
    }
}
