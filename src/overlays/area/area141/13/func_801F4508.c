#include "area141_13.h"

MATCH void func_801F4508(void) {
    s32 slot;
    u8  idx;

    slot = Actor_FindFree();
    idx  = slot;
    if (idx != 0xFF) {
        ((u8*)g_Actors)[idx * 0x98] = 1;
        *(u16*)0x1F800000           = idx;
        func_801A65A0(D_801F4DFC);
        Actor_BeginScript(3, 0);
    }
}
