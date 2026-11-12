#include "area141_13.h"

MATCH void func_801F4764(void) {
    u8 slot;

    slot = Actor_FindFree();
    if (slot != GAME_NONE) {
        g_Actors[slot].header.flags = 1;
        SP_REF(u16, 0x00)           = slot;
        func_801A4D54(D_801F4E50);
    }
}
