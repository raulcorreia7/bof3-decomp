#include "area141_13.h"

MATCH void func_801F4508(void) {
    u8 slot;

    slot = Actor_FindFreeField();
    if (slot != GAME_NONE) {
        g_Actors[slot].header.flags = ACTOR_FLAG_IN_USE;
        SP_REF(u16, 0)              = slot;
        Actor_SpawnPartyFromRecord(D_801F4DFC);
        Actor_BeginScript(3, 0);
    }
}
