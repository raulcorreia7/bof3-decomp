#include "area100_13.h"

MATCH void func_801F369C(void) {
    ActorSlot* actor;
    s32        slot;

    g_AreaSceneMode = 1;
    Area_SetCellPalette(0x4A, 0x2F);
    slot = func_8019601C() & 0xFF;
    if (slot != 0xFF) {
        actor           = &g_ActorSlots[slot];
        actor->type     = 0x9B;
        actor->x.fixed  = 0x460000;
        actor->flags_00 = 1;
        actor->y.fixed  = 0x340000;
    }
}
