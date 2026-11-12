#include "game_00.h"

/* K&R call keeps a0 undisturbed; the callee ignores its mode argument. */

MATCH void func_8019ABB0(s32 mode) {
    u8 index;

    index = Actor_FindFreeSlot() & BYTE_MASK;
    if (index != GAME_NONE) {
        g_ActorSlots[index].header.flags = 1;
        /* FAKE: block boundary holds the SYS_SetFlag address load between the stores. */
        FAKE_ORDER_FENCE();
        g_ActorSlots[index].type  = 4;
        g_ActorSlots[index].layer = mode;
        SYS_SetFlag(g_SceneEventFlags, 28);
    }
}
