#include "area144_13.h"

MATCH void func_801F3BAC(void) {
    u8 slot;

    slot = Actor_FindFreeSlot();
    if (slot != GAME_NONE) {
        g_ActorSlots[slot].header.flags = 1;
        g_ActorSlots[slot].type         = 0x85;
        g_ActorSlots[slot].unk_06       = g_CurrentActor - g_Actors;
    } else {
        g_ScriptState->cursor -= 2;
    }
}
