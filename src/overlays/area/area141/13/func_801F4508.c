#include "area141_13.h"

MATCH void func_801F4508(void) {
    u8 slot;

    slot = Actor_FindFree();
    if (slot != GAME_NONE) {
        g_Actors[slot].header.flags = ACTOR_FLAG_IN_USE;
        SP_REF(u16, 0)              = slot;
        func_801A65A0(D_801F4DFC);
        Actor_BeginScript(3, 0);
    }
}
