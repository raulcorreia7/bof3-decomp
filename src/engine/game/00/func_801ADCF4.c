#include "game_00.h"

/* K&R call forwards a0 untouched as the mode argument. */

MATCH void func_801ADCF4(u8 actor_slot) {
    g_Task->unk_0B = Actor_FindFreeSlot();
    if (g_Task->unk_0B != GAME_NONE) {
        g_ActorSlots[g_Task->unk_0B].header.flags = 1;
        g_ActorSlots[g_Task->unk_0B].type         = 0x32;
        g_ActorSlots[g_Task->unk_0B].unk_06       = actor_slot;
    }
}
