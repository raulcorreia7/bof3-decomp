#include "area141_13.h"

MATCH void func_801F4508(void) {
    s16 slot;

    slot = Actor_FindFree();
    if ((u8)slot != 0xFF) {
        g_Actors[(u8)slot].header.flags = 1;
        *(u16*)0x1F800000               = (u8)slot;
        func_801A65A0(D_801F4DFC);
        Actor_BeginScript(3, 0);
    }
}
