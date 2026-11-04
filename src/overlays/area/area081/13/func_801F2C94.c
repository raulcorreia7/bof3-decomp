#include "area081_13.h"
#include "work/area_spad.h"

MATCH void func_801F2C94(void) {
    ActorSlot* slot;
    u8         index;

    index = Actor_FindFreeSlot();
    if (index != GAME_NONE) {
        slot           = &g_ActorSlots[index];
        slot->flags_00 = 1;
        slot->type     = 0x27;
        slot->x.fixed  = g_SpadWork->x.fixed;
        slot->y.fixed  = g_SpadWork->y.fixed;
    }
}
