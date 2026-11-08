#include "area141_13.h"

MATCH void func_801F4508(void) {
    s32 slot;
    u8  b;

    slot = Actor_FindFree();
    b    = slot;
    if (b != 0xFF) {
        g_Actors[b].header.flags = 1;
        *(u16*)0x1F800000        = b;
        func_801A65A0(D_801F4DFC);
        Actor_BeginScript(3, 0);
    }
}
