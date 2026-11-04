#include "area010_13.h"
#include "work/area_spad.h"

MATCH void func_801F2CDC(void) {
    ActorSlot* slot;
    s32        index;

    index = Actor_FindFreeSlot();
    if (index != GAME_NONE) {
        slot           = &g_ActorSlots[index];
        slot->flags_00 = 1;
        slot->type     = 0x1C;
        slot->x.fixed  = g_SpadWork->x.fixed;
        slot->y.fixed  = g_SpadWork->y.fixed;
    }
}
