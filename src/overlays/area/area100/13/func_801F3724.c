#include "area100_13.h"

MATCH void func_801F3724(void) {
    ActorSlot* actor;
    s32        slot;

    g_AreaSceneMode = 1;
    Area_SetCellPalette(0x4A, 0x2F);
    slot = Actor_FindFreeSlot() & 0xFF;
    if (slot != 0xFF) {
        actor               = &g_ActorSlots[slot];
        actor->type         = 0xB7;
        actor->pos.x.fixed  = 0x460000;
        actor->header.flags = 1;
        actor->pos.y.fixed  = 0x340000;
    }
}
