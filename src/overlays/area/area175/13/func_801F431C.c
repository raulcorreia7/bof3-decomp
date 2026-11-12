#include "area175_13.h"

MATCH void func_801F431C(void) {
    ActorSlot* slot;
    s32        index;

    index = Actor_FindFreeSlot() & BYTE_MASK;
    if (index != GAME_NONE) {
        slot               = &g_ActorSlots[index];
        slot->header.flags = 1;
        slot->type         = 0x39;
        slot->unk_2E       = g_Task->screen_x;
        slot->unk_30       = g_Task->screen_y;
    }
}
