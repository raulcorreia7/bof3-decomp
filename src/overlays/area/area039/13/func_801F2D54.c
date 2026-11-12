#include "area039_13.h"

MATCH void func_801F2D54(void) {
    s32 slot = Actor_FindFreeSlot() & BYTE_MASK;

    if (slot != GAME_NONE) {
        g_ActorSlots[slot].header.flags = 1;
        g_ActorSlots[slot].type         = 0x36;
        g_ActorSlots[slot].layer        = 0;
    } else {
        g_CurrentActor->unk_7E -= 2;
    }
}
