#include "area141_13.h"

MATCH void func_801F4764(void) {
    u8 slot;

    slot = Actor_FindFreeField();
    if (slot != GAME_NONE) {
        g_Actors[slot].header.flags = 1;
        SP_REF(u16, 0x00)           = slot;
        Actor_SpawnFromRecord(D_801F4E50);
    }
}
