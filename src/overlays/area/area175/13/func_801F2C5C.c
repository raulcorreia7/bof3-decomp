#include "area175_13.h"

MATCH void func_801F2C5C(void) {
    u8* spin;
    s32 i;

    spin = (u8*)0x800E4800;
    i    = 0;
    do {
        Area_InitSpin(spin);
        i += 1;
        spin += 0x2C;
    } while ((u32)(i & 0xFF) < 0x20U);
    g_SpadWork->unk_09 = 0;
    g_SpadWork->unk_01 += 1;
}
