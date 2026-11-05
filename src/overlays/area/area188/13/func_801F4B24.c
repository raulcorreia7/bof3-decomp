#include "area188_13.h"

MATCH void func_801F4B24(void) {
    s32        slot;
    ActorSlot* row;

    slot = Actor_FindFreeSlot() & BYTE_MASK;
    if (slot != GAME_NONE) {
        row        = &g_ActorSlots[slot];
        row->flags = 1;
        row->type  = 0xB9;
    }
}
